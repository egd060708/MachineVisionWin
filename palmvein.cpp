#include "iostream"
#include "opencv2/opencv.hpp"
#include "Palm.h"
#include "opencv2/plot.hpp"

using namespace std;
using namespace cv;

int main()
{
  // 定义图像匹配的平均分数
  float mean_score = 0;
  uint32_t cnt = 0;
  vector<float> temp_scores;
  vector<float> temp_cnt;
  // 从数据目录读取图片
  for (int type = 73; type <= 73; type++)
  {
    vector<Mat> palm_src;
    vector<Palm> palms;

    for (int i = 1; i <= 30; i++)
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
    mat_x.at<float>(0, i) = temp_cnt[i];
    mat_y.at<float>(0, i) = temp_scores[i];
  }
  Mat plot_result;

  Ptr<plot::Plot2d> plot = plot::Plot2d::create(mat_x, mat_y);
  plot->render(plot_result);
  imshow("plot 2d data in default way!", plot_result);
  // 自定义参数
  plot->setShowText(false);
  plot->setShowGrid(false);
  plot->setPlotBackgroundColor(Scalar(255, 200, 200));
  plot->setPlotLineColor(Scalar(255, 0, 0));
  plot->setPlotLineWidth(2);
  plot->setInvertOrientation(true); // 左右颠倒绘制
  plot->render(plot_result);        // 根据参数进行渲染

  imshow("The plot rendered with some of custom visualization options", plot_result);
  waitKey(0);
  system("pause");
  return 0;
}