#include "kinect_preview.h"
#include <sstream>
#include <QMessageBox>

using namespace std;
using namespace cv;

KinectPreview::KinectPreview(QObject *parent): QThread(parent)
{
   recording = false;
   stopped = true;
}

KinectPreview::~KinectPreview()
{
    mutex.lock();
    recording = false;
    stopped = true;
    depth.clear();
    colors.clear();
    colorReader->Release();
    colorReader = nullptr;
    depthReader->Release();
    depthReader = nullptr;
    if (sensor) sensor->Close();
    sensor->Release();
    sensor = nullptr;
    condition.wakeOne();
    mutex.unlock();
    wait();
}

void KinectPreview::startPreview(QSize previewSize)
{
    //Takes size of the preview window, clears vectors which contain depth and color images
    frameImageSize = previewSize;
    depth.clear();
    colors.clear();
    //Check the errors
    HRESULT hr = GetDefaultKinectSensor(&sensor);
    if (FAILED(hr)){
        throw std::runtime_error("Kinect sensor could not be found!");
    }
    //If sensor is found, initialise sourses of depth and color images
    if (sensor){
        initDepthSource();
        initColorSource();
        InitMapper();
    }

    if (!sensor || FAILED(hr)){
        throw std::runtime_error("Kinect init failed!");
    }
    //Starts the thread execution
    if (!isRunning()) {
        if (isStopped()){
            stopped = false;
        }
        start(HighPriority);
    }
}




void KinectPreview::initDepthSource()
{
    IDepthFrameSource* depth_frame_source = nullptr;

    HRESULT hr = sensor->Open();
    //If succesfull, gets the source of the depth frames.
    if (SUCCEEDED(hr))
    {
        hr = sensor->get_DepthFrameSource(&depth_frame_source);
    }
    //A new frame reader for the depth frame source.
    if (SUCCEEDED(hr))
    {
        hr = depth_frame_source->OpenReader(&depthReader);
    }
    //Releases the pointer depth_frame_source and sets it equal to NULL.
    SafeRelease(depth_frame_source);
    depth_frame_source = nullptr;
}

void KinectPreview::InitMapper(){

     int hr = sensor->get_CoordinateMapper(&mapper);
}

void KinectPreview::initColorSource()
{
    IColorFrameSource* color_frame_source = nullptr;
    //If succesfull, gets the source of the color frames.
    HRESULT hr = sensor->Open();

    if (SUCCEEDED(hr))
    {
        hr = sensor->get_ColorFrameSource(&color_frame_source);
    }
    //A new frame reader for the color frame source.
    if (SUCCEEDED(hr))
    {
        hr = color_frame_source->OpenReader(&colorReader);
    }
    //Releases the pointer color_frame_source and sets it equal to NULL.
    SafeRelease(color_frame_source);
    color_frame_source = nullptr;
}

void KinectPreview::stopPreview()
{
    stopped = true;
}

void KinectPreview::run()
{
    while (!stopped) {
        if (stopped) return;
        //While the thread is running, gets the latest depth frame from depth reader
        IDepthFrame* depthFrame = nullptr;
        HRESULT depthHr = depthReader->AcquireLatestFrame(&depthFrame);
        if (SUCCEEDED(depthHr)){
            convertAndSaveDepthMat(depthFrame);
        }
        //Release depth frame and set pointer to NULL
        SafeRelease(depthFrame);
        depthFrame = nullptr;
        //Gets the latest color frame from color reader
        IColorFrame* colorFrame = nullptr;
        HRESULT colorHr = colorReader->AcquireLatestFrame(&colorFrame);
        if (SUCCEEDED(colorHr)){
            convertAndSaveColorMat(colorFrame);
        }
        //Release color frame and set pointer to NULL
        SafeRelease(colorFrame);
        colorFrame = nullptr;
    }

    //when preview stopped, erase last frame
    frameImage = QImage(frameImageSize, QImage::Format_RGB32);
    frameImage.fill(Qt::white);
    emit frameReady(frameImage);
}

void KinectPreview::convertAndSaveDepthMat(IDepthFrame* frame)
{
    UINT nBufferSize = 0; //Contains the size of the frame data buffer in bytes.
    UINT16 *pBuffer = NULL; //Contains the pointer to the depth frame data.

    HRESULT hr = frame->AccessUnderlyingBuffer(&nBufferSize, &pBuffer);

    cv::Mat depthMat(depth_h_, depth_w_, CV_16UC1);
    //Copies the values from buffer to depthMat
    memcpy(depthMat.data, pBuffer, nBufferSize * sizeof(uint16_t));

    if (recording) {
        //Stores depthMat into the vector of depth frames
        depth.push_back(depthMat);
    }
}


void KinectPreview::convertAndSaveColorMat(IColorFrame* frame)
{
    ColorImageFormat imageFormat = ColorImageFormat_None;
    HRESULT hr = frame->get_RawColorImageFormat(&imageFormat);

    cv::Mat colorMat(color_h_, color_w_, CV_8UC4);
    const int buf_size = color_h_ * color_w_ * sizeof(uint8_t) * 4;
    //Copies data from buffer into matrix
    hr = frame->CopyConvertedFrameDataToArray(buf_size, colorMat.data, ColorImageFormat_Bgra);

    if (recording) {
        //Put colorMat into the vector of color frames
        colors.push_back(colorMat);
    }

    //Send for preview
    frameImage = QImage((uchar*) colorMat.data, colorMat.cols, colorMat.rows, colorMat.step, QImage::Format_RGB32);
    frameImage = frameImage.scaled(frameImageSize, Qt::KeepAspectRatio);
    emit frameReady(frameImage);
}

bool KinectPreview::isStopped() const
{
    return this->stopped;
}

void KinectPreview::startRecording()
{
    depth.clear();
    colors.clear();
    recording = true;
}

void KinectPreview::stopRecording()
{
    recording = false;
    emit depthAndColorsReady(depth, colors);
    //SHows message box about number of recorded depth and color frames
    std::stringstream sb;
    sb << "depth = ";
    sb << depth.size();
    sb << ", colors = ";
    sb << colors.size();

    QMessageBox box;
    box.setText(QString::fromStdString(sb.str()));
    box.exec();

    //cv::imshow("color frame", colors[0]);




    std::string folder = "capturedimages";

    cv::Mat output;
    cv::Mat depthimg, colorimg ,   depth_thr;



    std::vector<cv::KeyPoint> keyPts;keyPts.clear();
    int delay = 1000;
    for(int i =0;i<colors.size() && i<depth.size();i+=30){ // we loop over the depth and the color vectors , and "taking every 30 frames,,, one frame "
        // so we can have real time aquisation with no delay , since the kinect speed is 30 frame per second, by using this loop we can trick it and have our data as real time.

        colorimg = colors.at(i);   // accessing color vecter
        depthimg = depth.at(i);  //    accesssing depth vector

       // improc.threshold_depth(depthimg, depth_thr, 1 , 100); // need more about the parameter
     // improc.border_outlier_removal(depth_thr,depth_thr,  10 );

        cv::Mat mapped = map_depth_to_color(depthimg,colorimg);

        cv::cvtColor(colorimg,output,CV_BGRA2BGR);//output is the rgb image ,, but we don't need to add it again

      cv::imwrite("./"+folder+"/depthimage_"+std::to_string(i)+".png", depthimg);
       cv::cvtColor(mapped,mapped,CV_BGRA2RGB);
      cv::imwrite("./"+folder+"/Cmap_"+std::to_string(i)+".png", mapped);


// we can push back to different vector here but we choose to show the user the captured data.



    }
}



cv::Mat KinectPreview::map_depth_to_color(cv::Mat& depth_im, cv::Mat& rgb_im, int colorBytesPerPixel  ){

    // Retrieve Mapper , mapping depth to color frame
    std::vector<ColorSpacePoint> colorSpacePoints(depth_w_ * depth_h_ );
    mapper->MapDepthFrameToColorSpace(depth_w_ * depth_h_, (UINT16*)depth_im.data, colorSpacePoints.size(), &colorSpacePoints[0] );

    //after mapping
    std::vector<BYTE> buffer( depth_w_ * depth_h_ * colorBytesPerPixel );

    // Mapping Color 2 depth in hight and width
    for( int depthY = 0; depthY < depth_h_; depthY++ ){
        for( int depthX = 0; depthX < depth_w_; depthX++ ){
            const unsigned int depthIndex = depthY * depth_w_ + depthX;
            const int colorX = static_cast<int>( colorSpacePoints[depthIndex].X + 0.5f );
            const int colorY = static_cast<int>( colorSpacePoints[depthIndex].Y + 0.5f );
            if( ( 0 <= colorX ) && ( colorX < color_w_ ) && ( 0 <= colorY ) && ( colorY < color_h_ ) ){
                const unsigned int colorIndex = colorY * color_w_ + colorX;
                  buffer[depthIndex * colorBytesPerPixel + 0] = rgb_im.data[colorIndex * colorBytesPerPixel + 0];
                   buffer[depthIndex * colorBytesPerPixel + 1] = rgb_im.data[colorIndex * colorBytesPerPixel + 1];
                  buffer[depthIndex * colorBytesPerPixel + 2] = rgb_im.data[colorIndex * colorBytesPerPixel + 2];
                  buffer[depthIndex * colorBytesPerPixel + 3] = rgb_im.data[colorIndex * colorBytesPerPixel + 3];
            }
         }
       }


    // e.g. Mapped Color Buffer to cv::Mat
    cv::Mat colorMat = cv::Mat( depth_h_, depth_w_, CV_8UC4, &buffer[0] ).clone();
    return colorMat;

}






bool KinectPreview::isRecording() const
{
    return this->recording;
}
