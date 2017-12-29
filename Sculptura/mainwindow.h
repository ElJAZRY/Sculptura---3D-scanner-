#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "advanced_scanning.h"
#include "camerapreview.h"

#include "ui_mainwindow.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <OpenNI.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <vector>
#include <cvimagewidget.h>
#include <QImage>
#include <QFileDialog>
#include <QString>
#include <QMessageBox>
#include <QStandardItem>
#include <QStandardItemModel>



using namespace openni;
using namespace cv;

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void renderFrame(QImage frame);

    void on_advanced_scanning_clicked();
    void on_start_preview_clicked();
    void on_actionOpen_PointClouds_triggered();

private:
    void showPointCloudFiles();

    Ui::MainWindow *ui;
    Advanced_scanning *advanced_parameters;
    CameraPreview* preview;
    QStringList* pointCloudFiles;

};
#endif // MAINWINDOW_H
