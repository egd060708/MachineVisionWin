#include "Palm.h"

double calculateDistance(Point a, Point b)
{
	double dx = a.x - b.x;
	double dy = a.y - b.y;

	// 使用欧氏距离公式计算距离
	double distance = std::sqrt(dx * dx + dy * dy);

	return distance;
}

int thresh_threshold = 1;
Mat temp_binary_roi;
void on_Trackbar_THRESH_BINARY_roi(int, void *)
{
	Mat temp;
	cv::threshold(temp_binary_roi, temp, thresh_threshold, 255, THRESH_BINARY);
	cout << "thresh_threshold_split" << thresh_threshold << endl;
	imshow("THRESH_BINARY", temp);
}

void Palm::palm_roi_process()
{
	// 转灰度图
	Mat temp_roi;
	cvtColor(this->palm_src, temp_roi, COLOR_BGR2GRAY);
	cv::threshold(temp_roi, temp_roi, 39, 255, THRESH_BINARY);

	// 轮廓查找
	vector<vector<cv::Point2i>> contours;
	vector<Vec4i> hierarchy;
	findContours(temp_roi, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);

	// 找出面积最大的轮廓
	int max_contour_index = 0;
	{
		double max_area = 0;
		for (int i = 0; i < contours.size(); ++i)
		{
			auto contour = contours[i];
			double temp_area = contourArea(contour);
			if (temp_area > max_area)
			{
				max_area = temp_area;
				max_contour_index = i;
			}
		}
		temp_roi = 0;
		drawContours(temp_roi, contours, max_contour_index, Scalar(255), -1);
	}
	// imshow("src",palm_src);
	// waitKey(1);
	// imshow("temp_roi",temp_roi);
	// waitKey(0);

	Point palm_center;
	int maxdist = 0;
	// 寻找掌心，最大内切圆的中心，也就是距离圆轮廓最远的为掌心位置
	{
		int dist = 0;
		for (int i = 0; i < temp_roi.cols; i++)
		{
			for (int j = 0; j < temp_roi.rows; j++)
			{
				if (temp_roi.at<uint8_t>(j, i) == 0)
					continue;

				dist = pointPolygonTest(contours[max_contour_index], Point(i, j), true);
				if (dist > maxdist)
				{
					maxdist = dist;
					palm_center = Point(i, j);
				}
			}
		}
		Mat temp = temp_roi.clone();
		circle(temp, palm_center, maxdist, Scalar(0));
		imshow("CIRCLE", temp);
		waitKey(1);
	}

	// 手腕剔除
	{
		double cut_scale = 0.8;
		int row_end = maxdist * cut_scale + palm_center.y;
		temp_roi = temp_roi.rowRange(0, row_end).clone();
		// 定义结构元素
		cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(7, 7));
		// 开运算
		cv::morphologyEx(temp_roi, temp_roi, cv::MORPH_OPEN, kernel);
	}

	vector<cv::Point2i> target_contour;
	{
		findContours(temp_roi, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE);
		double max_area = 0;
		for (int i = 0; i < contours.size(); ++i)
		{
			auto contour = contours[i];
			double temp_area = contourArea(contour);
			if (temp_area > max_area)
			{
				max_area = temp_area;
				max_contour_index = i;
			}
		}
		target_contour = contours[max_contour_index];
	}

	// 找出参考点
	Point2i point_ref(0, temp_roi.rows - 1);
	{
		Point2i point_L(0, temp_roi.rows - 1), point_R(temp_roi.cols - 1, temp_roi.rows - 1);

		for (int i = 1; i < temp_roi.cols - 1; i++)
		{
			if (temp_roi.at<uint8_t>(temp_roi.rows - 1, i - 1) == 0 && temp_roi.at<uint8_t>(temp_roi.rows - 1, i) == 255)
			{
				point_L.x = i;
				break;
			}
		}

		for (int i = temp_roi.cols - 2; i > 0; i--)
		{
			if (temp_roi.at<uint8_t>(temp_roi.rows - 1, i) == 255 && temp_roi.at<uint8_t>(temp_roi.rows - 1, i + 1) == 0)
			{
				point_R.x = i;
				break;
			}
		}

		point_ref.x = (point_L.x + point_R.x) / 2;

		Mat temp_draw_defects = temp_roi.clone();
		cvtColor(temp_draw_defects, temp_draw_defects, COLOR_GRAY2BGR);
		circle(temp_draw_defects, point_ref, 6, Scalar(0, 0, 255), -1);
		circle(temp_draw_defects, point_L, 6, Scalar(255, 255, 0), -1);
		circle(temp_draw_defects, point_R, 6, Scalar(255, 255, 0), -1);
		imshow("point_ref", temp_draw_defects);
		waitKey(1);
	}

	// 找出指尖与指根
	vector<cv::Point2i> fingerTip, fingerRoot;
	{
		Mat temp_draw_defects = temp_roi.clone();
		cvtColor(temp_draw_defects, temp_draw_defects, COLOR_GRAY2BGR);

		// 算出所有轮廓点与参考点的直线距离
		vector<float> distances(target_contour.size());
		for (int i = 0; i < target_contour.size(); i++)
		{
			distances[i] = calculateDistance(target_contour[i], point_ref);
		}

		// 找出distances中的极值点，提取出指尖与指根
		const int field = 50; // 用于判断极值点的领域长度
		for (int i = 0; i < distances.size(); ++i)
		{
			if (target_contour[i].y >= 0.9 * temp_roi.rows)
				continue;

			// 检查当前点是否为极大值点
			bool isMaxima = true;
			bool isMinima = true;
			for (int j = i - field; j <= i + field; ++j)
			{
				int temp_j = j;
				if (temp_j < 0)
					temp_j += distances.size();
				if (temp_j >= distances.size())
					temp_j -= distances.size();

				if (temp_j != i && distances[i] < distances[temp_j])
				{
					isMaxima = false;
				}
				else if (temp_j != i && distances[i] > distances[temp_j])
				{
					isMinima = false;
				}

				if (isMaxima == false && isMinima == false)
					break;
			}

			// 如果是极大值点，将其索引添加到输出数组
			if (isMaxima)
			{
				fingerTip.push_back(target_contour[i]);
				circle(temp_draw_defects, target_contour[i], 6, Scalar(0, 0, 255), -1);
			}
			else if (isMinima)
			{
				fingerRoot.push_back(target_contour[i]);
				circle(temp_draw_defects, target_contour[i], 6, Scalar(0, 255, 0), -1);
			}
		}

		imshow("point_ref", temp_draw_defects);
		waitKey(1);
	}

	// 检查指根是否成功提取，并排除虎口的点
	{
		sort(fingerRoot.begin(), fingerRoot.end(),
			 [](Point2i point_1, Point2i point_2) -> bool
			 {
				 int x1 = point_1.x;
				 int x2 = point_2.x;
				 return x1 < x2;
			 });

		int i = 0;
		int size = fingerRoot.size();
		while (i < size - 1)
		{
			if (calculateDistance(fingerRoot[i], fingerRoot[i + 1]) < 35)
			{
				fingerRoot.erase(fingerRoot.begin() + i + 1);
				i--;
			}
			i++;
			size = fingerRoot.size();
		}

		if (fingerRoot.size() < 3)
		{
			cout << "detect fingerRoot fail " << fingerRoot.size() << endl;
			while (1)
			{
			}
		}
		else
		{
			// cout << "detect fingerRoot success " << endl;
			if (fingerRoot.size() == 4)
			{
				if (calculateDistance(fingerRoot[0], fingerRoot[1]) > calculateDistance(fingerRoot[2], fingerRoot[3]))
				{
					fingerRoot.erase(fingerRoot.begin());
				}
				else
				{
					fingerRoot.erase(fingerRoot.end());
				}
			}
		}
	}
	// 从原图中提取ROI
	{
		// 计算旋转角度
		double angle = std::atan2(fingerRoot[2].y - fingerRoot[0].y, fingerRoot[2].x - fingerRoot[0].x) * 180.0 / CV_PI;

		// 定义旋转矩阵
		cv::Mat rotationMatrix = cv::getRotationMatrix2D(fingerRoot[0], angle, 1.0);

		// 进行仿射变换
		Mat temp_img;
		cv::warpAffine(palm_src, temp_img, rotationMatrix, palm_src.size());
		// imshow("temp_img", temp_img);
		// waitKey(0);

		int width = calculateDistance(fingerRoot[0], fingerRoot[2]) * 1.4;
		int height = width;

		Point2i rect_org_point = fingerRoot[0];
		rect_org_point.x -= 0.15 * calculateDistance(fingerRoot[0], fingerRoot[2]);

		if (rect_org_point.x + width > temp_img.cols)
			width = height = temp_img.cols - rect_org_point.x;

		if (rect_org_point.y + height > temp_img.rows)
			width = height = temp_img.rows - rect_org_point.y;

		Rect palm_roi_rect(rect_org_point.x, rect_org_point.y, width, height);

		this->palm_roi = temp_img(palm_roi_rect).clone();
		resize(palm_roi, palm_roi, Size(240, 240));
		imshow("palm_roi_rect", this->palm_roi);
		waitKey(1);
	}
}
