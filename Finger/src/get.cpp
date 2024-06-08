#include "Finger.h"


//---------------- 获取处理过程中的图片------------
cv::Mat Finger::get_finger_src() {
  return cv::Mat(finger_src);
}
cv::Mat Finger::get_finger_preprocessing() {
  return cv::Mat(finger_preprocessing);
}
cv::Mat Finger::get_finger_rotate() {
  return cv::Mat(finger_rotate);
}
cv::Mat Finger::get_finger_roi() {
  return cv::Mat(finger_roi);
}
cv::Mat Finger::get_finger_vein_enhance() {
  return cv::Mat(finger_vein_enhance);
}
cv::Mat Finger::get_finger_vein_split() {
  return cv::Mat(finger_vein_split);
}
