#include "Palm.h"

//---------------- 展示处理过程中的图片------------
void Palm::show_palm_src()
{
  namedWindow("palm_src", WINDOW_AUTOSIZE);
  imshow("palm_src", this->palm_src);
  waitKey(0);
}

void Palm::show_palm_preprocessing()
{
  namedWindow("palm_preprocessing", WINDOW_AUTOSIZE);
  imshow("palm_preprocessing", this->palm_preprocessing);
  waitKey(0);
}

void Palm::show_palm_rotate()
{
  namedWindow("palm_rotate", WINDOW_AUTOSIZE);
  imshow("palm_rotate", this->palm_rotate);
}

void Palm::show_palm_roi()
{
  namedWindow("palm_roi", WINDOW_AUTOSIZE);
  imshow("palm_roi", this->palm_roi);
}

void Palm::show_palm_vein_enhance()
{
  namedWindow("palm_vein_enhance", WINDOW_AUTOSIZE);
  imshow("palm_vein_enhance", this->palm_vein_enhance);
}

void Palm::show_palm_vein_split()
{
  namedWindow("palm_vein_split", WINDOW_AUTOSIZE);
  imshow("palm_vein_split", this->palm_vein_split);
}
