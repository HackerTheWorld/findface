//
//  main.cpp
//  findface
//
//  Created by apple on 2018/9/26.
//  Copyright © 2018年 apple. All rights reserved.
//

#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "contrastPicture.hpp"
#include <iostream>
#include <unistd.h>
#define FACEXMLPATCH "/Users/apple/Desktop/IOS_test/findface/facexml/haarcascade_frontalface_alt.xml"
#define CAMERADEVICE "0"
using namespace std;
using namespace cv;
static int pic = 0;
string photoType = ".jpg";
std::vector<KeyPoint> avec_keypoints_object;//第一张图片特征点
std::vector<KeyPoint> avec_keypoints_scene;//第二张图片特征点
std::vector<DMatch> avec_goodMatches;//相似特征点
std::vector<Point2f> avec_scene;//第二张图相似特征点
std::vector<Point2f> avec_obj;//第一张图相似特征点
/** Function Headers */
void detectAndDisplay( Mat &frame );

/** Global variables */
CascadeClassifier face_cascade;
//CascadeClassifier eyes_cascade;

/** @function main */
int main( int argc, const char** argv )
{
    
    String face_cascade_name = FACEXMLPATCH;
    //-- 1. Load the cascades
    if( !face_cascade.load( face_cascade_name ) )
    {
        cout << "--(!)Error loading face cascade\n";
        return -1;
    };
    
    //加载图片
//    Mat frame = imread("/Users/apple/Pictures/1915299602.jpeg", 1);
//    detectAndDisplay(frame);
//    imshow("图片", frame);
//    waitKey();
    Mat frame;
    int camera_device = 0;
    VideoCapture capture;
    //-- 2. Read the video stream
    capture.open( camera_device );
    if ( ! capture.isOpened() )
    {
        cout << "--(!)Error opening video capture\n";
        return -1;
    }
    while ( capture.read(frame) )
    {
        if( frame.empty() )
        {
            cout << "--(!) No captured frame -- Break!\n";
            break;
        }
        //-- 3. Apply the classifier to the frame
        detectAndDisplay( frame );
        imshow("面部识别", frame);
        if( waitKey(10) == 27 )
        {
            break; // escape
        }
    }
    return 0;
}

/** @function detectAndDisplay */
void detectAndDisplay( Mat &frame )
{
    Mat frame_gray;
    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );
    
    //-- Detect faces
    std::vector<Rect> faces;
    face_cascade.detectMultiScale( frame_gray, faces );
    for ( size_t i = 0; i < faces.size(); i++ )
    {
        
        //绘制矩形点
        Rect rect(faces[i].x,faces[i].y,faces[i].width,faces[i].height);
        rectangle(frame, rect, Scalar( 220,20,60 ), 3,8,0 );
        Mat roiImg = frame(rect);
        if (roiImg.empty()) {
            continue;
        }
        Mat face = imread("/Users/apple/Desktop/IOS_test/findface/facepicture/55.jpg",IMREAD_GRAYSCALE);
        SamePicture samePicture(roiImg,face);
        if(samePicture.checkPicture()){
            Point avg_Cur = Point(faces[i].x, faces[i].y);
            putText(frame, "panlingyun", avg_Cur,cv::FONT_HERSHEY_PLAIN,2.0,Scalar( 255,255,0 ),2,8,false);
        }
//        string strPath = "/Users/apple/Desktop/IOS_test/findface/facepicture/";
//        strPath.append(to_string (pic));
//        strPath.append(photoType);
//        pic++;
//        imwrite(strPath, roiImg);
        Mat faceROI = frame_gray( faces[i] );
        imshow("人脸识别",frame);
    }
    
    //-- Show what you got
}
//
//                       _oo0oo_
//                      o8888888o
//                      88" . "88
//                      (| -_- |)
//                      0\  =  /0
//                    ___/`---'\___
//                  .' \\|     |// '.
//                 / \\|||  :  |||// \
//                / _||||| -:- |||||- \
//               |   | \\\  -  /// |   |
//               | \_|  ''\---/''  |_/ |
//               \  .-\__  '-'  ___/-. /
//             ___'. .'  /--.--\  `. .'___
//          ."" '<  `.___\_<|>_/___.' >' "".
//         | | :  `- \`.;`\ _ /`;.`/ - ` : | |
//         \  \ `_.   \_ __\ /__ _/   .-` /  /
//     =====`-.____`.___ \_____/___.-`___.-'=====
//                       `=---='
//
//
//     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//               佛祖保佑         永无BUG
//
