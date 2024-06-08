#ifndef FINGERVEIN_HAND_HAND_H_
#define FINGERVEIN_HAND_HAND_H_

#include "iostream"
#include "opencv2/opencv.hpp"
#include <numeric>
#include <cmath>
#include "frangi.h"
#include <algorithm> //max,min

using namespace std;
using namespace cv;

double hand_match(Mat &img1, Mat &img2);

// 参考文献 -----
//  https://kns.cnki.net/kcms/detail/knetsearch.aspx?dbcode=CJFD&sfield=au&skey=%E9%A9%AC%E9%9D%99%E4%BA%91&code=44099745&uid=WEEvREcwSlJHSldSdmVqMDh6cEFHNDJkbDNwSjdmaUtkMllXVkVFZDdxQT0=$9A4hF_YAuvQ5obgVAqNKPCYcEjKensW4IQMovwHtwkF4VYPoHbKxJw!!
class Hand
{

public:
  /**
   * @brief 自定义构造函数 输入手指图
   * @param finger_src 输入的手指原图
   */
  Hand(const cv::Mat &_hand_src) :hand_src(_hand_src.clone()) { }

  void hand_roi_process(); // 图像的预处理
  void find_hand_edge();   // 对图像进行手指边缘检测 ,获取手指的两个边沿
  void get_middle_line();  // 根据手指两个边缘拟合手指中线，
  void rotate_hand();      // 求出手指旋转角度，进行旋转角度校正 得到旋转手指图像

  void find_knuckle(); // 寻找指关节中间亮的部分。

  void enhance_hand_vein();  // 增强手指上的静脉
  void spilt_hand_vein();    // 分割手指静脉纹理
  void hand_LBP_get();       // LBP特征提取
  float template_matching(); // 手指模板匹配

  const cv::Mat& get_hand_src();           // 获取输入的图片原生图
  const cv::Mat& get_hand_preprocessing(); // 获取预处理后的图片
  const cv::Mat& get_hand_rotate();        // 获取旋转后的图片
  const cv::Mat& get_hand_roi();           // 获取旋转后截取的ROI图片 | 指关节图片
  const cv::Mat& get_hand_vein_enhance();  // 获取静脉纹理增强图片
  const cv::Mat& get_hand_vein_split();    // 获取静脉纹理分割图片

  void show_hand_src();           // 获取输入的图片原生图
  void show_hand_preprocessing(); // 获取预处理后的图片
  void show_hand_rotate();        // 获取旋转后的图片
  void show_hand_roi();           // 获取旋转后截取的ROI图片 | 指关节图片
  void show_hand_vein_enhance();  // 获取静脉纹理增强图片
  void show_hand_vein_split();    // 获取静脉纹理分割图片

private:
  cv::Mat hand_src;           // 手指的图片备份
  cv::Mat hand_preprocessing; // 预处理后的图片
  cv::Mat hand_rotate;        // 旋转后的图片
  cv::Mat hand_roi;           // 旋转后截取的ROI图片 | 指关节图片
  cv::Mat hand_vein_enhance;  // 静脉纹理增强图片
  cv::Mat hand_vein_split;    // 静脉纹理分割图片

  vector<cv::Point2i> edge_left;   // 左边缘
  vector<cv::Point2i> edge_right;  // 右边缘
  vector<cv::Point2i> edge_middle; // 中心边缘
};

#endif // FINGERVEIN_HAND_HAND_H_
