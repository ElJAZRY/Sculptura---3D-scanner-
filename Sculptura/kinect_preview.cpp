#include "kinect_preview.h"

using namespace std;
using namespace cv;

KinectPreview::KinectPreview(QObject *parent): QThread(parent)
{
    stopped = true;
}

KinectPreview::~KinectPreview()
{
    mutex.lock();
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

    depth_frame_source->Release();
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

    color_frame_source->Release();
    color_frame_source = nullptr;
}

void KinectPreview::stopPreview()
{
    stopped = true;
    emit depthAndColorsReady(depth, colors);
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
        depthFrame->Release();
        depthFrame = nullptr;

        IColorFrame* colorFrame = nullptr;
        HRESULT colorHr = colorReader->AcquireLatestFrame(&colorFrame);
        if (SUCCEEDED(colorHr)){
            convertAndSaveColorMat(colorFrame);
        }
        colorFrame->Release();
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

    depth.push_back(depthMat);
}

void KinectPreview::convertAndSaveColorMat(IColorFrame* frame)
{
    ColorImageFormat imageFormat = ColorImageFormat_None;
    HRESULT hr = frame->get_RawColorImageFormat(&imageFormat);

    cv::Mat colorMat(color_h_, color_w_, CV_8UC4);
    const int buf_size = color_h_ * color_w_ * sizeof(uint8_t) * 4;
    hr = frame->CopyConvertedFrameDataToArray(buf_size, colorMat.data, ColorImageFormat_Bgra);

    colors.push_back(colorMat);

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
