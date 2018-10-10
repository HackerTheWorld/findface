//
//  contrastPicture.hpp
//  findface
//
//  Created by apple on 2018/9/30.
//  Copyright © 2018年 apple. All rights reserved.
//

#ifndef contrastPicture_hpp
#define contrastPicture_hpp

#include <stdio.h>
#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/calib3d.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#endif /* contrastPicture_hpp */

class SamePicture{
    
private:
    std::string astr_imgObject;//第一张图片地址
    std::string astr_imgScenec;//第二张图片地址
    cv::Mat amat_img_object;//第一张图片矩阵
    cv::Mat amat_img_scene;//第二张图片矩阵
    std::vector<cv::KeyPoint> avec_keypoints_object;//第一张图片特征点
    std::vector<cv::KeyPoint> avec_keypoints_scene;//第二张图片特征点
    std::vector<cv::DMatch> avec_goodMatches;//相似特征点
    std::vector<cv::Point2f> avec_scene;//第二张图相似特征点
    std::vector<cv::Point2f> avec_obj;//第一张图相似特征点
public:
    SamePicture(std::string str_imgObject,std::string str_imgScenec);
    SamePicture(cv::Mat mat_img_object,cv::Mat mat_img_scene);
    SamePicture();
    ~SamePicture();
    
    void surfPoint(int int_minHessian,cv::Mat &mat_object,std::vector<cv::KeyPoint> &vec_point,cv::Mat &mat_findObject);
    
    std::vector< std::vector<cv::DMatch>> matchesPoint(cv::Mat &mat_object,cv::Mat &mat_scence);
    
    bool isSame(float flo_ratio,float flo_degree,std::vector< std::vector<cv::DMatch>> vec_matches,std::vector<cv::DMatch> &vec_goodMatches,std::vector<cv::Point2f> &vec_obj,std::vector<cv::Point2f> &vec_scene,std::vector<cv::KeyPoint> vec_keypoints_object,std::vector<cv::KeyPoint> vec_keypoints_scene);
    
    bool checkPicture();
    
};
