#ifndef KINECT_PREVIEW_H
#define KINECT_PREVIEW_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QImage>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/PolygonMesh.h>

#include <Kinect.h>

template<class Interface>
inline void SafeRelease(Interface*& ptr_int)
{
    if (ptr_int)
    {
        ptr_int->Release();
        ptr_int = nullptr;
    }
}

class KinectPreview : public QThread
{
    Q_OBJECT

private:
    static const int depth_w_ = 512;  //512
    static const int depth_h_ = 424;  //424
    static const int color_w_ = 1920; //1920
    static const int color_h_ = 1080; //1080

    IKinectSensor* sensor;
    IDepthFrameReader* depthReader;
    IColorFrameReader* colorReader;

    std::vector<cv::Mat> depth;
    std::vector<cv::Mat> colors;
    //cv::Mat* depthForDisplay;

    QImage frameImage;
    QSize frameImageSize;

    bool recording;
    bool stopped;
    QMutex mutex;
    QWaitCondition condition;

    void initDepthSource();
    void initColorSource();
    void Depth2meter(const float feat_x, const float feat_y, const float rawDisparity,
                     float &x, float &y, float &z);
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr rgbd2pcl(const cv::Mat &rgbImg, const cv::Mat &depthImg);

    void convertAndSaveDepthMat(IDepthFrame* depthFrame);
    void convertAndSaveColorMat(IColorFrame* colorFrame);

signals:
      void frameReady(const QImage &frame);
      void depthAndColorsReady(std::vector<cv::Mat> depth, std::vector<cv::Mat> colors);

protected:
     void run();

public:
    KinectPreview(QObject *parent = 0);
    ~KinectPreview();

    void startPreview(QSize previewSize);
    void stopPreview();
    bool isStopped() const;

    void startRecording();
    void stopRecording();
    bool isRecording() const;
};

#endif // KINECT_PREVIEW_H
