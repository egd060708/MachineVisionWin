#include "Finger.h"
void Finger::find_finger_edge()
{

  Mat edge_y;
  // 使用sobel算子边缘提取且只运算x方向上的梯度
  cv::Sobel(this->finger_preprocessing, edge_y, CV_16S, 0, 1, 1, 30);
  convertScaleAbs(edge_y, edge_y); // 得到梯度图
  // 二值化处理
  cv::threshold(edge_y, edge_y, 200, 255, THRESH_BINARY);
  // 截取图片中间的位置取得更好的边缘
  Mat temp;
  temp = edge_y.rowRange(static_cast<int>(edge_y.rows * 0.18), static_cast<int>(edge_y.rows * 0.945)).clone();
  temp = temp.colRange(static_cast<int>(temp.cols * 0.1),static_cast<int>(temp.cols * 0.92)).clone();

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
  // 寻找上边缘线
  for (int i = 0; i < temp_binary.cols; ++i)
  {
    for (int j = 0; j < temp_binary.rows / 2; ++j)
    {
      // 如果是白色的则检测为边缘
      uchar *point = temp_binary.ptr(j);
      if (static_cast<int>(*(point + i)) > 0)
      {
        // i 表示列 对应横坐标  ； j对应纵坐标
        this->edge_up.emplace_back(Point2i(i, j));
        break; // 退出本行的循环
      }
    }
  }
  // 下边的边缘线 从最下边向中间遍历
  for (int i = 0; i < temp_binary.cols; ++i)
  {
    for (int j = temp_binary.rows; j > temp_binary.rows / 2; --j)
    {
      uchar *point = temp_binary.ptr(j);
      if (static_cast<int>(*(point + i)) > 0)
      {
        // i 表示列 对应横坐标  ； j对应纵坐标
        edge_down.emplace_back(Point2i(i, j));
        break; // 退出本行的循环
      }
    }
  }
  // std::cout<<edge_up.size()<<"  "<<edge_down.size()<<std::endl;

  for (int i = 0; i < temp_binary.cols; ++i)
  {
    Point2i middle_point = (this->edge_up[i] + this->edge_down[i]) / 2;
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
