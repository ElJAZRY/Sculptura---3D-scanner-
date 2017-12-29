#ifndef CAMERAPREVIEW_H
#define CAMERAPREVIEW_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QImage>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

//using namespace cv;

class CameraPreview : public QThread
{
    Q_OBJECT

private:
    cv::VideoCapture capture;
    cv::Mat frame;
    QImage frameImage;
    QSize frameImageSize;
    bool stopped;
    QMutex mutex;
    QWaitCondition condition;

signals:
      void frameReady(const QImage &frame);

protected:
     void run();

public:
    CameraPreview(QObject *parent = 0);
    ~CameraPreview();

    void startPreview(QSize previewSize);
    void stopPreview();

    bool isStopped() const;
};

#endif // CAMERAPREVIEW_H
