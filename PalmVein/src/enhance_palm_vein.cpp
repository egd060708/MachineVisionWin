#include "Palm.h"

// 定义一个滚动条函数
// calhe函数参数调整代码 测试发现 size2 尽可能大  size1 小一点  clioLimit大概20【8bit图】少一点点即可。
int clioLimit = 5584; // 32bit图 大一点
int size_1 = 5;		  // size 设置成五恰好吧
int size_2 = 23;	  // cliomit高的时候 ，size2需要设置的小一些 50下降到45吧 //调整到27可以保留横向和纵向的静脉
Mat temp_CLAHE;
void on_Trackbar_CLAHE(int, void *)
{

	Mat temp = temp_CLAHE.clone();
	auto cla = cv::createCLAHE(clioLimit, Size(size_1, size_2));
	cla->apply(temp, temp);
	cout << "clioLimit" << clioLimit << endl;
	cout << "size1" << size_1 << endl;
	cout << "size2" << size_2 << endl;
	imshow("CLA-TRACKER", temp);
	waitKey(0);
	return;
}

// 滚动条函数
// frangi函数参数调整代码 参数初始化为默认数值 参数的意义看源代码
int sigma_start = 3;	// 3&4是理想的参数
int sigma_end = 5;		// 4 & 5 是理想的参数
int sigma_step = 3;		// 1 & 2 & 3 都可以 , 但是 3可以保留静脉形状的更多信息
int BetaOne_int = 16;	// 分辨率0。1
int BetaTwo_int = 6;	// 分辨率0.01
float BetaOne = 2.0;	// 我挺喜欢1.6的
float BetaTwo = 0.06;	// 0.06是不错的数字
bool BlackWhite = true; //
Mat temp_frangi_input;
void on_Trackbar_Frangi(int, void *)
{
	// 临时的 操作核心
	frangi2d_opts_t temp_opts;
	BetaOne = float(BetaOne_int) / 10.0;
	BetaTwo = float(BetaTwo_int) / 100.0;
	frangi2d_createopts_custom(&temp_opts, sigma_start, sigma_end, sigma_step, BetaOne, BetaTwo, BlackWhite);

	Mat temp = temp_frangi_input.clone(); // temp是输入的图片
	Mat temp_vesselness, temp_scale, temp_angles;

	frangi2d(temp, temp_vesselness, temp_scale, temp_angles, temp_opts);

	temp_vesselness.convertTo(temp_vesselness, CV_8UC1, 255);
	//  temp_vesselness.convertTo(temp_vesselness, CV_16UC1, 256*256-1);

	cout << "sigma_start" << sigma_start << endl;
	cout << "sigma_end" << sigma_end << endl;
	cout << "sigma_step" << sigma_step << endl;
	cout << "BetaOne" << BetaOne << endl;
	cout << "BetaTwo" << BetaTwo << endl;

	imshow("Frangi", temp_vesselness);
	waitKey(0);
	return;
}

// 联合调节滚动条函数
Mat temp16bit_backup;
Mat img1;
void on_Trackbar_CLAHE_FRANGI(int, void *)
{
	// 临时的 操作核心
	Mat temp = temp16bit_backup.clone(); // temp是输入的图片
	auto cla = cv::createCLAHE(clioLimit, Size(size_1, size_2));
	cla->apply(temp, temp);
	imshow("CLA-TRACKER", temp);
	waitKey(0);

	// 转32位
	cv::Mat temp32bit;
	temp.convertTo(temp32bit, CV_32F, 1.0 / (256 * 256 - 1));
	BetaOne = float(BetaOne_int) / 10.0;
	BetaTwo = float(BetaTwo_int) / 100.0;
	frangi2d_opts_t temp_opts;
	frangi2d_createopts_custom(&temp_opts, sigma_start, sigma_end, sigma_step, BetaOne, BetaTwo, BlackWhite);
	Mat temp_vesselness, temp_scale, temp_angles;
	frangi2d(temp32bit, temp_vesselness, temp_scale, temp_angles, temp_opts);
	temp_vesselness.convertTo(temp_vesselness, CV_8UC1, 255);

	cout << "clioLimit" << clioLimit << endl;
	cout << "size_1" << size_1 << endl;
	cout << "size_2" << size_2 << endl;
	cout << "sigma_start" << sigma_start << endl;
	cout << "sigma_end" << sigma_end << endl;
	cout << "BetaOne" << BetaOne << endl;
	cout << "BetaTwo" << BetaTwo << endl;

	img1 = temp_vesselness.clone();

	// cv::threshold(temp_vesselness,temp_vesselness ,20,255,THRESH_OTSU) ;
	imshow("CLAHEFRANGI", temp_vesselness);
	waitKey(0);
	return;
}

int thresh = 10;
// 二值化操作
void on_Trackbar_threshold(int, void *)
{
	// 临时的 操作核心
	cv::threshold(img1, img1, thresh, 255, THRESH_BINARY);

	cout << "thresh" << thresh << endl;
	imshow("thresh", img1);
	waitKey(0);
	return;
}

/**
 * @brief 静脉纹理增强
 */
void Palm::enhance_palm_vein()
{
	this->palm_vein_enhance = this->palm_roi.clone(); // 复制

	// finger从bgr转换成灰度图，再从8bit转换成16bit，提高精度，让静脉增强效果更好，参数更细致
	Mat temp16bit;
	cv::cvtColor(this->palm_vein_enhance, temp16bit, COLOR_BGR2GRAY);
	temp16bit.convertTo(temp16bit, CV_16U, 256, 0); // 8bit->16bit 增大8位 放大256
	temp16bit_backup = temp16bit.clone();

	// 此注释用于滚动条调节 CLAHE 函数的若干个参数 寻找合适参数
	// 下面是滚动条 用于寻找alche算法的三个参数
	// clahe 使用4800 差不多的
	// temp_CLAHE=temp16bit.clone() ;
	// namedWindow("CLA-TRACKER", WINDOW_AUTOSIZE ) ;
	// createTrackbar("clioLimit", "CLA-TRACKER", &clioLimit, 7000, on_Trackbar_CLAHE);
	// createTrackbar("size_1", "CLA-TRACKER", &size_1, 100, on_Trackbar_CLAHE);
	// createTrackbar("size_2", "CLA-TRACKER", &size_2, 100, on_Trackbar_CLAHE);
	// on_Trackbar_CLAHE(clioLimit, 0);

	// 使用CLAHE算法进行直方图均衡化
	auto cla = cv::createCLAHE(5584, Size(5, 23));
	cla->apply(temp16bit, temp16bit);
	// imshow("CLA-TRACKER", temp16bit);
	// waitKey(1);

	// 16bit转32F归一化到0-1之间
	cv::Mat temp32bit_fl;
	temp16bit.convertTo(temp32bit_fl, CV_32F, 1.0 / (256 * 256 - 1), 0);
	// imshow("32bit", temp32bit_fl);
	// waitKey(1);

	/* 注释的代码段用于调整frangi滤波函数的参数，使用默认参数设定Frangi */
	// namedWindow("Frangi", WINDOW_AUTOSIZE);
	// temp_frangi_input = temp32bit_fl.clone();
	// createTrackbar("SIGMA_START", "Frangi", &sigma_start, 20, on_Trackbar_Frangi);
	// createTrackbar("SIGMA_END", "Frangi", &sigma_end, 20, on_Trackbar_Frangi);
	// createTrackbar("SIGMA_STEP", "Frangi", &sigma_step, 20, on_Trackbar_Frangi);
	// //不能输入float变量
	// createTrackbar("BETA_ONE", "Frangi", &BetaOne_int, 100, on_Trackbar_Frangi);
	// createTrackbar("BETA_TWO", "Frangi", &BetaTwo_int, 100, on_Trackbar_Frangi);
	// createTrackbar("BLACKWHITE", "Frangi", &BlackWhite, 1, on_Trackbar_Frangi);
	// on_Trackbar_Frangi(0, 0);

	/* 此处代码用于CALHE 和 Frangi 参数联调 主要调节climit参数 */
	// namedWindow("CLAHEFRANGI", WINDOW_AUTOSIZE);
	// createTrackbar("clioLimit", "CLAHEFRANGI", &clioLimit, 28000, on_Trackbar_CLAHE_FRANGI);
	// createTrackbar("size_1", "CLAHEFRANGI", &size_1, 200, on_Trackbar_CLAHE_FRANGI);
	// createTrackbar("size_2", "CLAHEFRANGI", &size_2, 200, on_Trackbar_CLAHE_FRANGI);
	// createTrackbar("SIGMA_START", "CLAHEFRANGI", &sigma_start, 20, on_Trackbar_CLAHE_FRANGI);
	// createTrackbar("SIGMA_END", "CLAHEFRANGI", &sigma_end, 20, on_Trackbar_CLAHE_FRANGI);
	// createTrackbar("SIGMA_STEP", "CLAHEFRANGI", &sigma_step, 20, on_Trackbar_CLAHE_FRANGI);
	// createTrackbar("BETA_ONE", "CLAHEFRANGI", &BetaOne_int, 100, on_Trackbar_CLAHE_FRANGI);
	// createTrackbar("BETA_TWO", "CLAHEFRANGI", &BetaTwo_int, 100, on_Trackbar_CLAHE_FRANGI);
	// createTrackbar("THRESH", "thresh", &thresh, 255, on_Trackbar_threshold);
	// on_Trackbar_CLAHE_FRANGI(0, 0);

	// 利用滤波函数处理32bit图像，并最后生成8bit图，存在finger_vein_enhance中
	{
		Mat vesselness, scale, angles;
		frangi2d_opts_t opts;
		frangi2d_createopts_custom(&opts, 3, 5, 3, 2.0, 0.06, true); // frangi滤波参数设置
		frangi2d(temp32bit_fl, vesselness, scale, angles, opts); // 进行frangi滤波
		// 显示结果
		// cout << "flag: " << vesselness.flags << endl;
		// cout << "channels: " << vesselness.channels() << endl;;
		vesselness.convertTo(this->palm_vein_enhance, CV_8UC1, 255);
		// scale.convertTo(scale, CV_8UC1, 255);
		// angles.convertTo(angles, CV_8UC1, 255);
		imshow("finger_vein_enhance", this->palm_vein_enhance);
		waitKey(1);
	}
}
