#ifndef READ_MESH_H
#define READ_MESH_H


#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/PolygonMesh.h>
#include <pcl/io/vtk_lib_io.h>
#include <boost/make_shared.hpp>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <vector>
#include <QString>

class ReadMesh : public QThread
{
    Q_OBJECT

public:
    ReadMesh(QObject *parent = 0);
    ~ReadMesh();

    void read(QStringList files);

    bool isStopped() const;

signals:
    void meshReady(std::vector<pcl::PolygonMesh::Ptr> meshes);

protected:
    void run();

private:
    QStringList meshfilenames;
    std::vector<pcl::PolygonMesh::Ptr> meshes;

    //Object for loading a PLY file
    //pcl::PLYReader plyReader;

    bool stopped;
    QMutex mutex;
    QWaitCondition condition;
};

#endif // READ_MESH_H
