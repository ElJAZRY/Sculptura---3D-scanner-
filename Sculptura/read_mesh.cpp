#include "read_mesh.h"

ReadMesh::ReadMesh(QObject *parent): QThread(parent)
{
    stopped = true;
}

ReadMesh::~ReadMesh()
{
    mutex.lock();
    stopped = true;
    //filenames.clear();
    //delete filenames;
    condition.wakeOne();
    mutex.unlock();
    wait();
}

void ReadMesh::read(QStringList files)
{
    meshfilenames = files;
    meshes.clear();

    if (!isRunning()) {
        if (isStopped()){
            stopped = false;
        }
        start(HighPriority);
    }
}

void ReadMesh::run()
{
    if (stopped) return;

    for(int i=0; i<meshfilenames.size(); i++) {
        QString filename = meshfilenames.at(i);
        pcl::PolygonMesh::Ptr tmpMesh(new pcl::PolygonMesh);

        //Check if it's vtk file
        if(filename.contains(".vtk"))
        {
            if (pcl::io::loadPolygonFileVTK(filename.toStdString(), *tmpMesh) == -1)
            {
              PCL_ERROR ("Couldn't read vtk file \n"); //TODO don't show filename on screen
            }
        }
        //TODO add STL format

        //Remove undefined values in the pointcloud
        //std::vector<int> indices;
        //pcl::removeNaNFromPointCloud(*tmpCloud, *tmpCloud, indices); //TODO!!!!!!!

        meshes.push_back(tmpMesh);
    }

    emit meshReady(meshes);
    stopped = true;
}

bool ReadMesh::isStopped() const
{
    return this->stopped;
}
