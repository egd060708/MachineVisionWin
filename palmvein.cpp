#include "iostream"
#include "opencv2/opencv.hpp"
#include "Palm.h"
#include "opencv2/plot.hpp"
#include <string>

using namespace std;
using namespace cv;

#define PLOT_HEIGHT
#define PLOT_WIDTH

int main()
{
  // 定义图像匹配的平均分数
  float mean_score = 0;
  uint32_t cnt = 0;
  vector<float> temp_scores;
  vector<float> temp_cnt;
  // 从数据目录读取图片
  for (int type = 73; type <= 74; type++)
  {
    vector<Mat> palm_src;
    vector<Palm> palms;

    for (int i = 1; i <= 10; i++)
    {
      char temp[100];
      sprintf(temp, "../data/Palms/%d/%d_%d.bmp", type, type, i);
      palm_src.push_back(Mat(imread(temp)));
    }

    // 统一图片大小
    for (int i = 0; i < palm_src.size(); i++)
    {
      if (palm_src[i].cols > palm_src[i].rows)
        resize(palm_src[i], palm_src[i], Size(640, 480));
      else
        resize(palm_src[i], palm_src[i], Size(480, 640));

      palms.push_back(Palm(palm_src[i]));
      // 图像预处理
      palms[i].palm_roi_process();
      // 增强手掌静脉
      palms[i].enhance_palm_vein();
      // 分割手掌静脉纹理
      palms[i].spilt_palm_vein();
    }

    // 计算匹配度以及匹配成功次数
    int success_sum = 0;

    vector<float> match_rate;
    for (int i = 0; i < palms.size(); i++)
    {
      for (int j = 0; j < palms.size(); j++)
      {
        Mat img1 = palms[i].get_palm_vein_split().clone();
        Mat img2 = palms[j].get_palm_vein_split().clone();
        double score = palm_match(img1, img2);
        mean_score += score;
        temp_cnt.push_back(cnt);
        cnt++;
        temp_scores.push_back(score);
        if (score > 0.16)
          success_sum++;
      }
    }
    match_rate.push_back((float)success_sum / (palms.size() * palms.size()));
    cout << type << " match rate: " << match_rate[type] << endl;
  }
  mean_score /= cnt;
  cout << "mean_score: " << mean_score << endl;
  // 转换为opencv数据类型
  Mat mat_x(1, temp_cnt.size(), CV_64F);
  Mat mat_y(1, temp_scores.size(), CV_64F);
  for (int i = 0; i < temp_scores.size(); i++)
  {
    mat_x.at<double>(0, i) = temp_cnt[i];
    mat_y.at<double>(0, i) = -temp_scores[i];
    // cout << temp_cnt[i] << ":  " << temp_scores[i] << endl;
  }
  // 绘图基础参数配置
  int width = 800;
  int height = 600;
  double y_max = 1.2;
  double step = 0.1;

  // 创建Plot2d对象
  Ptr<plot::Plot2d> plot = plot::Plot2d::create(mat_x, mat_y);

  // 设置图表属性
  plot->setPlotSize(width,height);
  // plot->setShowGrid(true);
  // plot->setShowText(true);
  plot->setPlotBackgroundColor(Scalar(255, 255, 255)); // 白色背景
  plot->setPlotLineColor(Scalar(0, 0, 255));           // 蓝色线条
  plot->setPlotLineWidth(2);                           // 线条宽度
  plot->setPlotAxisColor(Scalar(0, 0, 0));
  plot->setMinY(-y_max); // Y轴最小值
  plot->setMaxY(0);      // Y轴最大值
  plot->setMinX(0);
  plot->setMaxX(temp_scores.size());

  // 绘制图表并显示(相当于把plot的配置数据打包成一个矩阵)
  Mat plot_result;
  plot->render(plot_result);
  int devide_num = int(y_max*10) / int(step*10);
  // 添加图表标题和坐标轴标签
  putText(plot_result, "Score Line", Point(50, 30), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 255), 1.5);
  for (int i = 1; i <= (devide_num - 1); i++)
  {
    putText(plot_result, "-", Point(0, height - 1 - i * height / devide_num + 0.005 * height), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 0), 1);
    putText(plot_result, to_string(i * step), Point(10, height - 1 - i * height / devide_num + 0.005 * height), FONT_HERSHEY_PLAIN, 1, Scalar(0, 0, 0), 1);
  }

  // 显示图表
  imshow("Plot", plot_result);
  waitKey(0);
  system("pause");
  return 0;
}