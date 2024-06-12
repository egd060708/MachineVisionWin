#include "Finger.h"
/**
 * @brief ③根据已检测的手指边缘确定ROI区域上下边界，
 * 确定手指关节位置（由于手指的组织结构，手指关节处往往亮度比较高）
 * 根据手指关节位置确定ROI区域左右边界，获得ROI区域。参考实验步骤如图2。
 */
void Finger::find_knuckle()
{
	this->finger_roi = this->finger_rotate.clone();

	// 左右收缩
	// Mat temp = finger_roi.rowRange(static_cast<int>(finger_roi.rows * 0.05), static_cast<int>(finger_roi.rows * 0.95)).clone();
	Mat temp;
  	temp = finger_roi.rowRange(static_cast<int>(finger_roi.rows * 0.18), static_cast<int>(finger_roi.rows * 0.92)).clone();
  	temp = temp.colRange(static_cast<int>(temp.cols * 0.1),static_cast<int>(temp.cols * 0.99)).clone();
	find_finger_edge(this->finger_roi,0.18,0.91,0.1,0.99);
	// imshow("ori",finger_roi);
	// waitKey(1);
	// imshow("temp",temp);
	// waitKey(0);
	// 上下收缩
	int cod_y_down;
	{
		vector<int> edge_down_y;
		for (auto &point : *this->edge_down)
		{
			edge_down_y.emplace_back(point.y);
		}
		cod_y_down = *(std::min_element(edge_down_y.begin(), edge_down_y.end()));
	}

	int cod_y_up;
	{
		vector<int> edge_up_y;
		for (auto &point : *this->edge_up)
		{
			edge_up_y.emplace_back(point.y);
		}
		cod_y_up = *(std::max_element(edge_up_y.begin(), edge_up_y.end()));
	}
	// // 由于手指边缘干扰较多，多往内截取一部分
	// cod_y_up += 15;
	// cod_y_down -= 15;
	// 创建保存一个不画线的
	Mat temp1 = temp.clone();
	line(temp, Point2i(0, cod_y_up), Point2i(temp.cols - 1,cod_y_up), Scalar(0, 255, 0));
	line(temp, Point2i(0, cod_y_down), Point2i(temp.cols - 1, cod_y_down), Scalar(0, 255, 0));
	imshow("finger_roi_get", temp);
	waitKey(1);
	// 截取出最终选定区域
	this->finger_roi = temp1.rowRange(static_cast<int>(cod_y_up), static_cast<int>(cod_y_down)).clone();
	// this->finger_roi = this->finger_roi.colRange(static_cast<int>(finger_roi.cols * 0.1),static_cast<int>(finger_roi.cols * 0.92)).clone();
	// imshow("finger_roi_true", this->finger_roi);
	// waitKey(1);

	// 接下来在 手指图中寻找到两个亮的地方 找到关节
	vector<uint64_t> windows_value;
	vector<int> coordinate;
	Mat finger_roi_grey_tmp;
	Mat finger_roi_gray;

	// 转为灰度图（由于某些图右侧指关节没有明显亮度增强，因此需要增加灰度图像的对比度）
	cvtColor(this->finger_roi, finger_roi_grey_tmp, COLOR_BGR2GRAY);
	{
		// imshow("finger_roi_gray_tmp", finger_roi_grey_tmp);
		// waitKey(1);
		// 直方图均衡化
		cv::equalizeHist(finger_roi_grey_tmp, finger_roi_gray);
		// imshow("finger_roi_gray", finger_roi_gray);
		// waitKey(1);
	}

	for (int col = 10; col < finger_roi_gray.cols - 11; col++)
	{
		uint64_t pixel_sum_value = 0;						   // 初始化像素值为 0
		for (int col_w = col - 10; col_w <= col + 10; col_w++) // 扫描每一列上下10个像素的领域
		{
			for (int row = 0; row < finger_roi_gray.rows - 1; row++)
			{
				pixel_sum_value += finger_roi_gray.ptr<uchar>(row)[col_w]; // 记录下整个区域内的像素和
			}
		}
		windows_value.emplace_back(pixel_sum_value); //  ##将找到的像素值存起来
		coordinate.emplace_back(col);				 //  ##对应的中心行也存起来
	}

	vector<uint64_t> peak; // 存放极大值点
	vector<int> pin;	   // 用于存放极大值点的下标

	int field = 100; // 用于判断极大值点的领域大小
	// 寻找极大值点，当极大值点的数量>2时，扩大领域大小，重新寻找
	while(1)
	{
		for (int i = 0; i < windows_value.size(); ++i)
		{
			// 检查当前点是否为极大值点
			bool isMaxima = true;
			for (int j = i - field; j <= i + field; ++j)
			{
				int temp_j = j;
				// 处理边缘邻域溢出情况
				if (temp_j < 0)
					temp_j += windows_value.size();
				if (temp_j >= windows_value.size())
					temp_j -= windows_value.size();

				if (temp_j != i && windows_value[i] < windows_value[temp_j])
				{
					isMaxima = false;
					break;
				}
			}

			// 如果是极大值点，将其索引添加到输出数组
			if (isMaxima)
			{
				peak.push_back(windows_value[i]);
				pin.push_back(coordinate[i]);
			}
		}

		if(peak.size() <= 2)
			break;
		else if(peak.size() > 2)
		{
			peak.clear();
			pin.clear();

			field += 20;
			continue;
		}
	};
	// 截取到两个极大值，然后分割出最后的区域
	if(peak.size() == 2){
		Mat temp2 = this->finger_roi.clone();
		for (auto col : pin)
		{
			line(temp2, Point2i(col, 0), Point2i(col, temp2.rows - 1), Scalar(255, 0, 0));
		}
		imshow("temp2", temp2);
		waitKey(1);
		this->finger_roi = this->finger_roi.colRange(std::min(pin[0], pin[1]), std::max(pin[0], pin[1])).clone();
		// imshow("finger_roi", this->finger_roi);
		// waitKey(1);
	}
	else{
		Mat temp2 = this->finger_roi.clone();
		for (auto col : pin)
		{
			line(temp2, Point2i(col, 0), Point2i(col, temp2.rows - 1), Scalar(255, 0, 0));
			line(temp2, Point2i(temp2.cols - 1 - static_cast<int>(0.5*col), 0), Point2i(temp2.cols - 1 - static_cast<int>(0.5*col), temp2.rows - 1), Scalar(255, 0, 0));
		}
		imshow("temp2", temp2);
		waitKey(1);
		this->finger_roi = this->finger_roi.colRange(std::min(pin[0], temp2.cols - 1 - static_cast<int>(0.5*pin[0])), std::max(pin[0], temp2.cols - 1 - static_cast<int>(0.5*pin[0]))).clone();
		// imshow("finger_roi", this->finger_roi);
		// waitKey(1);
	}

	
}
