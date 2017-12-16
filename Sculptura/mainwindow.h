#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "advanced_scanning.h"

#include "ui_mainwindow.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <OpenNI.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <vector>
#include<cvimagewidget.h>
#include<QImage>
#include<QFileDialog>
#include<QString>

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


    void on_advanced_scanning_clicked();

    void on_start_scanning_clicked();


    void on_kinect_window_destroyed();

private:
    Ui::MainWindow *ui;
    Advanced_scanning *advanced_parameters;


};
#endif // MAINWINDOW_H
