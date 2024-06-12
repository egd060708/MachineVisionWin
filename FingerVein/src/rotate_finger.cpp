#include "Finger.h"

void Finger::rotate_finger()
{
  find_finger_edge(finger_preprocessing,0.18,0.945,0.1,0.92);
  Mat temp = Mat::zeros(finger_preprocessing.size(), CV_8UC3);
  temp = temp.rowRange(static_cast<int>(temp.rows * 0.18), static_cast<int>(temp.rows * 0.945)).clone();
  temp = temp.colRange(static_cast<int>(temp.cols * 0.1), static_cast<int>(temp.cols * 0.92)).clone();

  Vec<float, 4> middle_fit_line;
  // 别的方法 拟合出来的直线 角度是一样的， 距离有些不同罢了 没关系 所以选择L2计算快一点;
  cv::fitLine(*this->edge_middle, middle_fit_line, DIST_L2, 0, 0.01, 0.01);
  double middle_line_k = middle_fit_line[1] / middle_fit_line[0];
  // std::cout<<middle_line_k<<std::endl;
  // std::cout<<middle_fit_line[2]<<"  "<<middle_fit_line[3]<<std::endl;
  // middle_line_k =(left_line_k+right_line_k)/2;
  double step_middle = 40;
  cv::Point2i middle_line_point_1(middle_fit_line[2] - step_middle, middle_fit_line[3] - middle_line_k * step_middle);
  cv::Point2i middle_line_point_2(middle_fit_line[2] + step_middle, middle_line_k * step_middle + middle_fit_line[3]);
  cv::line(temp, middle_line_point_1, middle_line_point_2, Scalar(0, 255, 0), 4);
  // // 展示拟合中线
  // imshow("mid_line&fit_line", temp);
  // waitKey(0);

  // 画出真正的边缘线
  for (auto point : *this->edge_up)
  {
    temp.at<Vec3b>(point.y, point.x)[0] = 255;
    temp.at<Vec3b>(point.y, point.x)[1] = 255;
    temp.at<Vec3b>(point.y, point.x)[2] = 255;
  }
  for (auto point : *this->edge_down)
  {
    temp.at<Vec3b>(point.y, point.x)[0] = 255;
    temp.at<Vec3b>(point.y, point.x)[1] = 255;
    temp.at<Vec3b>(point.y, point.x)[2] = 255;
  }

  for (auto point : *this->edge_middle)
  {
    temp.at<Vec3b>(point.y, point.x)[0] = 255;
    temp.at<Vec3b>(point.y, point.x)[1] = 255;
    temp.at<Vec3b>(point.y, point.x)[2] = 255;
  }
  // 展示拟合中线
  imshow("mid_line&fit_line", temp);
  waitKey(1);

  double degree = atan(middle_line_k) * 180 / CV_PI; // 输出在-90 和 90 之间
  // if (degree < 0)
  // {
  //   degree = 90 - abs(degree);
  // }
  // else
  // {
  //   degree = -(90 - abs(degree));
  // }
  // std::cout<<degree<<std::endl;

  Point2f center = Point2f(finger_preprocessing.rows / 2, finger_preprocessing.cols / 2);
  Mat martix = getRotationMatrix2D(center, degree, 1); // 得到仿射矩阵  k_line2/CV_PI*180 弧度转角度

  warpAffine(this->finger_preprocessing, this->finger_rotate, martix, finger_preprocessing.size());
  // imshow("finger",this->finger_preprocessing);
  // waitKey(1);
  // imshow("finger_rotate", this->finger_rotate);
  // waitKey(1);
}
