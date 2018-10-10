//
//  contrastPicture.cpp
//  findface
//
//  Created by apple on 2018/9/30.
//  Copyright © 2018年 apple. All rights reserved.
//

#include "contrastPicture.hpp"
SamePicture::SamePicture(std::string str_imgObject,std::string str_imgScenec){
    astr_imgObject = str_imgObject;
    astr_imgScenec = str_imgScenec;
}

SamePicture::SamePicture(cv::Mat mat_img_object,cv::Mat mat_img_scene){
    amat_img_scene = mat_img_scene;
    amat_img_object = mat_img_object;
}

SamePicture::SamePicture(){
    
}

SamePicture::~SamePicture(){
    
}
/**
 int_minHessian 关键点
 mat_object 目标图片
 vec_point 关键点坐标
 mat_findObject 关键点矩正
 */
void SamePicture::surfPoint(int int_minHessian, cv::Mat &mat_object, std::vector<cv::KeyPoint> &vec_point, cv::Mat &mat_findObject){
    //利用SURF检测器检测关键点，计算描述符
    cv::Ptr<cv::xfeatures2d::SURF> detector = cv::xfeatures2d::SURF::create( int_minHessian );
    detector->detectAndCompute( mat_object, cv::noArray(), vec_point, mat_findObject );
}

 std::vector< std::vector<cv::DMatch> > SamePicture::matchesPoint(cv::Mat &mat_object,cv::Mat &mat_scence){
    //基于FLANN匹配器的描述符向量匹配
    //由于SURF是浮点描述符，所以使用NoMyLy2。
    cv::Ptr<cv::DescriptorMatcher> matcher = cv::DescriptorMatcher::create(cv::DescriptorMatcher::FLANNBASED);
    std::vector< std::vector<cv::DMatch> > knn_matches;
    matcher->knnMatch( mat_object, mat_scence, knn_matches, 2 );
     return knn_matches;
}

bool SamePicture::isSame(float flo_ratio,float flo_degree,std::vector< std::vector<cv::DMatch>> vec_matches,std::vector<cv::DMatch> &vec_goodMatches,std::vector<cv::Point2f> &vec_obj,std::vector<cv::Point2f> &vec_scene,std::vector<cv::KeyPoint> vec_keypoints_object,std::vector<cv::KeyPoint> vec_keypoints_scene){
    for (size_t i = 0; i < vec_matches.size(); i++)
    {
        if (vec_matches[i][0].distance < flo_ratio * vec_matches[i][1].distance)
        {
            vec_goodMatches.push_back(vec_matches[i][0]);
            vec_obj.push_back(vec_keypoints_object[vec_matches[i][0].queryIdx].pt);
            vec_scene.push_back(vec_keypoints_scene[vec_matches[i][0].trainIdx].pt);
        }
    }
    if(vec_goodMatches.size()>=vec_keypoints_object.size()*flo_degree){
        return true;
    }else{
        return false;
    }
}

bool SamePicture::checkPicture(){
    bool boo_check = false;
    int int_point = 400;
    cv::Mat mat_findObjectPoint;
    cv::Mat mat_findScenenPoint;
    float flo_ratio = 0;
    float flo_degree = 0;
    if(amat_img_object.empty()){
        amat_img_object = cv::imread(astr_imgObject);
    }
    if (amat_img_scene.empty()) {
        amat_img_scene = cv::imread(astr_imgScenec);
    }
    surfPoint(int_point,amat_img_object,avec_keypoints_object,mat_findObjectPoint);
    surfPoint(int_point, amat_img_scene, avec_keypoints_scene, mat_findScenenPoint);
    std::vector< std::vector<cv::DMatch> > knn_matches = matchesPoint(mat_findObjectPoint,mat_findScenenPoint);
    boo_check = isSame(flo_ratio, flo_degree, knn_matches, avec_goodMatches, avec_obj, avec_scene, avec_keypoints_object, avec_keypoints_scene);
    return boo_check;
}
