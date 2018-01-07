#include "imgproces.h"
#include <opencv/highgui.h>

// Feature detection function headers
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>


ImgProces::ImgProces()
{

}


ImgProces::~ImgProces()
{

}


cv::Mat ImgProces::threshold_depth(cv::Mat depth_img)
{
    float scale_factor = 1000;
    int min_dis = 0,max_dis = 1.0;
    for(int j=0; j<depth_img.cols; j++) // y
      {
        for(int i=0; i<depth_img.rows; i++) // x
          {

            unsigned short depth = depth_img.at<unsigned short>(i,j)/scale_factor;
            if(min_dis>depth || depth>max_dis){
                 depth_img.at<unsigned short>(i,j)=0;
            }

          };
    }
    return depth_img;
}
cv::Mat ImgProces::map_depth_to_color(cv::Mat& depth_im, cv::Mat& rgb_im){


    int colorBytesPerPixel = 4;

    // Retrieve Mapped Coordinates
    std::vector<ColorSpacePoint> colorSpacePoints(depth_w_ * depth_h_ );
    mapper->MapDepthFrameToColorSpace(depth_w_ * depth_h_, (UINT16*)depth_im.data, colorSpacePoints.size(), &colorSpacePoints[0] );

    // Mapped Color Buffer
    std::vector<BYTE> buffer( depth_w_ * depth_h_ * colorBytesPerPixel );

    // Mapping Color Data to Depth Resolution
    for( int depthY = 0; depthY < depth_h_; depthY++ ){
        for( int depthX = 0; depthX < depth_w_; depthX++ ){
            const unsigned int depthIndex = depthY * depth_w_ + depthX;
            const int colorX = static_cast<int>( colorSpacePoints[depthIndex].X + 0.5f );
            const int colorY = static_cast<int>( colorSpacePoints[depthIndex].Y + 0.5f );
            if( ( 0 <= colorX ) && ( colorX < color_w_ ) && ( 0 <= colorY ) && ( colorY < color_h_ ) ){
                const unsigned int colorIndex = colorY * color_w_ + colorX;
                buffer[depthIndex * colorBytesPerPixel + 0] = rgb_im.data[colorIndex * colorBytesPerPixel + 0];
                buffer[depthIndex * colorBytesPerPixel + 1] = rgb_im.data[colorIndex * colorBytesPerPixel + 1];
                buffer[depthIndex * colorBytesPerPixel + 2] = rgb_im.data[colorIndex * colorBytesPerPixel + 2];
                buffer[depthIndex * colorBytesPerPixel + 3] = rgb_im.data[colorIndex * colorBytesPerPixel + 3];
            }
        }
    }


    // e.g. Mapped Color Buffer to cv::Mat
    cv::Mat colorMat = cv::Mat( depth_h_, depth_w_, CV_8UC4, &buffer[0] ).clone();
    return colorMat;

}


cv::Mat ImgProces::map_color_to_depth(cv::Mat& depth_im, cv::Mat& rgb_im){

    // Retrieve Mapped Coordinates
    std::vector<DepthSpacePoint> depthSpacePoints( color_w_ * color_h_ );
    mapper->MapColorFrameToDepthSpace(depth_w_ * depth_h_, (UINT16*)depth_im.data, depthSpacePoints.size(), &depthSpacePoints[0] );

    // Mapped Depth Buffer
    std::vector<UINT16> buffer( color_w_ * color_h_ );

    // Mapping Depth Data to Color Resolution
    for ( int colorY = 0; colorY < color_h_; colorY++ ){
        for ( int colorX = 0; colorX < color_w_; colorX++ ){
            const unsigned int colorIndex = colorY * color_w_ + colorX;
            const int depthX = static_cast<int>( depthSpacePoints[colorIndex].X + 0.5f );
            const int depthY = static_cast<int>( depthSpacePoints[colorIndex].Y + 0.5f );
            if ( ( 0 <= depthX ) && ( depthX < depth_w_ ) && ( 0 <= depthY ) && ( depthY < depth_h_ ) ){
                const unsigned int depthIndex = depthY * depth_w_ + depthX;
                buffer[colorIndex] = depth_im.data[depthIndex];

            }

        }
    }

    // e.g. Mapped Depth Buffer to cv::Mat
    cv::Mat depthMat = cv::Mat( color_h_, color_w_, CV_16UC1, &buffer[0] ).clone();
    return depthMat;
}



void ImgProces::myDepth2meter(const float feat_x, const float feat_y, const float rawDisparity,
                             float &X, float &Y, float &Z)
{
  // reject invalid points
  if(rawDisparity <= 0)
    {
      X = 0; Y = 0; Z = 0; return;
    }

  float fx = 525.0; // focal length x
  float fy = 525.0; // focal length y
  float cx = 319.5; // optical center x
  float cy = 239.5; // optical center y
  float sclFactor = 1000.0;

  // Recall the camera projective projection model
  Z = rawDisparity / sclFactor;
  X = (feat_x - cx) * Z / fx;
  Y = (feat_y - cy) * Z / fy;
}

void ImgProces::depth2meter(const float feat_x, const float feat_y, const float rawDisparity,
                             float &X, float &Y, float &Z)
{
  float minDistance = -10;
  float scaleFactor = 0.0021;
  Z = 0.1236 * std::tan(rawDisparity / 2842.5 + 1.1863);
  X = (feat_x - 480 / 2) * (Z + minDistance) * scaleFactor;
  Y = (feat_y - 640 / 2) * (Z + minDistance) * scaleFactor;
}


pcl::PointCloud<pcl::PointXYZRGB>::Ptr KinectGrabber::rgbd2pcl(const cv::Mat &rgbImg, const cv::Mat &depthImg){
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud;
    cloud.reset (new pcl::PointCloud<pcl::PointXYZRGB>);
    cloud->points.resize (rgbImg.rows*rgbImg.cols);
    int p_count = 0;
    for(int j=0; j<rgbImg.cols; j++) // y
      {
        for(int i=0; i<rgbImg.rows; i++) // x
          {
            float X, Y, Z;
            unsigned short depth = depthImg.at<unsigned short>(i,j);
            // Render the 3D values
            myDepth2meter(i,j,depth, X, Y, Z);

            // Remove features which are out of Kinect senser range
            if(X>5 || Y > 5 || Z == 0.0){continue; }
            // Write out the colored 3D point
            cloud->points[p_count].x = X;
            cloud->points[p_count].y = Y;
            cloud->points[p_count].z = Z;


            cloud->points[p_count].r = (float)rgbImg.at<cv::Vec3b>(i,j)[0];
            cloud->points[p_count].g = (float)rgbImg.at<cv::Vec3b>(i,j)[1];
            cloud->points[p_count].b = (float)rgbImg.at<cv::Vec3b>(i,j)[2];
            p_count++;

          }
      }
      return cloud;
}


void ImgProces::rgb2gray(cv::Mat &rgbImg, cv::Mat &grayImg)
{
    cv::cvtColor(rgbImg, grayImg, cv::COLOR_RGB2GRAY);

}

// Flip image left to right

void KinectGrabber::flipImage(cv::Mat &rgbImg)
{
  cv::flip(rgbImg, rgbImg, 1);
}

void ImgProces::featureExtraction
(cv::Mat &rgbImg, std::vector<cv::KeyPoint> &keyPts)
{
  std::cout<<"Start feature detection...\n";
  // Extract SIFT features
  cv::Ptr<cv::Feature2D> f2d = cv::xfeatures2d::SIFT::create();
   cv::Mat grayImg; rgb2gray(rgbImg, grayImg);
    cv::imshow("grey",grayImg);
  f2d->detect(grayImg,keyPts);

  std::cout<<"Number of detected key points: "<<keyPts.size()<<std::endl;

}


void ImgProces::showKeyPoints
(cv::Mat &rgbImg, std::vector<cv::KeyPoint> &keyPts){
  //-- Draw keypoints
  cv::Mat img_keyPts;
  drawKeypoints( rgbImg, keyPts, img_keyPts, cv::Scalar::all(-1), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS );

  //-- Show detected (drawn) keypoints
  cv::imshow("Keypoints_"+std::to_string(1)+"img", img_keyPts );

  //cv::waitKey(0);
  std::cout<<"End feature detection...\n";
}

void ImgProces::showKeyPoints1
(cv::Mat &rgbImg, std::vector<cv::KeyPoint> &keyPts){
  //-- Draw keypoints
  cv::Mat img_keyPts;
  drawKeypoints( rgbImg, keyPts, img_keyPts, cv::Scalar::all(-1), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS );

  //-- Show detected (drawn) keypoints
  cv::imshow("Keypoints_"+std::to_string(2)+"img", img_keyPts );

  //cv::waitKey(0);
  std::cout<<"End feature detection...\n";
}



void ImgProces::featureMatching(cv::Mat &rgb_1, std::vector<cv::KeyPoint> &keyPts_1,
                                 cv::Mat &rgb_2, std::vector<cv::KeyPoint> &keyPts_2,
                                 std::vector< cv::DMatch > *matches, bool robustMatch)
{
  std::cout<<"Start feature matching...\n";
  //-- Extract SIFT features

  cv::Ptr<cv::Feature2D> f2d = cv::xfeatures2d::SIFT::create();
 // cv::Ptr<cv::FeatureDetector> fd1 = cv::ORB::create();
  cv::Mat gray_1; rgb2gray(rgb_1, gray_1);
  cv::Mat gray_2; rgb2gray(rgb_2, gray_2);
  f2d->detect(gray_1,keyPts_1);
  f2d->detect(gray_2,keyPts_2);

  //-- Draw keypoints
  cv::Mat img_keyPts_1;
  cv::Mat img_keyPts_2;
  drawKeypoints( rgb_1, keyPts_1, img_keyPts_1, cv::Scalar::all(-1), cv::DrawMatchesFlags::DEFAULT );
  drawKeypoints( rgb_2, keyPts_2, img_keyPts_2, cv::Scalar::all(-1), cv::DrawMatchesFlags::DEFAULT );

  //-- Compute descriptor
  cv::Ptr<cv::xfeatures2d::SIFT> extractor = cv::xfeatures2d::SiftDescriptorExtractor::create();
  cv::Mat descriptors_1, descriptors_2;
  extractor->compute( gray_1, keyPts_1, descriptors_1 );
  extractor->compute( gray_2, keyPts_2, descriptors_2 );

  extractor->std::cout<<"descriptors type: "<<descriptors_1.type()<<std::endl;


  cv::FlannBasedMatcher matcher;

//  if ( descriptors_1.empty() || descriptors_2.empty() )
//   {
//       matches->clear(); //set to 0
//       return;
//   }

  matcher.match( descriptors_1, descriptors_2, *matches );

  std::cout<<"Matched descriptors: "<<matches->size()<<std::endl;
    sort(matches->begin(),matches->end(),[](const cv::DMatch& a,const cv::DMatch& b){
        return a.distance<b.distance;
    });

  if(robustMatch)
    {
      std::cout<<"\n Start outlier removal...\n";
      double max_dist = 0; double min_dist = 1000;
      //-- Quick calculation of max and min distances between keypoints
       for( int i = 0; i < descriptors_1.rows; i++ )
       { double dist = (*matches)[i].distance;
         if( dist < min_dist ) min_dist = dist;
         if( dist > max_dist ) max_dist = dist;
       }
       std::cout<<"max descriptor distance = "<<max_dist<<", min descriptor disance = " <<min_dist<<std::endl;
       // Only consider matches with small distances
       std::vector< cv::DMatch > good_matches;
       for( int i = 0; i < descriptors_1.rows; i++ )
       { if( (*matches)[i].distance <= cv::max(9*min_dist, 0.02) )
         { good_matches.push_back( (*matches)[i]); }
       }

      std::nth_element(matches->begin(), matches->begin()+8, matches->end()); // end position
       matches->erase(matches->begin()+9, matches->end());

 //      matches->clear();


//       for(int i = 0; i<10; i++ )
//         {
//     //      good_matches.push_back((*matches[i]));
//          matches->push_back( good_matches[i]);
//         }
       std::cout<<"Good matches number: "<<matches->size()<<std::endl;

  std::cout<<"End feature matching...\n";
 }
}



void ImgProces::showFeatureMatches
(cv::Mat &rgb_1, std::vector<cv::KeyPoint> &keyPts_1,
 cv::Mat &rgb_2, std::vector<cv::KeyPoint> &keyPts_2,
 std::vector< cv::DMatch > *matches)
{
  //-- Show detected (drawn) matches
  cv::Mat img_matches;



  cv::drawMatches( rgb_1, keyPts_1, rgb_2, keyPts_2,
                   *matches, img_matches, cv::Scalar::all(-1), cv::Scalar::all(-1),
                   std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );

  //-- Show detected matches
  imshow( "Feature Matches", img_matches );
  //cv::waitKey(0);
}
