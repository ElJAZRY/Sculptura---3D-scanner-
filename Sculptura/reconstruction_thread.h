#ifndef RECONSTRUCTION_THREAD_H
#define RECONSTRUCTION_THREAD_H

class reconstruction_thread : public QThread
{
public:
    reconstruction_thread (pcl::PolygonMesh::Ptr mesh)

private:

    pcl::PolygonMesh::Ptr mainMesh;

    Cloud_Mesh newMesh;

protected:
    void run();

};



#endif // RECONSTRUCTION_THREAD_H
