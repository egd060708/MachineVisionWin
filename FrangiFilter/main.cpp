#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <vector>
#include "include/frangi.h"
using namespace std;
using namespace cv;

int main(int argc, char *argv[]) {
	//使用默认参数设定Frangi
	frangi2d_opts_t opts;
	frangi2d_createopts(&opts);

	//读取图片为单通道，进行处理
	Mat input_img = imread("51.jpg", 0);
	Mat input_img_fl;

    //转换浮点
	input_img.convertTo(input_img_fl, CV_32FC1);
    cout<<input_img.row(0) <<endl ;
    cout<<input_img_fl.row(0) <<endl ;

    //进行处理
	Mat vesselness, scale, angles;
	frangi2d(input_img_fl, vesselness, scale, angles, opts);
	//显示结果
  cout<<vesselness.row(0) <<endl ;
	vesselness.convertTo(vesselness, CV_8UC1, 255);
  cout<<vesselness.row(0) <<endl ;
	scale.convertTo(scale, CV_8UC1, 255);
	angles.convertTo(angles, CV_8UC1, 255);
	imshow("result", vesselness);
    waitKey(0);
	 
}
