#include "Finger.h"
void Finger::preprocessing() 
{
  // imshow("src", finger_src);
  // waitKey(1);
  //高斯滤波处理
  cv::GaussianBlur(this->finger_src, this->finger_preprocessing, cv::Size(7, 7), 1.5);
  // this->finger_preprocessing = this->finger_src;
  
  // cv::threshold(this->finger_preprocessing, this->finger_preprocessing, 220, 255, THRESH_BINARY);
  // imshow("pro", finger_preprocessing);
  // waitKey(0);
}