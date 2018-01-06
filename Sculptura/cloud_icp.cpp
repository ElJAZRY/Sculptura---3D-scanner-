#include "cloud_icp.h"

Cloud_ICP::Cloud_ICP()
{

}

Cloud_ICP::~Cloud_ICP()
{

}




Cloud::Ptr Cloud_ICP::RunICP(
                                  std::vector<Cloud> Point_clouds,
                                  double dist = 0.05, double rans = 0.05, int iter = 50, bool nonLinear =
        false)

{
    Cloud::Ptr intial_model(new Cloud);
    Cloud::Ptr cloud_target(new Cloud); // target
    Cloud::Ptr cloud_source(new Cloud); //source

    *intial_model = Point_clouds[0];


    for (int i = 1; i < Point_clouds.size () ; i++)
    {

        *cloud_source = *intial_model;

        *cloud_target = Point_clouds[i];

        //        //Downsampling voxel grid


        pcl::VoxelGrid<PointT> grid; //Instance of grid
        grid.setLeafSize(0.01f, 0.01f, 0.01f); //Setting leaf size
        grid.setInputCloud (cloud_source); //Input cloud
        grid.filter (*cloud_source); //Filtered cloud

        grid.setInputCloud (cloud_target); //Input target
        grid.filter (*cloud_target); //Filtered target


        Cloud::Ptr cloud_output1(new Cloud);

        Eigen::Matrix4f Transform(Eigen::Matrix4f::Identity());


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
        icp->setInputTarget(cloud_target); //target
        icp->setInputSource(cloud_source); //soutce


        icp->align(*cloud_output1);

        Transform = Transform * icp->getFinalTransformation();

        //Final Tranformation
        if (icp->hasConverged ())
        {
            pcl::transformPointCloud(*cloud_source, *cloud_output1, Transform);  //Transforming Source to allign Point Cloud
            *cloud_output1 += *cloud_target;  //Concatinating Point Cloud

            std::cout << "\nICP has converged, score is " << icp->getFitnessScore () << std::endl;  //Checking Convergence Value of Point Clouds

        }
        else
        {
            PCL_ERROR ("\nICP has not converged.\n");

        }

        Cloud::Ptr cloud_output2(new Cloud);


        icp->setInputCloud (cloud_output1); //ICP input
        icp->setInputTarget (cloud_target); //ICP target
        icp->setMaxCorrespondenceDistance(dist); // -Set MaxCorrespondenceDistance
        icp->setMaximumIterations (iter);//Setting ICP Iterations
        icp->setRANSACOutlierRejectionThreshold(dist); //Settting RANSAC Outlier Rejection Threshold
        icp->align (*cloud_output2); //Transformed Point Cloud

        Eigen::Matrix4f Transform2 = icp->getFinalTransformation();
        if (icp->hasConverged ())
        {
            pcl::transformPointCloud(*cloud_output1, *cloud_output2, Transform2);

            *cloud_output2 += *cloud_target;//Concatinating Point Cloud
        }


        pcl::io::savePCDFileBinary("cloud_output2.pcd", *cloud_output2);
        std::cout << "saving result to " << "cloud_output2.pcd" << std::endl;



        //out = *tmp;

        return cloud_output2;



    }
}
