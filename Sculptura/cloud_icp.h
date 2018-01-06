#ifndef CLOUD_ICP_H
#define CLOUD_ICP_H

#include <pcl/console/parse.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/registration/icp.h>
#include <pcl/registration/icp_nl.h>

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <Eigen/Dense>

//using namespace pcl;
//using namespace pcl::io;
//using namespace pcl::console;

typedef pcl::PointXYZRGBA PointT;
typedef pcl::PointCloud<PointT> Cloud;
typedef Cloud::ConstPtr CloudConstPtr;


class Cloud_ICP
{
public:
    Cloud_ICP();
    ~Cloud_ICP();

    Eigen::Matrix4f
    RunICP (pcl::PointCloud<PointT>& input1,
            pcl::PointCloud<PointT>& input2
            , pcl::PointCloud<PointT>& out, Eigen::Matrix4f & init_Transfrom,
            double dist, double rans,
            int iter, bool nonLinear);



};

#endif // CLOUD_ICP_H
