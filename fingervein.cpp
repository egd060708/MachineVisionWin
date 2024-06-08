#include "iostream"
#include "opencv2/opencv.hpp"
#include "Finger.h"

using namespace std;
using namespace cv;

int main()
{
  Mat finger_src_1 = imread("../data/Fingers/002_3/02.jpg");
  if (finger_src_1.empty() == 1)
  {
    cout << "no image load";
  }
  Finger finger_1(finger_src_1);

  Mat finger_src_2 = imread("../data/Fingers/002_2/01.jpg");
  if (finger_src_2.empty() == 1)
  {
    cout << "no image load";
  }
  Finger finger_2(finger_src_2);

  finger_1.preprocessing();
  finger_1.find_finger_edge();
  finger_1.rotate_finger();
  finger_1.find_knuckle();
  finger_1.enhance_finger_vein();
  finger_1.spilt_finger_vein();

  // 展示原图
  finger_2.preprocessing();
  finger_2.find_finger_edge();
  finger_2.rotate_finger();
  finger_2.find_knuckle();
  finger_2.enhance_finger_vein();
  finger_2.spilt_finger_vein();

  // 两张图匹配 ；
  Mat img1 = finger_1.get_finger_vein_split().clone();
  Mat img2 = finger_2.get_finger_vein_split().clone();
  double score = finger_match(img1, img2);
  cout << "score: " << score;
}