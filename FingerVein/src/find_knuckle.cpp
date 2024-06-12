#include "Finger.h"
/**
 * @brief ③根据已检测的手指边缘确定ROI区域上下边界，
 * 确定手指关节位置（由于手指的组织结构，手指关节处往往亮度比较高）
 * 根据手指关节位置确定ROI区域左右边界，获得ROI区域。参考实验步骤如图2。
 */
void Finger::find_knuckle()
{
	this->finger_roi = this->finger_rotate.clone();

	// 上下收缩
	Mat temp = finger_roi.rowRange(static_cast<int>(finger_roi.rows * 0.05), static_cast<int>(finger_roi.rows * 0.95)).clone();
	// 左右收缩
	int cod_x_right;
	{
		vector<int> edge_down_x;
		for (auto &point : this->edge_down)
		{
			edge_down_x.emplace_back(point.x);
		}
		cod_x_right = *(std::min_element(edge_down_x.begin(), edge_down_x.end()));
	}

	int cod_x_left;
	{
		vector<int> edge_up_x;
		for (auto &point : this->edge_up)
		{
			edge_up_x.emplace_back(point.x);
		}
		cod_x_left = *(std::max_element(edge_up_x.begin(), edge_up_x.end()));
	}
	line(temp, Point2i(cod_x_left, 0), Point2i(cod_x_left, temp.rows - 1), Scalar(0, 255, 0));
	line(temp, Point2i(cod_x_right, 0), Point2i(cod_x_right, temp.rows - 1), Scalar(0, 255, 0));
	// imshow("finger_roi", temp);
	// waitKey(1);

	this->finger_roi = this->finger_roi.rowRange(static_cast<int>(finger_roi.rows * 0.05), static_cast<int>(finger_roi.rows * 0.95)).clone();
	this->finger_roi = this->finger_roi.colRange(static_cast<int>(cod_x_left), static_cast<int>(cod_x_right)).clone();
	// imshow("finger_roi_true", this->finger_roi);
	// waitKey(1);

	// 接下来在 手指图中寻找到两个亮的地方 找到关节
	vector<uint64_t> windows_value;
	vector<int> coordinate;
	Mat finger_roi_gray;

	cvtColor(this->finger_roi, finger_roi_gray, COLOR_BGR2GRAY);
	{
		//imshow("finger_roi_gray", finger_roi_gray);
		//waitKey(1);
	}

	for (int row = 10; row < finger_roi_gray.rows - 10; row++)
	{
		uint64_t pixel_sum_value = 0;						   // 初始化像素值为 0
		for (int row_w = row - 10; row_w <= row + 10; row_w++) // 扫描每一行上下10个像素的领域
		{
			for (int col = 0; col < finger_roi_gray.cols; col++)
			{
				pixel_sum_value += finger_roi_gray.ptr<uchar>(row_w)[col]; // 记录下整个区域内的像素和
			}
		}
		windows_value.emplace_back(pixel_sum_value); //  ##将找到的像素值存起来
		coordinate.emplace_back(row);				 //  ##对应的中心行也存起来
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

		if(peak.size() == 2)
			break;
		else if(peak.size() > 2)
		{
			peak.clear();
			pin.clear();

			field += 20;
			continue;
		}
		else
		{
			while (1)
			{
			}
		}
	};

	{
		Mat temp = this->finger_roi.clone();
		for (auto row : pin)
		{
			line(temp, Point2i(0, row), Point2i(temp.cols - 1, row), Scalar(255, 0, 0));
		}

		imshow("temp", temp);
		waitKey(1);
	}

	this->finger_roi = this->finger_roi.rowRange(std::min(pin[0], pin[1]), std::max(pin[0], pin[1])).clone();
	// imshow("finger_roi", this->finger_roi);
	// waitKey(1);
}
