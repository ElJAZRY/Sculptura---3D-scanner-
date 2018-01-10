#ifndef CLOUD_ICP_H
#define CLOUD_ICP_H

#include <pcl/console/parse.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/registration/icp.h>
#include <pcl/registration/icp_nl.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/registration/correspondence_rejection_sample_consensus.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <Eigen/Dense>
#include <iostream>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/point_types.h>
#include <pcl/filters/passthrough.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl/filters/conditional_removal.h>
//#include <pcl/console/parse.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/surface/mls.h>
#include <pcl/common/transforms.h>
#include <pcl/features/normal_3d.h>
#include <pcl/registration/icp.h>
#include <pcl/registration/ia_ransac.h>
#include <cstddef>
#include <cstdint>

#include <pcl/features/normal_3d_omp.h>
#include <pcl/surface/gp3.h>
#include <pcl/io/vtk_io.h>
#include <pcl/surface/poisson.h>
#include <pcl/surface/grid_projection.h>
#include <pcl/surface/vtk_smoothing/vtk_mesh_smoothing_laplacian.h>
#include <pcl/surface/marching_cubes_hoppe.h>
#include <pcl/surface/mls.h>

#include <opencv/cv.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/PolygonMesh.h>



#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


#include <boost/make_shared.hpp>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/point_representation.h>

#include <pcl/io/pcd_io.h>

#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/filter.h>

#include <pcl/features/normal_3d.h>

#include <pcl/registration/icp.h>
#include <pcl/registration/icp_nl.h>
#include <pcl/registration/transforms.h>


using namespace pcl;
using namespace pcl::io;
using namespace pcl::console;

typedef pcl::PointXYZRGB PointT;
typedef pcl::PointCloud<PointT> Cloud;
typedef Cloud::ConstPtr CloudConstPtr;


class Cloud_ICP
{
private:
    double distance;
    int n_iter;
    bool non_linear;
    double rans;
public:
    Cloud_ICP();
    ~Cloud_ICP();

    Cloud::Ptr
    RunICP (std::vector<Cloud::Ptr> Point_clouds,double dist, double rans,int iter, bool nonLinear);




    void sit_distance(double dist_value ){
        distance = dist_value;
    }
    void sit_n_iter(int n_iter_value ){
        n_iter = n_iter_value;
    }
    void sit_rans(double rans_value ){
        rans = rans_value;
    }

    void sit_distance(bool non_linear_value ){
        non_linear = non_linear_value;
    }



};

#endif // CLOUD_ICP_H
