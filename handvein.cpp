#include "iostream"
#include "opencv2/opencv.hpp"
#include "Hand.h"

using namespace std;
using namespace cv;

int main()
{
  float mean_score = 0;
  uint32_t cnt = 0;
  for (int type = 60; type <= 70; type++)
  {
    vector<Mat> hand_src;
    vector<Hand> hands;

    //hand_src.push_back(Mat(imread("../data/Hands/67/67_2.bmp")));

    for (int i = 1; i <= 10; i++)
    {
      char temp[100];
      sprintf(temp, "../data/Hands/%d/%d_%d.bmp", type, type, i);
      hand_src.push_back(Mat(imread(temp)));
    }

    for (int i = 0; i < hand_src.size(); i++)
    {
      if(hand_src[i].cols > hand_src[i].rows)
        resize(hand_src[i], hand_src[i], Size(640, 480));
      else
        resize(hand_src[i], hand_src[i], Size(480, 640));

      hands.push_back(Hand(hand_src[i]));
      hands[i].hand_roi_process();
      hands[i].enhance_hand_vein();
      hands[i].spilt_hand_vein();
    }

    int success_sum = 0;
    vector<vector<float>> scores;
    for (int i = 0; i < hands.size(); i++)
    {
      vector<float> temp_scores;
      for (int j = 0; j < hands.size(); j++)
      {
        Mat img1 = hands[i].get_hand_vein_split().clone();
        Mat img2 = hands[j].get_hand_vein_split().clone();
        double score = hand_match(img1, img2);
        mean_score += score;
        cnt++;
        temp_scores.push_back(score);
        if (score > 0.16)
          success_sum++;
      }
      scores.push_back(temp_scores);
    }

    cout << type <<" match rate: " << (float)success_sum / (hands.size() * hands.size()) << endl;
  }
  mean_score /= cnt;
  cout << "mean_score: " << mean_score << endl;
}