#ifndef FINGERVEIN_HAND_HAND_H_
#define FINGERVEIN_HAND_HAND_H_

#include "iostream"
#include "opencv2/opencv.hpp"
#include <numeric>
#include <cmath>
#include "frangi.h"
#include <algorithm> //max,min
#include <string>

using namespace std;
using namespace cv;

double palm_match(Mat &img1, Mat &img2);

// 参考文献 -----
//  https://kns.cnki.net/kcms/detail/knetsearch.aspx?dbcode=CJFD&sfield=au&skey=%E9%A9%AC%E9%9D%99%E4%BA%91&code=44099745&uid=WEEvREcwSlJHSldSdmVqMDh6cEFHNDJkbDNwSjdmaUtkMllXVkVFZDdxQT0=$9A4hF_YAuvQ5obgVAqNKPCYcEjKensW4IQMovwHtwkF4VYPoHbKxJw!!
class Palm
{

public:
  /**
   * @brief 自定义构造函数 输入手掌图
   * @param palm_src 输入的手掌原图
   */
  Palm(const cv::Mat &_palm_src) :palm_src(_palm_src.clone()) { }

  void palm_roi_process(); // 图像的预处理
  void find_palm_edge();   // 对图像进行手掌边缘检测 ,获取手掌的两个边沿
  void get_middle_line();  // 根据手掌两个边缘拟合手掌中线，
  void rotate_palm();      // 求出手掌旋转角度，进行旋转角度校正 得到旋转手掌图像

  void find_knuckle(); // 寻找指关节中间亮的部分。

  void enhance_palm_vein();  // 增强手掌上的静脉
  void spilt_palm_vein();    // 分割手掌静脉纹理
  void palm_LBP_get();       // LBP特征提取
  float template_matching(); // 手掌模板匹配

  const cv::Mat& get_palm_src();           // 获取输入的图片原生图
  const cv::Mat& get_palm_preprocessing(); // 获取预处理后的图片
  const cv::Mat& get_palm_rotate();        // 获取旋转后的图片
  const cv::Mat& get_palm_roi();           // 获取旋转后截取的ROI图片 | 指关节图片
  const cv::Mat& get_palm_vein_enhance();  // 获取静脉纹理增强图片
  const cv::Mat& get_palm_vein_split();    // 获取静脉纹理分割图片

  void show_palm_src();           // 获取输入的图片原生图
  void show_palm_preprocessing(); // 获取预处理后的图片
  void show_palm_rotate();        // 获取旋转后的图片
  void show_palm_roi();           // 获取旋转后截取的ROI图片 | 指关节图片
  void show_palm_vein_enhance();  // 获取静脉纹理增强图片
  void show_palm_vein_split();    // 获取静脉纹理分割图片

private:
  cv::Mat palm_src;           // 手掌的图片备份
  cv::Mat palm_preprocessing; // 预处理后的图片
  cv::Mat palm_rotate;        // 旋转后的图片
  cv::Mat palm_roi;           // 旋转后截取的ROI图片 | 指关节图片
  cv::Mat palm_vein_enhance;  // 静脉纹理增强图片
  cv::Mat palm_vein_split;    // 静脉纹理分割图片

  vector<cv::Point2i> edge_left;   // 左边缘
  vector<cv::Point2i> edge_right;  // 右边缘
  vector<cv::Point2i> edge_middle; // 中心边缘
};

#endif // FINGERVEIN_HAND_HAND_H_
