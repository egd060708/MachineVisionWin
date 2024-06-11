#include "Finger.h"

//---------------- 展示处理过程中的图片------------
void Finger::show_finger_src() {

  namedWindow("finger_src", WINDOW_AUTOSIZE);
  imshow("finger_src", this->finger_src);
  waitKey(0);
}
void Finger::show_finger_preprocessing() {

  namedWindow("finger_preprocessing", WINDOW_AUTOSIZE);
  imshow("finger_preprocessing", this->finger_preprocessing);
  waitKey(0);

}
void Finger::show_finger_rotate() {

  namedWindow("finger_rotate", WINDOW_AUTOSIZE);
  imshow("finger_rotate", this->finger_rotate);

}
void Finger::show_finger_roi() {
  namedWindow("finger_roi", WINDOW_AUTOSIZE);
  imshow("finger_roi", this->finger_roi);
}

void Finger::show_finger_vein_enhance() {
  namedWindow("finger_vein_enhance", WINDOW_AUTOSIZE);
  imshow("finger_vein_enhance", this->finger_vein_enhance);
}
void Finger::show_finger_vein_split() {
  namedWindow("finger_vein_split", WINDOW_AUTOSIZE);
  imshow("finger_vein_split", this->finger_vein_split);
}
