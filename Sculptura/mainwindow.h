#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define NOMINMAX

#include "advanced_scanning.h"
#include "camerapreview.h"
#include "ui_mainwindow.h"

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <OpenNI.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>

#include <pcl/visualization/pcl_visualizer.h>
#include <vtkRenderWindow.h>

#include <iostream>
#include <vector>
#include <cvimagewidget.h>
#include <boost/make_shared.hpp>

#include <QMainWindow>
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
    void initVisualiser();

    Ui::MainWindow *ui;
    Advanced_scanning *advanced_parameters;
    CameraPreview* preview;
    QStringList* pointCloudFiles;

    //Object in charge of visualizing pointclouds and meshes:
    boost::shared_ptr<pcl::visualization::PCLVisualizer> visualiser;

//    typedef pcl::PointXYZ PointType;
//    typedef pcl::PointCloud<PointType> PointCloudT;

//    PointCloudT::Ptr pointCloud;
//    std::vector<PointCloudT::Ptr> pointCloudSet;

};
#endif // MAINWINDOW_H
