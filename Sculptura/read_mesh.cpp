#include "read_mesh.h"

ReadMesh::ReadMesh(QObject *parent): QThread(parent)
{
    stopped = true;
}

ReadMesh::~ReadMesh()
{
    mutex.lock();
    stopped = true;
    condition.wakeOne();
    mutex.unlock();
    wait();
}

void ReadMesh::read(QStringList files)
{
    //Saves input list of mesh filenames and clear vector of meshes
    meshfilenames = files;
    meshes.clear();
    //Starts the thread execution
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
    //Read checked mesh files from computer
    for(int i=0; i<meshfilenames.size(); i++) {
        QString filename = meshfilenames.at(i);
        pcl::PolygonMesh::Ptr tmpMesh(new pcl::PolygonMesh);

        //Check if it is in a vtk format
        if(filename.contains(".vtk"))
        {
            if (pcl::io::loadPolygonFileVTK(filename.toStdString(), *tmpMesh) == -1)
            {
              PCL_ERROR ("Couldn't read vtk file \n");
            }
        }
        //Put current mesh into the vector of meshes
        meshes.push_back(tmpMesh);
    }
   //Send signal that meshes are ready and stop running
    emit meshReady(meshes);
    stopped = true;
}

bool ReadMesh::isStopped() const
{
    return this->stopped;
}
