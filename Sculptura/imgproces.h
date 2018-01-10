#ifndef IMGPROCES_H
#define IMGPROCES_H
#include <Kinect.h>
#include <stdexcept>

#include <thread>
#include <chrono>

#include <iostream>
#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
#include <opencv2/video/video.hpp>
#include <opencv/highgui.h>
#include <OpenNI.h>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>


#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/PolygonMesh.h>

class ImgProces
{
public:
    ImgProces();
    ~ImgProces();

    cv::Mat GetDepthFrame();

    cv::Mat GetColorFrame();

    cv::Mat ModDepthForDisplay(const cv::Mat& mat);

    void rgb2gray(cv::Mat &rgbImg, cv::Mat &grayImg);

    void flipImage(cv::Mat &rgbImg);

    void ShowDepthFrame();

    void ShowColorFrame();

    void featureExtraction(cv::Mat &rgbImg, std::vector<cv::KeyPoint> &keyPts);


    void showKeyPoints(cv::Mat &rgbImg, std::vector<cv::KeyPoint> &keyPts);

    void showKeyPoints1(cv::Mat &rgbImg, std::vector<cv::KeyPoint> &keyPts);

    void featureMatching(cv::Mat &rgbImg01, std::vector<cv::KeyPoint> &keyPts01,
                         cv::Mat &rgbImg02, std::vector<cv::KeyPoint> &keyPts02,
                         std::vector< cv::DMatch > *matches, bool robustMatch = false);

    void showFeatureMatches(cv::Mat &rgb_1, std::vector<cv::KeyPoint> &keyPts_1,
                            cv::Mat &rgb_2, std::vector<cv::KeyPoint> &keyPts_2,
                            std::vector< cv::DMatch > *matches);

    cv::Mat map_depth_to_color(cv::Mat& depth_im, cv::Mat& rgb_im);

    cv::Mat threshold_depth(cv::Mat depth_img);
    cv::Mat map_color_to_depth(cv::Mat& depth_im, cv::Mat& rgb_im);

    void drawPointCloud();

    pcl::PointCloud<pcl::PointXYZRGB>::Ptr rgbd2pcl(const cv::Mat &rgbImg, const cv::Mat &depthImg);
private:

    void InitDepthSource();

    void InitColorSource();

    void InitMapper();

    IDepthFrame* WaitForDepthFrame();

    IColorFrame* WaitForColorFrame();

    void myDepth2meter(const float feat_x, const float feat_y, const float rawDisparity,
                                 float &X, float &Y, float &Z);
    void depth2meter(const float feat_x, const float feat_y, const float rawDisparity,
                                 float &X, float &Y, float &Z);





    static const int depth_w_ = 512;  //512
    static const int depth_h_ = 424;  //424
    static const int color_w_ = 1920; //1920
    static const int color_h_ = 1080; //1080

    int i = 1 ;

    IKinectSensor* kin_sensor_;
    IDepthFrameReader* depth_frame_reader_;
    IColorFrameReader* color_frame_reader_;
    ICoordinateMapper* mapper;

    UINT16 *pBuffer;


};

#endif // IMGPROCES_H
