#include "mainwindow.h"
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/images/column.png"));
    vtkObject::GlobalWarningDisplayOff();

    preview = new CameraPreview();
    QObject::connect(preview, SIGNAL(frameReady(QImage)), this, SLOT(renderFrame(QImage)));
    QObject::connect(preview, SIGNAL(depthAndColorsReady(std::vector<cv::Mat>, std::vector<cv::Mat>)),
                     this, SLOT(saveDepthAndColorMat(std::vector<cv::Mat>, std::vector<cv::Mat>)));

    kinectPreview = new KinectPreview();
    //Once color frame is ready - show it in preview window
    //When depth and color frames are ready during the scanning - store it into the depth and color vectors of cv::Mat
    QObject::connect(kinectPreview, SIGNAL(frameReady(QImage)), this, SLOT(renderFrame(QImage)));
    QObject::connect(kinectPreview, SIGNAL(depthAndColorsReady(std::vector<cv::Mat>, std::vector<cv::Mat>)),
                     this, SLOT(saveDepthAndColorMat(std::vector<cv::Mat>, std::vector<cv::Mat>)));

    pointCloudFiles = new QStringList();
    pointCloud.reset(new PointCloudT);


    meshFiles = new QStringList();
    selectedMesh.reset(new pcl::PolygonMesh);

    initVisualiser();

    qRegisterMetaType<std::vector<PointCloudT::Ptr>>("std::vector<PointCloudT::Ptr>");
    readPointClouds = new ReadPointClouds();
    QObject::connect(readPointClouds, SIGNAL(pointCloudsReady(std::vector<PointCloudT::Ptr>)),
                     this, SLOT(savePointClouds(std::vector<PointCloudT::Ptr>)));

    qRegisterMetaType<std::vector<pcl::PolygonMesh::Ptr>>("std::vector<pcl::PolygonMesh::Ptr>");
    readMeshes = new ReadMesh();
    QObject::connect(readMeshes, SIGNAL(meshReady(std::vector<pcl::PolygonMesh::Ptr>)),
                     this, SLOT(saveMeshes(std::vector<pcl::PolygonMesh::Ptr>)));
}

MainWindow::~MainWindow()
{
    pointCloudFiles->clear();
    delete pointCloudFiles;
    meshFiles->clear();
    delete meshFiles;
    depth.clear();
    colors.clear();
    delete ui;
}



void MainWindow::on_advanced_scanning_clicked()
{
    advanced_parameters = new Advanced_scanning(this);
    advanced_parameters->show();
}


void MainWindow::on_start_preview_clicked()
{
    ui->statusBar->showMessage("Kinect Ready");

    //Execute the thread
    if (kinectPreview->isStopped()){
        kinectPreview->startPreview(ui->preview_window->size());
        ui->start_preview->setText(tr("Stop preview"));
    } else {
        kinectPreview->stopPreview();
        ui->start_preview->setText(tr("Start preview"));
    }
}

void MainWindow::on_start_scanning_clicked()
{


    ui->statusBar->showMessage("Scanning now");
    //Retrieve and save color and depth frames while scanning
    if (kinectPreview->isRecording()){
        kinectPreview->stopRecording();
        ui->statusBar->showMessage("Scanned");
        ui->start_scanning->setText(tr("Start scanning"));
    } else {
        kinectPreview->startRecording();
        ui->start_scanning->setText(tr("Stop scanning"));
    }
}

void MainWindow::renderFrame(QImage frame)
{
    //Shows color frame in a dedicated window
    if (!frame.isNull())
    {
        ui->preview_window->setAlignment(Qt::AlignCenter);
        ui->preview_window->setPixmap(QPixmap::fromImage(frame));
    }
}

void MainWindow::saveDepthAndColorMat(std::vector<cv::Mat> depth, std::vector<cv::Mat> colors)
{
    this->depth = depth;
    this->colors = colors;
}

void MainWindow::on_actionNew_triggered()
{
    pointCloudFiles->clear();
    showPointCloudFiles();
    pointCloudSet.clear();
    meshFiles->clear();
    showMeshFiles();
    meshSet.clear();
    depth.clear();
    colors.clear();
    initVisualiser();
}


void MainWindow::closeEvent (QCloseEvent *event)
{
    //Generate a confirmation message
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Sculptura",
                                                                tr("Are you sure?, you will lose scanned data"),
                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);

    //Ignore or accept the action according to user's election
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {

        event->accept();
    }
}





void MainWindow::on_actionOpen_PointClouds_triggered()
{
    //Asks user to chose pointclouds,
    QStringList filenames = QFileDialog::getOpenFileNames(
                this,
                tr("Choose Point Clouds"),
                "C://",
                tr("Point Clouds(*.ply *.pcd)"));

    if( !filenames.isEmpty() )
    {
        //Stores files in the list of pointclouds
        pointCloudFiles->append(filenames);
        //Read and save pointclouds in a vector of pointclouds
        readPointClouds->read(filenames);
    }
}


void MainWindow::on_actionOpen_Mesh_triggered()
{
    //Asks user to chose meshes,
    QStringList filenames = QFileDialog::getOpenFileNames(
                this,
                tr("Choose Mesh"),
                "C://",
                tr("Mesh(*.vtk *.stl)"));


    if( !filenames.isEmpty() )
    {
        //Stores files in the list of meshes
        meshFiles->append(filenames);
        //Read and save meshes in a vector of poimeshesntclouds
        readMeshes->read(filenames);
    }
}

void MainWindow::on_actionSave_as_triggered()
{
    //Asks user to chose folder where a mesh will be saved in vtk format
    QString directoryName = QFileDialog::getExistingDirectory(this, QString("Export mesh"),QString(""), QFileDialog::ShowDirsOnly);
    if(directoryName != ""){
        QString filePath;
        filePath = directoryName + "/" + "yourmesh" ".vtk";
        pcl::io::savePolygonFileVTK(filePath.toStdString(), *(meshSet[0]));
    }
}

void MainWindow::on_deletePointCloud_clicked()
{
    QModelIndexList selection = ui->listPointClouds->selectionModel()->selectedIndexes();
    if (!selection.isEmpty()) {
        QModelIndex index = selection.at(0);
        pointCloudFiles->removeAt(index.row());
        pointCloudSet.erase(pointCloudSet.begin()+index.row());
        showPointCloudFiles();
        if (!pointCloudFiles->isEmpty()) {
            showSelectedPointCloud(0);
        }
        else {
            pointCloud.reset(new PointCloudT);
            visualiser->updatePointCloud(pointCloud, "cloud");
            ui->vtkWindow->update ();
        }
    }
}

void MainWindow::on_deleteAllPointClouds_clicked()
{
    if(!pointCloudFiles->isEmpty()) {
        pointCloudFiles->clear();
        showPointCloudFiles();
        pointCloudSet.clear();
        initVisualiser();
    }
}

void MainWindow::on_deleteMesh_clicked()
{
    QModelIndexList selection = ui->listMeshes->selectionModel()->selectedIndexes();
    if (!selection.isEmpty()) {
        QModelIndex index = selection.at(0);
        meshFiles->removeAt(index.row());
        meshSet.erase(meshSet.begin()+index.row());
        showMeshFiles();
        if (!meshFiles->isEmpty()) {
            showSelectedMesh(0);
        }
        else {
            initVisualiser();
        }
    }
}

void MainWindow::on_deleteAllMeshes_clicked()
{
    if(!meshFiles->isEmpty()) {
        meshFiles->clear();
        showMeshFiles();
        meshSet.clear();
        initVisualiser();
    }
}


void MainWindow::showPointCloudFiles()
{
    QStandardItemModel* listModel = new QStandardItemModel();

    QStringList filenameParts;
    foreach (const QString &filename, *pointCloudFiles) {
        filenameParts = filename.split("/");
        QStandardItem* item = new QStandardItem(filenameParts.last());
        listModel->appendRow(item);
    }
    ui->listPointClouds->setModel(listModel);
}

void MainWindow::showMeshFiles()
{
    QStandardItemModel* listModel = new QStandardItemModel();

    QStringList filenameParts;
    foreach (const QString &filename, *meshFiles) {
        filenameParts = filename.split("/");
        QStandardItem* item = new QStandardItem(filenameParts.last());
        listModel->appendRow(item);
    }
    ui->listMeshes->setModel(listModel);
}

void MainWindow::initVisualiser()
{
    //Set up the QvtkWindow widget
    visualiser.reset(new pcl::visualization::PCLVisualizer("visualiser", false));
    ui->vtkWindow->SetRenderWindow(visualiser->getRenderWindow());
    visualiser->setupInteractor(ui->vtkWindow->GetInteractor(), ui->vtkWindow->GetRenderWindow());
    visualiser->addCoordinateSystem(0.3,-0.5,-0.5,-0.5);
    ui->vtkWindow->update();
}

void MainWindow::savePointClouds(std::vector<PointCloudT::Ptr> pointClouds)
{
    pointCloudSet.insert(std::end(pointCloudSet), std::begin(pointClouds), std::end(pointClouds));
    pointCloud = pointCloudSet.at(0);
    showPointCloudFiles();
    showSelectedPointCloud(0);
}

void MainWindow::saveMeshes(std::vector<pcl::PolygonMesh::Ptr> meshes)
{
    meshSet.insert(std::end(meshSet), std::begin(meshes), std::end(meshes));
    selectedMesh = meshSet.at(0);
    showMeshFiles();
    showSelectedMesh(0);
}

void MainWindow::showSelectedPointCloud(int indexPointcloud)
{
    initVisualiser();
    pointCloud = pointCloudSet[indexPointcloud];
    pcl::visualization::PointCloudColorHandlerRGBField<PointType> colorPt(pointCloud);
    visualiser->addPointCloud(pointCloud, colorPt, "cloud");
    visualiser->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "cloud");
    visualiser->updatePointCloud(pointCloud, "cloud");
    ui->vtkWindow->update ();
}

void MainWindow::on_listPointClouds_doubleClicked(const QModelIndex &index)
{
    showSelectedPointCloud(index.row());
}


void MainWindow::showSelectedMesh(int indexMesh)
{
    initVisualiser();
    selectedMesh = meshSet[indexMesh];
    visualiser->addPolygonMesh(*selectedMesh, "polygon");
    visualiser->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "polygon");
    visualiser->updatePolygonMesh(*selectedMesh, "polygon");
    ui->vtkWindow->update ();
}

void MainWindow::Depth2meter(const float feat_x, const float feat_y, const float rawDisparity,
                             float &X, float &Y, float &Z)
{
    // reject invalid points
    if(rawDisparity <= 0)
    {
        X = 0; Y = 0; Z = 0; return;
    }

    float fx = 525.0; // focal length x
    float fy = 525.0; // focal length y
    float cx = 319.5; // optical center x
    float cy = 239.5; // optical center y
    float sclFactor = 1000.0;

    // Recall the camera projective projection model
    Z = rawDisparity / sclFactor;
    X = (feat_x - cx) * Z / fx;
    Y = (feat_y - cy) * Z / fy;
}







pcl::PointCloud<pcl::PointXYZRGB>::Ptr MainWindow::rgbd2pcl(const cv::Mat &rgbImg, const cv::Mat &depthImg)
{
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud;
    cloud.reset (new pcl::PointCloud<pcl::PointXYZRGB>);
    cloud->points.resize (rgbImg.rows*rgbImg.cols);
    int p_count = 0;
    for(int i=0; i<rgbImg.rows; i++) // x
    {
        for(int j=0; j<rgbImg.cols; j++) // y
        {
            float X, Y, Z;
            unsigned short depth = depthImg.at<unsigned short>(i, j);
            // Render the 3D values
            Depth2meter(i,j,depth, X, Y, Z);

            // Remove features which are out of Kinect senser range
            if(X>5 || Y > 5 || Z == 0.0){continue; }
            // Write out the colored 3D point
            cloud->points[p_count].x = X;
            cloud->points[p_count].y = Y;
            cloud->points[p_count].z = Z;


            cloud->points[p_count].r = (float)rgbImg.at<cv::Vec3b>(i,j)[0];
            cloud->points[p_count].g = (float)rgbImg.at<cv::Vec3b>(i,j)[1];
            cloud->points[p_count].b = (float)rgbImg.at<cv::Vec3b>(i,j)[2];
            p_count++;

        }
    }
    return cloud;
}








void MainWindow::on_listMeshes_doubleClicked(const QModelIndex &index)
{
    showSelectedMesh(index.row());
}



void MainWindow::on_get_3D_model_clicked()
{      ui->statusBar->showMessage("generating mesh");
    Cloud_Mesh mymesh;

    mymesh.Run_Mesh(*pointCloudSet[0], tmpmesh);
    visualiser->addPolygonMesh(tmpmesh, "polygon");
    ui->vtkWindow->update ();

    pcl::PolygonMesh::Ptr inp_ptr(&tmpmesh);
    meshSet.push_back(inp_ptr);

    QStandardItemModel* listModel = new QStandardItemModel();
    std::stringstream ss;
    ss << "New mesh.vtk";
    std::string meshName = ss.str();
    QStandardItem* item = new QStandardItem(QString::fromStdString(meshName));
    listModel->appendRow(item);
    ui->listMeshes->setModel(listModel);
       ui->statusBar->showMessage("Mesh Generated");

}



void MainWindow::on_getPointCloud_clicked()
{


    std::string folder = "capturedimages";
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud (new  pcl::PointCloud<pcl::PointXYZRGB>);
    cv::Mat fdepthimage,fcmapimage;
    QStandardItemModel* listModel = new QStandardItemModel();
    int counter = 0;



    ImagesFromDir = QFileDialog::getOpenFileNames(
                    this,tr("Open File"),"",tr("JPEG (*.jpg *.jpeg);;PNG (*.png)" ));



             ui->statusBar->showMessage("Reading images from directory");
        for(int i=0 ; i<=(ImagesFromDir.size()/2)-1;i++ ){

        // cv::Mat *tmp = new cv::Mat;
         fdepthimage  = cv::imread("./"+folder+"/depthimage_"+std::to_string(counter)+".png", CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
         fcmapimage = cv::imread("./"+folder+"/Cmap_"+std::to_string(counter)+".png", CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
         depthimage.push_back(fdepthimage);
         cmapimage.push_back(fcmapimage);  // add the images from dir to vector to use as element of drawing the new image
        counter+=30;

        }

        ui->statusBar->showMessage("images successfully read");

        std::cout<<depthimage.size()<<"  "<<cmapimage.size()<<std::endl;
//        //IMAGES LOADED


    for(int i=0;i<cmapimage.size();i++){

        ui->statusBar->showMessage("generating Point cloud");


        cloud = rgbd2pcl(cmapimage[i], depthimage[i]);
        std::cout<<"crash2"<<std::endl;


        pointCloudSet.push_back(cloud);
        std::cout<<"crash3"<<std::endl;

        std::stringstream ss;
        ss << "New Point Cloud" << i+1;
        std::string pcName = ss.str();
        QStandardItem* item = new QStandardItem(QString::fromStdString(pcName));
        listModel->appendRow(item);
        ui->listPointClouds->setModel(listModel);
    }

    ui->statusBar->showMessage("Point Cloud Ready");




}

