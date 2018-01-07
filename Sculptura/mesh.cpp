#include "mesh.h"
void mesh()
{
    // Load .pcd file into Pointcloud XYZRGB
    pcl::PointCloud<PointXYZRGB>::Ptr cloud(new pcl::PointCloud<PointXYZRGB>());
    pcl::PCLPointCloud2 cloud_blob;
    pcl::io::loadPCDFile ("alb1.pcd", cloud_blob);
    pcl::fromPCLPointCloud2 (cloud_blob, *cloud);

    // Apply PassThrough filter
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr filtered(new pcl::PointCloud<PointXYZRGB>());
    pcl::PassThrough<pcl::PointXYZRGB> filter;
    filter.setInputCloud(cloud);
    filter.filter(*filtered);

    // Calculate normals
    pcl::NormalEstimation<pcl::PointXYZRGB, pcl::Normal> n;
    pcl::PointCloud<pcl::Normal>::Ptr normals (new pcl::PointCloud<pcl::Normal>);
    pcl::search::KdTree<pcl::PointXYZRGB>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZRGB>);
    tree.reset(new pcl::search:: KdTree<pcl::PointXYZRGB>(false) ) ;
    tree->setInputCloud (cloud);
    n.setInputCloud (cloud);
    n.setSearchMethod (tree);
    n.setKSearch (20);
    n.compute (*normals);

    // Concatenate pointcloud and normals
    pcl::PointCloud<PointXYZRGBNormal>::Ptr cloud_normals(new pcl::PointCloud<PointXYZRGBNormal>());
    pcl::concatenateFields(*filtered, *normals, *cloud_normals);

    // Poisson reconstruction
    pcl::Poisson<pcl::PointXYZRGBNormal> poisson;
    poisson.setDegree(2);
    poisson.setDepth(10);
    poisson.setSolverDivide (6);
    poisson.setIsoDivide (6);

    poisson.setConfidence(true);
    poisson.setManifold(false); // perhaps, for our final pointcloud should be set to true
    poisson.setOutputPolygons(true);

    poisson.setInputCloud(cloud_normals);
    pcl::PolygonMesh mesh;
    poisson.reconstruct(mesh);


    // Color the mesh
    pcl::PointCloud<PointXYZRGB> cloud_color_mesh;
    pcl::fromPCLPointCloud2(mesh.cloud, cloud_color_mesh);

    pcl::KdTreeFLANN<pcl::PointXYZRGB> kdtree;
    kdtree.setInputCloud (cloud);

    // K nearest neighbor search
    int K = 3;
    std::vector<int> pointIdxNKNSearch(K);
    std::vector<float> pointNKNSquaredDistance(K);
    for(int i=0;i<cloud_color_mesh.points.size();++i)
    {
        uint8_t r = 0;
        uint8_t g = 0;
        uint8_t b = 0;
        float dist = 0.0; // probably redundant
        int red = 0;
        int green = 0;
        int blue = 0;

        if (kdtree.nearestKSearch (cloud_color_mesh.points[i], K, pointIdxNKNSearch, pointNKNSquaredDistance) > 0 )
        {
            for (int j = 0; j < pointIdxNKNSearch.size (); ++j)
            {
                r = cloud->points[ pointIdxNKNSearch[j] ].r;
                g = cloud->points[ pointIdxNKNSearch[j] ].g;
                b = cloud->points[ pointIdxNKNSearch[j] ].b;

                red += int(r);
                green += int(g);
                blue += int(b);
                dist += 1.0/pointNKNSquaredDistance[j];
            }
        }

        cloud_color_mesh.points[i].r = int(red/pointIdxNKNSearch.size ()+0.5); // maybe we don't need these 0.5
        cloud_color_mesh.points[i].g = int(green/pointIdxNKNSearch.size ()+0.5);
        cloud_color_mesh.points[i].b = int(blue/pointIdxNKNSearch.size ()+0.5);


    }
    pcl::toPCLPointCloud2(cloud_color_mesh, mesh.cloud);
    pcl::io::saveVTKFile ("mesh_alb_polytrue.vtk", mesh);
}
