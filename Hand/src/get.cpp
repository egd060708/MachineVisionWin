#include "Hand.h"


//---------------- 获取处理过程中的图片------------
const cv::Mat& Hand::get_hand_src() {
  return (hand_src);
}
const cv::Mat& Hand::get_hand_preprocessing() {
  return (hand_preprocessing);
}
const cv::Mat& Hand::get_hand_rotate() {
  return (hand_rotate);
}
const cv::Mat& Hand::get_hand_roi() {
  return (hand_roi);
}
const cv::Mat& Hand::get_hand_vein_enhance() {
  return (hand_vein_enhance);
}
const cv::Mat& Hand::get_hand_vein_split() {
  return (hand_vein_split);
}
