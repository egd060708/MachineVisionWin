#include "Palm.h"

double palm_match(Mat &img1, Mat &img2)
{
	// 计算交集
	cv::Mat intersection;
	cv::bitwise_and(img1, img2, intersection);

	// 计算并集
	cv::Mat union_;
	cv::bitwise_or(img1, img2, union_);

	// 计数非零像素点（255值像素点）
	int count_intersection = cv::countNonZero(intersection);
	int count_union = cv::countNonZero(union_);

	double score = static_cast<double>(count_intersection) / count_union;
	return score;
}