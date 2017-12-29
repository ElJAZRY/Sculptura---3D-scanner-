#include "camerapreview.h"
#include "time.h"
#include <iostream>

using namespace std;
using namespace cv;

CameraPreview::CameraPreview(QObject *parent): QThread(parent)
{
    stopped = true;
}

CameraPreview::~CameraPreview()
{
    mutex.lock();
    stopped = true;
    capture.release();
    condition.wakeOne();
    mutex.unlock();
    wait();
}

void CameraPreview::startPreview(QSize previewSize)
{
    frameImageSize = previewSize;
    capture.open(0); //TODO display if error

    if (!isRunning()) {
        if (isStopped()){
            stopped = false;
        }
        start(HighPriority);
    }
}

void CameraPreview::stopPreview()
{
    stopped = true;
}

void CameraPreview::run()
{
    while(!stopped){
        if(!capture.grab()){
            cout << "Sensor1 can not grab images." << endl;
        } else if(capture.retrieve(frame, CV_CAP_OPENNI_BGR_IMAGE)) {
            cv::cvtColor(frame, frame, CV_RGB2RGBA);
            frameImage = QImage((uchar*) frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB32);
            frameImage = frameImage.scaled(frameImageSize, Qt::KeepAspectRatio);
            cv::cvtColor(frame, frame, CV_RGBA2RGB);
            emit frameReady(frameImage);
        }
    }
    //when preview stopped, erase last frame
    frameImage = QImage(frameImageSize, QImage::Format_RGB32);
    frameImage.fill(Qt::white);
    emit frameReady(frameImage);
}

bool CameraPreview::isStopped() const
{
    return this->stopped;
}
