#include "Finger.h"
void Finger::preprocessing() 
{
  //高斯滤波处理
  cv::GaussianBlur(this->finger_src, this->finger_preprocessing, cv::Size(7, 7), 1.5);
  
  // cv::threshold(this->finger_preprocessing, this->finger_preprocessing, 220, 255, THRESH_BINARY);
  // imshow("", finger_preprocessing);
  // waitKey(0);
}