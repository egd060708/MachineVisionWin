#include "Finger.h"

void Finger::rotate_finger()
{

  Mat temp = Mat::zeros(finger_preprocessing.size(), CV_8UC3);
  /*
    Vec<float, 4> left_fit_line;
    Vec<float, 4> right_fit_line;

    {//左边的直线拟合
      cv::fitLine(this->edge_left, left_fit_line, DIST_L12, 0, 0.01, 0.01);
      //cv::line(temp, left_fit_line.front(), left_fit_line.back(), Scalar(0, 255, 0));
      double left_line_k = left_fit_line[1] / left_fit_line[0];
      double step_left = 40;

      cv::line(temp,
               cv::Point2i(left_fit_line[2] - step_left, left_fit_line[3] - left_line_k * step_left),
               cv::Point2i(left_fit_line[2] + step_left, left_line_k * step_left + left_fit_line[3]),
               Scalar(255, 0, 0), 4);
    }

    {//右边的直线拟合
      cv::fitLine(this->edge_right, right_fit_line, DIST_L12, 0, 0.01, 0.01);

      //cv::line(temp, right_fit_line.front(), right_fit_line.back(), Scalar(0, 255, 0));
      double right_line_k = right_fit_line[1] / right_fit_line[0];
      double step_right = 40;

      cv::line(temp,
               cv::Point2i(right_fit_line[2] - step_right, right_fit_line[3] - right_line_k * step_right),
               cv::Point2i(right_fit_line[2] + step_right, right_line_k * step_right + right_fit_line[3]),
               Scalar(255, 0, 0), 4);

    }*/

  Vec<float, 4> middle_fit_line;
  // 别的方法 拟合出来的直线 角度是一样的， 距离有些不同罢了 没关系 所以选择L2计算快一点;
  cv::fitLine(this->edge_middle, middle_fit_line, DIST_L2, 0, 0.01, 0.01);
  double middle_line_k = middle_fit_line[1] / middle_fit_line[0];
  // middle_line_k =(left_line_k+right_line_k)/2;
  double step_middle = 40;
  cv::Point2i middle_line_point_1(middle_fit_line[2] - step_middle, middle_fit_line[3] - middle_line_k * step_middle);
  cv::Point2i middle_line_point_2(middle_fit_line[2] + step_middle, middle_line_k * step_middle + middle_fit_line[3]);
  cv::line(temp, middle_line_point_1, middle_line_point_2, Scalar(0, 255, 0), 4);

  // 画出真正的边缘线
  for (auto point : this->edge_left)
  {
    temp.at<Vec3b>(point.y, point.x)[0] = 255;
    temp.at<Vec3b>(point.y, point.x)[1] = 255;
    temp.at<Vec3b>(point.y, point.x)[2] = 255;
  }
  for (auto point : this->edge_right)
  {
    temp.at<Vec3b>(point.y, point.x)[0] = 255;
    temp.at<Vec3b>(point.y, point.x)[1] = 255;
    temp.at<Vec3b>(point.y, point.x)[2] = 255;
  }

  for (auto point : this->edge_middle)
  {
    temp.at<Vec3b>(point.y, point.x)[0] = 255;
    temp.at<Vec3b>(point.y, point.x)[1] = 255;
    temp.at<Vec3b>(point.y, point.x)[2] = 255;
  }
  // 展示拟合中线
  imshow("mid_line&fit_line", temp);
  waitKey(1);

  double degree = atan(middle_line_k) * 180 / CV_PI; // 输出在-90 和 90 之间
  if (degree < 0)
  {
    degree = 90 - abs(degree);
  }
  else
  {
    degree = -(90 - abs(degree));
  }

  Point2f center = Point2f(finger_preprocessing.rows / 2, finger_preprocessing.cols / 2);
  Mat martix = getRotationMatrix2D(center, degree, 1); // 得到仿射矩阵  k_line2/CV_PI*180 弧度转角度

  warpAffine(this->finger_preprocessing, this->finger_rotate, martix, finger_preprocessing.size());
  imshow("finger_rotate", this->finger_rotate);
  waitKey(1);
}
