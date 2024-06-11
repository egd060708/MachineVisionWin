#include "Palm.h"


//---------------- 获取处理过程中的图片------------
const cv::Mat& Palm::get_palm_src() {
  return (palm_src);
}
const cv::Mat& Palm::get_palm_preprocessing() {
  return (palm_preprocessing);
}
const cv::Mat& Palm::get_palm_rotate() {
  return (palm_rotate);
}
const cv::Mat& Palm::get_palm_roi() {
  return (palm_roi);
}
const cv::Mat& Palm::get_palm_vein_enhance() {
  return (palm_vein_enhance);
}
const cv::Mat& Palm::get_palm_vein_split() {
  return (palm_vein_split);
}
