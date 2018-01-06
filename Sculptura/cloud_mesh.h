#ifndef CLOUD_MESH_H
#define CLOUD_MESH_H

#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/features/normal_3d.h>
#include <pcl/io/vtk_io.h>
#include <pcl/filters/passthrough.h>
#include <pcl/surface/poisson.h>


class Cloud_Mesh
{
public:
    Cloud_Mesh();
   ~Cloud_Mesh();
   pcl::PolygonMesh Run_Mesh(pcl::PointCloud<pcl::PointXYZRGB> &Cloud_input);

};

#endif // CLOUD_MESH_H
