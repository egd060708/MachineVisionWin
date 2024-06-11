#include "iostream"
#include "opencv2/opencv.hpp"
#include <numeric>
#include <cmath>
#include "../../FrangiFilter/include/frangi.h"


using namespace std;
using namespace cv;

 double  finger_match(Mat &img1, Mat &img2)  ;

//参考文献 -----
// https://kns.cnki.net/kcms/detail/knetsearch.aspx?dbcode=CJFD&sfield=au&skey=%E9%A9%AC%E9%9D%99%E4%BA%91&code=44099745&uid=WEEvREcwSlJHSldSdmVqMDh6cEFHNDJkbDNwSjdmaUtkMllXVkVFZDdxQT0=$9A4hF_YAuvQ5obgVAqNKPCYcEjKensW4IQMovwHtwkF4VYPoHbKxJw!!
class Finger {

 public:
  Finger(const cv::Mat &_finger_src) :finger_src(_finger_src.clone()) { }

  void preprocessing(); //图像的预处理
  void find_finger_edge(); // 对图像进行手指边缘检测 ,获取手指的两个边沿
  void get_middle_line(); // 根据手指两个边缘拟合手指中线，
  void rotate_finger(); // 求出手指旋转角度，进行旋转角度校正 得到旋转手指图像

  void find_knuckle(); // 寻找指关节中间亮的部分。


  void enhance_finger_vein(); // 增强手指上的静脉
  void spilt_finger_vein(); // 分割手指静脉纹理
  void finger_LBP_get(); //LBP特征提取
  float template_matching(); //手指模板匹配



  cv::Mat get_finger_src(); //获取输入的图片原生图
  cv::Mat get_finger_preprocessing(); //获取预处理后的图片
  cv::Mat get_finger_rotate(); //获取旋转后的图片
  cv::Mat get_finger_roi(); //获取旋转后截取的ROI图片 | 指关节图片
  cv::Mat get_finger_vein_enhance(); //获取静脉纹理增强图片
  cv::Mat get_finger_vein_split(); //获取静脉纹理分割图片

  void show_finger_src(); //获取输入的图片原生图
  void show_finger_preprocessing(); //获取预处理后的图片
  void show_finger_rotate(); //获取旋转后的图片
  void show_finger_roi(); //获取旋转后截取的ROI图片 | 指关节图片
  void show_finger_vein_enhance(); //获取静脉纹理增强图片
  void show_finger_vein_split(); //获取静脉纹理分割图片




 private:
  cv::Mat finger_src; //手指的图片备份
  cv::Mat finger_preprocessing; //预处理后的图片
  cv::Mat finger_rotate; //旋转后的图片
  cv::Mat finger_roi; //旋转后截取的ROI图片 | 指关节图片
  cv::Mat finger_vein_enhance; //静脉纹理增强图片
  cv::Mat finger_vein_split; //静脉纹理分割图片


  vector<cv::Point2i> edge_left  ;  //左边缘
  vector<cv::Point2i> edge_right  ;  //右边缘
  vector<cv::Point2i> edge_middle  ;  //中心边缘
};

