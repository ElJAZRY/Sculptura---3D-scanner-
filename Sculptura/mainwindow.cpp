#include "mainwindow.h"
//#include "ui_mainwindow.h"
//#include "opencv2/core/core.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include <iostream>
//#include <OpenNI.h>
//#include <opencv/cv.h>
//#include <opencv/highgui.h>
//#include <vector>
//#include<cvimagewidget.h>
//#include<QImage>
//#include<QFileDialog>
//#include<QString>

using namespace openni;
using namespace cv;

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_advanced_scanning_clicked()
{
    advanced_parameters = new Advanced_scanning(this);
    advanced_parameters->show();
}



void MainWindow::on_start_scanning_clicked()
{
    VideoCapture camera(0);

    if( !camera.isOpened() )
    {
        cout << "Can not open a laptop camera." << endl;

    }
    for(;;){
        Mat depth;

        if( !camera.grab() ){
            cout << "Sensor1 can not grab images." << endl;

        }else if( camera.retrieve( depth, CV_CAP_OPENNI_DEPTH_MAP ) )

             imshow("Camera",depth);


        if( waitKey( 30 ) == 27 )   break;// 27 is a number of ESC button

   }
}



void MainWindow::on_kinect_window_destroyed()
{

}
