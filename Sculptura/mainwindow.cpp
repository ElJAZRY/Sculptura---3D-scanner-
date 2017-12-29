#include "mainwindow.h"

using namespace openni;
using namespace cv;

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    preview = new CameraPreview();
    QObject::connect(preview, SIGNAL(frameReady(QImage)), this, SLOT(renderFrame(QImage)));
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

