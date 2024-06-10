#include <opencv2/opencv.hpp>


//options for the filtr
typedef struct{

	//vessel scales
	int sigma_start;
	int sigma_end;
	int sigma_step;
	
	//BetaOne: suppression of blob-like structures. 
	//BetaTwo: background suppression. (See Frangi1998...)
	float BetaOne;
	float BetaTwo;

	bool BlackWhite; //enhance black structures if true, otherwise enhance white structures


} frangi2d_opts_t;

#define DEFAULT_SIGMA_START 3
#define DEFAULT_SIGMA_END 7
#define DEFAULT_SIGMA_STEP 1
#define DEFAULT_BETA_ONE 1.6
#define DEFAULT_BETA_TWO 0.08
#define DEFAULT_BLACKWHITE true


/////////////////
//Frangi filter//
/////////////////

//frangi滤波主要过程
void frangi2d(const cv::Mat &src, cv::Mat &J, cv::Mat &scale, cv::Mat &directions, frangi2d_opts_t opts);
//计算Hessian矩阵 with parameter sigma on src, save to Dxx, Dxy and Dyy.
void frangi2d_hessian(const cv::Mat &src, cv::Mat &Dxx, cv::Mat &Dxy, cv::Mat &Dyy, float sigma);

//参数设置 (sigma_start = 3, sigma_end = 7, sigma_step = 1, BetaOne = 1.6, BetaTwo 0.08)
void frangi2d_createopts(frangi2d_opts_t *opts);

//默认参数 (sigma_start = 3, sigma_end = 7, sigma_step = 1, BetaOne = 1.6, BetaTwo 0.08)
//自由参数设置
void frangi2d_createopts_custom(frangi2d_opts_t *opts ,
                                int sigma_start,int sigma_end,int sigma_step,
                                float BetaOne,float BetaTwo,bool  BlackWhite ) ;

//计算特征值 from Dxx, Dxy, Dyy. Save results to lambda1, lambda2, Ix, Iy. 
void frangi2_eig2image(const cv::Mat &Dxx, const cv::Mat &Dxy, const cv::Mat &Dyy, cv::Mat &lambda1, cv::Mat &lambda2, cv::Mat &Ix, cv::Mat &Iy);

