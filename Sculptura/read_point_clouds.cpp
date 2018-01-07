#include "read_point_clouds.h"

ReadPointClouds::ReadPointClouds(QObject *parent): QThread(parent)
{
    stopped = true;
}

ReadPointClouds::~ReadPointClouds()
{
    mutex.lock();
    stopped = true;
    condition.wakeOne();
    mutex.unlock();
    wait();
}

void ReadPointClouds::read(QStringList files)
{
    //Saves input list of pointcloud filenames and clear vector of pointclouds
    filenames = files;
    pointClouds.clear();
    //Starts the thread execution
    if (!isRunning()) {
        if (isStopped()){
            stopped = false;
        }
        start(HighPriority);
    }
}

void ReadPointClouds::run()
{
    if (stopped) return;
    //Read checked pointcloud files from computer
    for(int i=0; i<filenames.size(); i++) {
        QString filename = filenames.at(i);
        PointCloudT::Ptr tmpCloud(new PointCloudT);

        //Check if it is whether a .ply or a .pcd file, and use the respective loading function
        if(filename.contains(".ply")){
            if (plyReader.read(filename.toStdString(), *tmpCloud) == -1)
            {
              PCL_ERROR ("Couldn't read ply file \n");
            }
        }else if(filename.contains(".pcd")){
            if (pcl::io::loadPCDFile<pcl::PointXYZRGB>(filename.toStdString(), *tmpCloud) == -1)
            {
              PCL_ERROR ("Couldn't read pcd file \n");
            }
        }
        //put current pointcloud into the vector of point clouds.
        pointClouds.push_back(tmpCloud);
    }
    //Send signal that pointclouds are ready and stop running
    emit pointCloudsReady(pointClouds);
    stopped = true;
}

bool ReadPointClouds::isStopped() const
{
    return this->stopped;
}
