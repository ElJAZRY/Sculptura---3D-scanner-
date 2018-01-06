#include "cloud_icp.h"

Cloud_ICP::Cloud_ICP()
{

}

Cloud_ICP::~Cloud_ICP()
{

}




Eigen::Matrix4f Cloud_ICP::RunICP(pcl::PointCloud<PointT>& input1,
        pcl::PointCloud<PointT>& input2, pcl::PointCloud<PointT>& out,Eigen::Matrix4f & init_Transfrom,
        double dist = 0.05, double rans = 0.05, int iter = 50, bool nonLinear =
                false)

{



    Cloud::Ptr model(new Cloud);
    *model = input1;

    std::cout << " width: " << model->width << " height: " << model->height
            << std::endl;

    Eigen::Matrix4f Transform(Eigen::Matrix4f::Identity());

    Cloud::Ptr data(new Cloud);
    *data = input2;
    std::cout << " width: " << data->width << " height: " << data->height
            << std::endl;

    pcl::IterativeClosestPoint < PointT, PointT > *icp;

    if (nonLinear) {
        std::cout << "Using IterativeClosestPointNonLinear" << std::endl;
        icp = new pcl::IterativeClosestPointNonLinear<PointT, PointT>();
    } else {
        std::cout << "Using IterativeClosestPoint" << std::endl;
        icp = new pcl::IterativeClosestPoint<PointT, PointT>();
    }

    icp->setMaximumIterations(iter);
    icp->setMaxCorrespondenceDistance(dist);
    icp->setRANSACOutlierRejectionThreshold(rans);

    icp->setInputTarget(model);

    icp->setInputSource(data);

    Cloud::Ptr tmp(new Cloud);
    icp->align(*tmp);

    Transform = Transform * icp->getFinalTransformation();

    pcl::transformPointCloud(*data, *tmp, Transform);

    std::cout << "has converged:" << icp->hasConverged() << " score: "
            << icp->getFitnessScore() << std::endl;

    std::cout << icp->getFinalTransformation() << std::endl;

    pcl::io::savePCDFileBinary("tmp.pcd", *tmp);
    std::cout << "saving result to " << "tmp.pcd" << std::endl;



    //out = *tmp;

    return icp->getFinalTransformation();

}
