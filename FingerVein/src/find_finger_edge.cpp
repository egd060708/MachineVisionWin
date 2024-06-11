#include "Finger.h"
void Finger::find_finger_edge()
{

  Mat edge_x;
  // 使用sobel算子边缘提取且只运算x方向上的梯度
  cv::Sobel(this->finger_preprocessing, edge_x, CV_16S, 1, 0, 1, 30);
  convertScaleAbs(edge_x, edge_x); // 得到梯度图
  // 二值化处理
  cv::threshold(edge_x, edge_x, 200, 255, THRESH_BINARY);
  // 截取图片中间的70% 取得更好的边缘
  Mat temp;
  temp = edge_x.rowRange(static_cast<int>(edge_x.rows * 0.15), static_cast<int>(edge_x.rows * 0.85)).clone();

  // 私有的预处理图也同样截取图片
  // this->finger_preprocessing =finger_src.rowRange(static_cast<int>(edge_x.rows * 0.15), static_cast<int>(edge_x.rows * 0.85)).clone();

  // 将两条边界线 变粗 开运算
  Mat open_kernel = cv::getStructuringElement(MORPH_RECT, Size(3, 3));
  cv::morphologyEx(temp, temp, MORPH_OPEN, open_kernel);

  // 将两条边界线 变细 腐蚀
  Mat close_kernel = cv::getStructuringElement(MORPH_RECT, Size(3, 3));
  cv::morphologyEx(temp, temp, MORPH_ERODE, close_kernel);

  Mat temp_binary;
  cv::cvtColor(temp, temp_binary, COLOR_BGR2GRAY, 1);

  // 寻找左边边缘线
  for (int i = 0; i < temp_binary.rows; ++i)
  {
    // 指针指向i行的首地址
    uchar *point = temp_binary.ptr(i);
    for (int j = 0; j < temp_binary.cols / 2; ++j)
    {
      if (static_cast<int>(*(point + j)) > 0)
      {
        // i 表示行 对应纵坐标  ； j对应横坐标
        this->edge_left.emplace_back(Point2i(j, i));
        break; // 退出本行的循环
      }
    }
  }
  // 右边的边缘线 从最右边向中间遍历
  for (int i = 0; i < temp_binary.rows; ++i)
  {
    // 第i行的首地址
    uchar *point = temp_binary.ptr(i);
    for (int j = temp_binary.cols; j > temp_binary.cols / 2; --j)
    {
      if (static_cast<int>(*(point + j)) > 0)
      {
        // i 表示行 对应纵坐标  ； j对应横坐标
        edge_right.emplace_back(Point2i(j, i));
        break; // 退出本行的循环
      }
    }
  }

  for (int i = 0; i < temp_binary.rows; ++i)
  {
    Point2i middle_point = (this->edge_right[i] + this->edge_left[i]) / 2;
    this->edge_middle.emplace_back(middle_point);
  }

  // 画图展示边缘
  //  for (auto point: this->edge_left) {
  //    temp.at<Vec3b>(point.y, point.x)[0] = 255;
  //    temp.at<Vec3b>(point.y, point.x)[1] = 0;
  //    temp.at<Vec3b>(point.y, point.x)[2] = 0;
  //  }
  //
  //  for (auto point: this->edge_right) {
  //    temp.at<Vec3b>(point.y, point.x)[0] = 0;
  //    temp.at<Vec3b>(point.y, point.x)[1] = 255;
  //    temp.at<Vec3b>(point.y, point.x)[2] = 0;
  //  }
  //  for (auto point: this->edge_middle) {
  //    temp.at<Vec3b>(point.y, point.x)[0] = 0;
  //    temp.at<Vec3b>(point.y, point.x)[1] = 0;
  //    temp.at<Vec3b>(point.y, point.x)[2] = 255;
  //  }
  //  imshow("edge_true", temp);
  //  waitKey(0);
}
