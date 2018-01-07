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
    RunICP (std::vector<Cloud> Point_clouds,
            double dist, double rans,
            int iter, bool nonLinear);




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
