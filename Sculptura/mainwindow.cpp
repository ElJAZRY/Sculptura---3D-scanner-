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
