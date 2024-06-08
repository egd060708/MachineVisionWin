#include "Finger.h"

double finger_match(Mat &img1, Mat &img2)
{
	if (img1.size() != img2.size())
	{
		// 确定新尺寸
		int new_width = std::max(img1.cols, img2.cols);
		int new_height = std::max(img1.rows, img2.rows);

		// 调整img1和img2的尺寸
		if (img1.size() != cv::Size(new_width, new_height))
		{
			cv::resize(img1, img1, cv::Size(new_width, new_height), 0, 0, cv::INTER_NEAREST);
		}
		if (img2.size() != cv::Size(new_width, new_height))
		{
			cv::resize(img2, img2, cv::Size(new_width, new_height), 0, 0, cv::INTER_NEAREST);
		}
	}
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