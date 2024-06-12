#include "Finger.h"
void Finger::find_finger_edge(InputArray src, float cutScaleUp, float cutScaleDown, float cutScaleLeft, float cutScaleRight)
{
  edge_up = new vector<cv::Point2i>;
  edge_down = new vector<cv::Point2i>;
  edge_middle = new vector<cv::Point2i>;
  Mat edge_y;
  // 使用sobel算子边缘提取且只运算x方向上的梯度
  cv::Sobel(src, edge_y, CV_16S, 0, 1, 1, 30);
  convertScaleAbs(edge_y, edge_y); // 得到梯度图
  // 二值化处理
  cv::threshold(edge_y, edge_y, 200, 255, THRESH_BINARY);
  // 截取图片中间的位置取得更好的边缘
  Mat temp;
  temp = edge_y.rowRange(static_cast<int>(edge_y.rows * cutScaleUp), static_cast<int>(edge_y.rows * cutScaleDown)).clone();
  temp = temp.colRange(static_cast<int>(temp.cols * cutScaleLeft), static_cast<int>(temp.cols * cutScaleRight)).clone();

  // 私有的预处理图也同样截取图片
  // this->finger_preprocessing =finger_src.rowRange(static_cast<int>(edge_y.rows * 0.15), static_cast<int>(edge_y.rows * 0.85)).clone();

  // 将两条边界线 变粗 开运算
  Mat open_kernel = cv::getStructuringElement(MORPH_RECT, Size(3, 3));
  cv::morphologyEx(temp, temp, MORPH_OPEN, open_kernel);

  // 将两条边界线 变细 腐蚀
  Mat close_kernel = cv::getStructuringElement(MORPH_RECT, Size(3, 3));
  cv::morphologyEx(temp, temp, MORPH_ERODE, close_kernel);
  // 转为灰度图
  Mat temp_binary;
  cv::cvtColor(temp, temp_binary, COLOR_BGR2GRAY, 1);
  // std::cout<<temp_binary.cols<<" "<<temp_binary.rows<<std::endl;
  // imshow("edges", temp_binary);
  // waitKey(1);
  // 寻找上边缘线
  for (int i = 0; i < temp_binary.cols - 1; ++i)
  {
    bool is_check = false; // 是否能够检测到边缘
    for (int j = 0; j < temp_binary.rows / 2; ++j)
    {
      // 如果是白色的则检测为边缘
      uchar *point = temp_binary.ptr(j);
      if (static_cast<int>(*(point + i)) > 0)
      {
        // i 表示列 对应横坐标  ； j对应纵坐标
        edge_up->emplace_back(Point2i(i, j));
        is_check = true;
        break; // 退出本行的循环
      }
    }
    if (is_check == false)
    {
      // 如果没有检测到边缘，则认为边缘在整个图像的边缘
      edge_up->emplace_back(Point2i(i, 0));
    }
  }
  // 下边的边缘线 从最下边向中间遍历
  for (int i = 0; i < temp_binary.cols - 1; ++i)
  {
    bool is_check = false; // 是否能够检测到边缘
    for (int j = temp_binary.rows - 1; j > temp_binary.rows / 2; --j)
    {
      uchar *point = temp_binary.ptr(j);
      if (static_cast<int>(*(point + i)) > 0)
      {
        // i 表示列 对应横坐标  ； j对应纵坐标
        edge_down->emplace_back(Point2i(i, j));
        is_check = true;
        break; // 退出本行的循环
      }
    }
    if (is_check == false)
    {
      // 如果没有检测到边缘，则认为边缘在整个图像的边缘
      edge_down->emplace_back(Point2i(i, temp_binary.rows - 1));
    }
  }
  // std::cout<<edge_up.size()<<"  "<<edge_down.size()<<std::endl;

  for (int i = 0; i < temp_binary.cols - 1; ++i)
  {
    Point2i middle_point = (this->edge_up->at(i) + this->edge_down->at(i)) / 2;
    edge_middle->emplace_back(middle_point);
  }

  // Mat temp1 = Mat::zeros(temp.size(), CV_8UC3);
  // // 画图展示边缘
  // for (auto point : *this->edge_up)
  // {
  //   temp1.at<Vec3b>(point.y, point.x)[0] = 255;
  //   temp1.at<Vec3b>(point.y, point.x)[1] = 0;
  //   temp1.at<Vec3b>(point.y, point.x)[2] = 0;
  // }

  // for (auto point : *this->edge_down)
  // {
  //   temp1.at<Vec3b>(point.y, point.x)[0] = 0;
  //   temp1.at<Vec3b>(point.y, point.x)[1] = 255;
  //   temp1.at<Vec3b>(point.y, point.x)[2] = 0;
  // }
  // for (auto point : *this->edge_middle)
  // {
  //   temp1.at<Vec3b>(point.y, point.x)[0] = 0;
  //   temp1.at<Vec3b>(point.y, point.x)[1] = 0;
  //   temp1.at<Vec3b>(point.y, point.x)[2] = 255;
  // }
  // imshow("my_edge", temp1);
  // waitKey(1);
}
