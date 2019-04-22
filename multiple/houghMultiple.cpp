#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <math.h>
using namespace cv;
using namespace std;

/**
综合实验：先将河流图片阈值二值化保留河流道，再计算最大连通变量（区域），最后使用形态学腐蚀
*/
//图像阈值二值化
Mat binaryzation(Mat src)
{
	Mat gray;
	int field;
	printf("请输入单个阈值: ");
	std::cin >> field;

	//src = imread("F:/ustcsse/AdvancedImageProcessing/experiment/picture/natali.jpg");
	
	cvtColor(src, gray, CV_RGB2GRAY);
	imshow("灰度图", gray);
	for (int i = 0; i < gray.rows; i++) {
		for (int j = 0; j < gray.cols; j++) {
			if (gray.at<uchar>(i, j) < field) {
				gray.at<uchar>(i, j) = 0;
			}
			else {
				gray.at<uchar>(i, j) = 255;
			}
		}
	}
	imshow("灰度图二值化", gray);
	//waitKey(0);
	return gray;

}


//https://blog.csdn.net/qq826309057/article/details/73008608
//二值图像骨架提取
void zhangSkeleton(Mat &srcimage)
{
	int kernel[9];
	int nl = srcimage.rows;
	int nc = srcimage.cols;
	vector<Point> delete_list;
	int A, B;
	while (true)
	{
		for (int j = 1; j < nl - 1; j++)
		{
			uchar* data_pre = srcimage.ptr<uchar>(j - 1);
			uchar* data = srcimage.ptr<uchar>(j);
			uchar* data_next = srcimage.ptr<uchar>(j + 1);
			for (int i = 1; i < (nc - 1); i++)
			{
				if (data[i] == 255)
				{
					kernel[0] = 1;
					if (data_pre[i] == 255) kernel[1] = 1;
					else  kernel[1] = 0;
					if (data_pre[i + 1] == 255) kernel[2] = 1;
					else  kernel[2] = 0;
					if (data[i + 1] == 255) kernel[3] = 1;
					else  kernel[3] = 0;
					if (data_next[i + 1] == 255) kernel[4] = 1;
					else  kernel[4] = 0;
					if (data_next[i] == 255) kernel[5] = 1;
					else  kernel[5] = 0;
					if (data_next[i - 1] == 255) kernel[6] = 1;
					else  kernel[6] = 0;
					if (data[i - 1] == 255) kernel[7] = 1;
					else  kernel[7] = 0;
					if (data_pre[i - 1] == 255) kernel[8] = 1;
					else  kernel[8] = 0;

					B = 0;
					for (int k = 1; k < 9; k++)
					{
						B = B + kernel[k];
					}
					if ((B >= 2) && (B <= 6))
					{
						A = 0;
						if (!kernel[1] && kernel[2]) A++;
						if (!kernel[2] && kernel[3]) A++;
						if (!kernel[3] && kernel[4]) A++;
						if (!kernel[4] && kernel[5]) A++;
						if (!kernel[5] && kernel[6]) A++;
						if (!kernel[6] && kernel[7]) A++;
						if (!kernel[7] && kernel[8]) A++;
						if (!kernel[8] && kernel[1]) A++;
						//
						if (A == 1)
						{
							if ((kernel[1] * kernel[3] * kernel[5] == 0)
								&& (kernel[3] * kernel[5] * kernel[7] == 0))
							{
								delete_list.push_back(Point(i, j));
							}
						}
					}
				}
			}
		}
		int size = delete_list.size();
		if (size == 0)
		{
			break;
		}
		for (int n = 0; n < size; n++)
		{
			Point tem;
			tem = delete_list[n];
			uchar* data = srcimage.ptr<uchar>(tem.y);
			data[tem.x] = 0;
		}
		delete_list.clear();
		for (int j = 1; j < nl - 1; j++)
		{
			uchar* data_pre = srcimage.ptr<uchar>(j - 1);
			uchar* data = srcimage.ptr<uchar>(j);
			uchar* data_next = srcimage.ptr<uchar>(j + 1);
			for (int i = 1; i < (nc - 1); i++)
			{
				if (data[i] == 255)
				{
					kernel[0] = 1;
					if (data_pre[i] == 255) kernel[1] = 1;
					else  kernel[1] = 0;
					if (data_pre[i + 1] == 255) kernel[2] = 1;
					else  kernel[2] = 0;
					if (data[i + 1] == 255) kernel[3] = 1;
					else  kernel[3] = 0;
					if (data_next[i + 1] == 255) kernel[4] = 1;
					else  kernel[4] = 0;
					if (data_next[i] == 255) kernel[5] = 1;
					else  kernel[5] = 0;
					if (data_next[i - 1] == 255) kernel[6] = 1;
					else  kernel[6] = 0;
					if (data[i - 1] == 255) kernel[7] = 1;
					else  kernel[7] = 0;
					if (data_pre[i - 1] == 255) kernel[8] = 1;
					else  kernel[8] = 0;

					B = 0;
					for (int k = 1; k < 9; k++)
					{
						B = B + kernel[k];
					}
					if ((B >= 2) && (B <= 6))
					{
						A = 0;
						if (!kernel[1] && kernel[2]) A++;
						if (!kernel[2] && kernel[3]) A++;
						if (!kernel[3] && kernel[4]) A++;
						if (!kernel[4] && kernel[5]) A++;
						if (!kernel[5] && kernel[6]) A++;
						if (!kernel[6] && kernel[7]) A++;
						if (!kernel[7] && kernel[8]) A++;
						if (!kernel[8] && kernel[1]) A++;
						//
						if (A == 1)
						{
							if ((kernel[1] * kernel[3] * kernel[7] == 0)
								&& (kernel[1] * kernel[5] * kernel[7] == 0))
							{
								delete_list.push_back(Point(i, j));
							}
						}
					}
				}
			}
		}
		size = delete_list.size();
		if (size == 0)
		{
			break;
		}
		for (int n = 0; n < size; n++)
		{
			Point tem;
			tem = delete_list[n];
			uchar* data = srcimage.ptr<uchar>(tem.y);
			data[tem.x] = 0;
		}
		delete_list.clear();
	}
}




//选择最大连通分域
void SelectMaxRegion(Mat &Src)
{
	//MAt转换成IplImage
	Mat SrcColor,gray,zhangM;
	cvtColor(Src, SrcColor, CV_RGB2GRAY);
	IplImage *src = &IplImage(SrcColor);
	
	


	// 摄像机保存的图像是32位的，有R,G,B和Alpha通道  
	// 图像中实际存储顺序是B,G,R  
	//IplImage *blue = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);    // 制作一个单通道图像  
	//IplImage *green = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);   // 制作一个单通道图像  
	//IplImage *red = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);     // 制作一个单通道图像  
	//cvSplit(src, blue, green, red, NULL);   // 分割颜色通道  

	//cvThreshold(green, green, 0.0, 255.0, CV_THRESH_BINARY_INV | CV_THRESH_OTSU);   // OTSU法二值化  
	
	
	//调用图像二值化,返回二值化后的灰度图
	gray=binaryzation(Src);
	IplImage *grayIpl = &IplImage(gray);

	cvNamedWindow("origin");
	cvShowImage("origin", src); // 显示原始图像  


	{
		int color = 254;            // 从254开始，因此连通域不能多于253个  
		CvSize sz = cvGetSize(grayIpl);
		int w, h;
		for (w = 0; w < sz.width; w++)
		{
			for (h = 0; h < sz.height; h++)
			{
				if (color > 0)
				{
					if (CV_IMAGE_ELEM(grayIpl, unsigned char, h, w) == 255)
					{
						cvFloodFill(grayIpl, cvPoint(w, h), CV_RGB(color, color, color)); // 把各连通域标记上颜色  
						color--;
					}
				}
			}
		}
		//cvNamedWindow("labeled");
		//cvShowImage("labeled", green);  // 显示标记后的图像  

		int colorsum[255] = { 0 };
		for (w = 0; w < sz.width; w++)
		{
			for (h = 0; h < sz.height; h++)
			{
				if (CV_IMAGE_ELEM(grayIpl, unsigned char, h, w) > 0)   // 不对0值计数，不可能为255  
				{
					colorsum[CV_IMAGE_ELEM(grayIpl, unsigned char, h, w)]++; // 统计每种颜色的数量  
				}
			}
		}
		std::vector<int> v1(colorsum, colorsum + 255);    // 用数组初始化vector  
		int maxcolorsum = max_element(v1.begin(), v1.end()) - v1.begin(); // 求出最多数量的颜色  
		for (w = 0; w < sz.width; w++)
		{
			for (h = 0; h < sz.height; h++)
			{
				if (CV_IMAGE_ELEM(grayIpl, unsigned char, h, w) == maxcolorsum)
				{
					CV_IMAGE_ELEM(grayIpl, unsigned char, h, w) = 0;    // 只把最多数量的颜色标为0  
				}
				else
				{
					CV_IMAGE_ELEM(grayIpl, unsigned char, h, w) = 255;      // 其他标为255  
				}
			}
		}
		cvNamedWindow("最大连通域");
		cvThreshold(grayIpl, grayIpl, 180, 255, CV_THRESH_BINARY_INV);
		cvShowImage("最大连通域", grayIpl);    // 显示最大连通域  
	}

	
	
	//https://blog.csdn.net/futurewu/article/details/10047409
	//cvErode(grayIpl, grayIpl, 0, 1);//0：默认3x3结构腐蚀，1：代表可重复进行1次
	//提取二值化图像骨架
	zhangM=cvarrToMat(grayIpl);
	zhangSkeleton(zhangM);//Zhang算法提取二值化图像骨架
	//cvNamedWindow("二值化骨架");
	//cvShowImage("二值化骨架", zhangM);
	imshow("二值化骨架",zhangM);
	cvWaitKey(0);

	//return grayIpl;
	
}






//测试
int main()
{
	Mat Src;
	IplImage *before=0, *after=0;
	//河流二值化阈值设200
	Src = imread("F:/ustcsse/AdvancedImageProcessing/experiment/picture/rivers.jpg");//读取图片 
	
	//Src = imread("../rivers.jpg");
	if (Src.empty())
	{
		return -1;
	}
	//threshold(Src, Src, 180, 255, CV_THRESH_BINARY_INV);

	SelectMaxRegion(Src);  //白底黑字

	

	return 0;
	//cvWaitKey(0);
}
