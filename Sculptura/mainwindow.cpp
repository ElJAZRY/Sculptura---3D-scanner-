#include "mainwindow.h"

using namespace openni;
using namespace cv;

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    pointCloudFiles = new QStringList();
    preview = new CameraPreview();
    QObject::connect(preview, SIGNAL(frameReady(QImage)), this, SLOT(renderFrame(QImage)));
    ui->setupUi(this);
    initVisualiser();
}

MainWindow::~MainWindow()
{
    pointCloudFiles->clear();
    delete pointCloudFiles;
    delete ui;
}

void MainWindow::on_advanced_scanning_clicked()
{
    advanced_parameters = new Advanced_scanning(this);
    advanced_parameters->show();
}

void MainWindow::on_start_preview_clicked()
{
    if (preview->isStopped()){
        preview->startPreview(ui->preview_window->size());
        ui->start_preview->setText(tr("Stop preview"));
    } else {
        preview->stopPreview();
        ui->start_preview->setText(tr("Start preview"));
    }
}

void MainWindow::renderFrame(QImage frame)
{
    if (!frame.isNull())
    {
        ui->preview_window->setAlignment(Qt::AlignCenter);
        //frame = frame.scaled(ui->preview_window->size(), Qt::KeepAspectRatio);
        ui->preview_window->setPixmap(QPixmap::fromImage(frame));
    }
}

void MainWindow::on_actionOpen_PointClouds_triggered()
{
    //TODO configure QFileDialog to block other file extensions than specified
    QStringList filenames = QFileDialog::getOpenFileNames(this, tr("Open PCD or PLY files..."),"", tr(""));

    if( !filenames.isEmpty() )
    {
        pointCloudFiles->append(filenames);
        showPointCloudFiles();
    }
}

void MainWindow::showPointCloudFiles() {
    QStandardItemModel* listModel = new QStandardItemModel();

    QStringList filenameParts;
    foreach (const QString &filename, *pointCloudFiles) {
        filenameParts = filename.split("/");
        QStandardItem* item = new QStandardItem(filenameParts.last());
        listModel->appendRow(item);
    }

    ui->listPointClouds->setModel(listModel);
}

void MainWindow::initVisualiser() {
    // Set up the QvtkWindow widget
    visualiser.reset(new pcl::visualization::PCLVisualizer("visualiser", false));
    //Set the QvtkWindow to show the graphics rendered by "visualiser"
    ui->vtkWindow->SetRenderWindow(visualiser->getRenderWindow());
    //Set "visualiser" to receive the user interactions captured by the WvtkWindow widget
    visualiser->setupInteractor(ui->vtkWindow->GetInteractor(), ui->vtkWindow->GetRenderWindow());
    visualiser->addCoordinateSystem(0.3,-0.5,-0.5,-0.5);
    ui->vtkWindow->update();

    //Link the pointcloud container from the database to the visualization object:
//    pcl::visualization::PointCloudColorHandlerCustom<PointType> colorPt(pointCloud, 0, 123, 100);
//    visualiser->addPointCloud(pointCloud, colorPt, "cloud");
    visualiser->resetCamera();
    //Set visualization parameters such as size of points:
    visualiser->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "cloud");
    ui->vtkWindow->update();
}
