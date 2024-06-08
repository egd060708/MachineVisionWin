#include "Hand.h"

//---------------- 展示处理过程中的图片------------
void Hand::show_hand_src()
{
  namedWindow("hand_src", WINDOW_AUTOSIZE);
  imshow("hand_src", this->hand_src);
  waitKey(0);
}

void Hand::show_hand_preprocessing()
{
  namedWindow("hand_preprocessing", WINDOW_AUTOSIZE);
  imshow("hand_preprocessing", this->hand_preprocessing);
  waitKey(0);
}

void Hand::show_hand_rotate()
{
  namedWindow("hand_rotate", WINDOW_AUTOSIZE);
  imshow("hand_rotate", this->hand_rotate);
}

void Hand::show_hand_roi()
{
  namedWindow("hand_roi", WINDOW_AUTOSIZE);
  imshow("hand_roi", this->hand_roi);
}

void Hand::show_hand_vein_enhance()
{
  namedWindow("hand_vein_enhance", WINDOW_AUTOSIZE);
  imshow("hand_vein_enhance", this->hand_vein_enhance);
}

void Hand::show_hand_vein_split()
{
  namedWindow("hand_vein_split", WINDOW_AUTOSIZE);
  imshow("hand_vein_split", this->hand_vein_split);
}
