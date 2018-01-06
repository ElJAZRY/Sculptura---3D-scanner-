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
    frameImageSize = previewSize;
    depth.clear();
    colors.clear();

    HRESULT hr = GetDefaultKinectSensor(&sensor);
    if (FAILED(hr)){
        throw std::runtime_error("Kinect sensor could not be found!");
    }

    if (sensor){
        initDepthSource();
        initColorSource();
    }

    if (!sensor || FAILED(hr)){
        throw std::runtime_error("Kinect init failed!");
    }

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

    if (SUCCEEDED(hr))
    {
        hr = sensor->get_DepthFrameSource(&depth_frame_source);
    }

    if (SUCCEEDED(hr))
    {
        hr = depth_frame_source->OpenReader(&depthReader);
    }

    SafeRelease(depth_frame_source);
    depth_frame_source = nullptr;
}

void KinectPreview::initColorSource()
{
    IColorFrameSource* color_frame_source = nullptr;

    HRESULT hr = sensor->Open();

    if (SUCCEEDED(hr))
    {
        hr = sensor->get_ColorFrameSource(&color_frame_source);
    }

    if (SUCCEEDED(hr))
    {
        hr = color_frame_source->OpenReader(&colorReader);
    }

    SafeRelease(color_frame_source);
    color_frame_source = nullptr;
}

void KinectPreview::stopPreview()
{
    stopped = true;
    //TODO maybe add sensor->Close() if camera still active
}

void KinectPreview::run()
{
    while (!stopped) {
        if (stopped) return;

        IDepthFrame* depthFrame = nullptr;
        HRESULT depthHr = depthReader->AcquireLatestFrame(&depthFrame);
        if (SUCCEEDED(depthHr)){
            convertAndSaveDepthMat(depthFrame);
        }
        SafeRelease(depthFrame);
        depthFrame = nullptr;

        IColorFrame* colorFrame = nullptr;
        HRESULT colorHr = colorReader->AcquireLatestFrame(&colorFrame);
        if (SUCCEEDED(colorHr)){
            convertAndSaveColorMat(colorFrame);
        }
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
    UINT nBufferSize = 0;
    UINT16 *pBuffer = NULL;

    HRESULT hr = frame->AccessUnderlyingBuffer(&nBufferSize, &pBuffer);

    cv::Mat depthMat(depth_h_, depth_w_, CV_16UC1);

    memcpy(depthMat.data, pBuffer, nBufferSize * sizeof(uint16_t));

    //cv::Mat disp_mat = ModDepthForDisplay(depth_mat);
    //cv::imshow("Depth", disp_mat);

    if (recording) {
        depth.push_back(depthMat);
    }
}


void KinectPreview::Depth2meter(const float feat_x, const float feat_y, const float rawDisparity,
                             float &X, float &Y, float &Z)
{
  // reject invalid points
  if(rawDisparity <= 0)
    {
      X = 0; Y = 0; Z = 0; return;
    }

  float fx = 525.0; // focal length x
  float fy = 525.0; // focal length y
  float cx = 319.5; // optical center x
  float cy = 239.5; // optical center y
  float sclFactor = 5000.0;

  // Recall the camera projective projection model
  Z = rawDisparity / sclFactor;
  X = (feat_x - cx) * Z / fx;
  Y = (feat_y - cy) * Z / fy;
}



pcl::PointCloud<pcl::PointXYZRGB>::Ptr KinectPreview::rgbd2pcl(const cv::Mat &rgbImg, const cv::Mat &depthImg)
{
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud;
    cloud.reset (new pcl::PointCloud<pcl::PointXYZRGB>);
    cloud->points.resize (rgbImg.rows*rgbImg.cols);
    int p_count = 0;
    for(int i=0; i<rgbImg.rows; i++) // x
      {
        for(int j=0; j<rgbImg.cols; j++) // y
          {
            float X, Y, Z;
            unsigned short depth = depthImg.at<unsigned short>(i, j);
            // Render the 3D values
            Depth2meter(i,j,depth, X, Y, Z);

            // Remove features which are out of Kinect senser range
            if(X>5 || Y > 5 || Z == 0.0){continue; }
            // Write out the colored 3D point
            cloud->points[p_count].x = X;
            cloud->points[p_count].y = Y;
            cloud->points[p_count].z = Z;


            cloud->points[p_count].r = (float)rgbImg.at<cv::Vec3b>(i,j)[0];
            cloud->points[p_count].g = (float)rgbImg.at<cv::Vec3b>(i,j)[1];
            cloud->points[p_count].b = (float)rgbImg.at<cv::Vec3b>(i,j)[2];
            p_count++;

          }
      }
      return cloud;
}



void KinectPreview::convertAndSaveColorMat(IColorFrame* frame)
{
    ColorImageFormat imageFormat = ColorImageFormat_None;
    HRESULT hr = frame->get_RawColorImageFormat(&imageFormat);

    cv::Mat colorMat(color_h_, color_w_, CV_8UC4);
    const int buf_size = color_h_ * color_w_ * sizeof(uint8_t) * 4;
    hr = frame->CopyConvertedFrameDataToArray(buf_size, colorMat.data, ColorImageFormat_Bgra);

    if (recording) {
        colors.push_back(colorMat);
    }

    //send for preview

    //cv::cvtColor(frame, frame, CV_RGB2RGBA); //if need to use make a copy of colorMat and change its format
    frameImage = QImage((uchar*) colorMat.data, colorMat.cols, colorMat.rows, colorMat.step, QImage::Format_RGB32);
    frameImage = frameImage.scaled(frameImageSize, Qt::KeepAspectRatio);
    //cv::cvtColor(frame, frame, CV_RGBA2RGB);
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

    std::stringstream sb;
    sb << "depth = ";
    sb << depth.size();
    sb << ", colors = ";
    sb << colors.size();

    QMessageBox box;
    box.setText(QString::fromStdString(sb.str()));
    box.exec();

    cv::imshow("color frame", colors[0]);
}

bool KinectPreview::isRecording() const
{
    return this->recording;
}
