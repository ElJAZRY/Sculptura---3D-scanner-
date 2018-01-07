
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define NOMINMAX

#include "advanced_scanning.h"
#include "camerapreview.h"
#include "kinect_preview.h"
#include "read_point_clouds.h"
#include "read_mesh.h"
#include "ui_mainwindow.h"
#include "cloud_mesh.h"

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <OpenNI.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>

#include <pcl/visualization/pcl_visualizer.h>
#include <vtkRenderWindow.h>
#include <pcl/io/vtk_lib_io.h>

#include <iostream>
#include <string>
#include <sstream>
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
#include <QListWidgetItem>

//using namespace openni;
//using namespace cv;
//using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    typedef pcl::PointXYZRGB PointType;
    typedef pcl::PointCloud<PointType> PointCloudT;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void renderFrame(QImage frame);
    void savePointClouds(std::vector<PointCloudT::Ptr> pointClouds);
    void saveMeshes(std::vector<pcl::PolygonMesh::Ptr> meshes);
    void saveDepthAndColorMat(std::vector<cv::Mat> depth, std::vector<cv::Mat> colors);

    void on_advanced_scanning_clicked();
    void on_start_preview_clicked();
    void on_start_scanning_clicked();
    void on_actionOpen_PointClouds_triggered();
    void on_deletePointCloud_clicked();
    void on_listPointClouds_doubleClicked(const QModelIndex &index);
    void on_listMeshes_doubleClicked(const QModelIndex &index);
    void on_actionOpen_Mesh_triggered();

    void on_deleteMesh_clicked();

    void on_deleteAllPointClouds_clicked();

    void on_deleteAllMeshes_clicked();

    void on_actionSave_as_triggered();

    void on_actionNew_triggered();

    void on_get_3D_model_clicked();

private:
    void showPointCloudFiles();
    void showSelectedPointCloud(int);
    void showMeshFiles();
    void showSelectedMesh(int);
    void initVisualiser();

    Ui::MainWindow *ui;
    Advanced_scanning *advanced_parameters;
    CameraPreview* preview;
    KinectPreview* kinectPreview;

    std::vector<cv::Mat> depth;
    std::vector<cv::Mat> colors;

    QStringList* pointCloudFiles;
    QStringList* meshFiles;

    //Object in charge of visualizing pointclouds and meshes:
    boost::shared_ptr<pcl::visualization::PCLVisualizer> visualiser;

    PointCloudT::Ptr pointCloud; //currently selected point cloud
    std::vector<PointCloudT::Ptr> pointCloudSet; //list of all loaded point clouds

    pcl::PolygonMesh::Ptr selectedMesh;
    std::vector<pcl::PolygonMesh::Ptr> meshSet;

    pcl::PolygonMesh tmpmesh;

    ReadPointClouds* readPointClouds;
    ReadMesh* readMeshes;

};
#endif // MAINWINDOW_H
