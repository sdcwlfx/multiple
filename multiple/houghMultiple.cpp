#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <math.h>
using namespace cv;
using namespace std;

/**
�ۺ�ʵ�飺�Ƚ�����ͼƬ��ֵ��ֵ���������������ټ��������ͨ���������򣩣����ʹ����̬ѧ��ʴ
*/
//ͼ����ֵ��ֵ��
Mat binaryzation(Mat src)
{
	Mat gray;
	int field;
	printf("�����뵥����ֵ: ");
	std::cin >> field;

	//src = imread("F:/ustcsse/AdvancedImageProcessing/experiment/picture/natali.jpg");
	
	cvtColor(src, gray, CV_RGB2GRAY);
	imshow("�Ҷ�ͼ", gray);
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
	imshow("�Ҷ�ͼ��ֵ��", gray);
	//waitKey(0);
	return gray;

}


//https://blog.csdn.net/qq826309057/article/details/73008608
//��ֵͼ��Ǽ���ȡ
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




//ѡ�������ͨ����
void SelectMaxRegion(Mat &Src)
{
	//MAtת����IplImage
	Mat SrcColor,gray,zhangM;
	cvtColor(Src, SrcColor, CV_RGB2GRAY);
	IplImage *src = &IplImage(SrcColor);
	
	


	// ����������ͼ����32λ�ģ���R,G,B��Alphaͨ��  
	// ͼ����ʵ�ʴ洢˳����B,G,R  
	//IplImage *blue = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);    // ����һ����ͨ��ͼ��  
	//IplImage *green = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);   // ����һ����ͨ��ͼ��  
	//IplImage *red = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);     // ����һ����ͨ��ͼ��  
	//cvSplit(src, blue, green, red, NULL);   // �ָ���ɫͨ��  

	//cvThreshold(green, green, 0.0, 255.0, CV_THRESH_BINARY_INV | CV_THRESH_OTSU);   // OTSU����ֵ��  
	
	
	//����ͼ���ֵ��,���ض�ֵ����ĻҶ�ͼ
	gray=binaryzation(Src);
	IplImage *grayIpl = &IplImage(gray);

	cvNamedWindow("origin");
	cvShowImage("origin", src); // ��ʾԭʼͼ��  


	{
		int color = 254;            // ��254��ʼ�������ͨ���ܶ���253��  
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
						cvFloodFill(grayIpl, cvPoint(w, h), CV_RGB(color, color, color)); // �Ѹ���ͨ��������ɫ  
						color--;
					}
				}
			}
		}
		//cvNamedWindow("labeled");
		//cvShowImage("labeled", green);  // ��ʾ��Ǻ��ͼ��  

		int colorsum[255] = { 0 };
		for (w = 0; w < sz.width; w++)
		{
			for (h = 0; h < sz.height; h++)
			{
				if (CV_IMAGE_ELEM(grayIpl, unsigned char, h, w) > 0)   // ����0ֵ������������Ϊ255  
				{
					colorsum[CV_IMAGE_ELEM(grayIpl, unsigned char, h, w)]++; // ͳ��ÿ����ɫ������  
				}
			}
		}
		std::vector<int> v1(colorsum, colorsum + 255);    // �������ʼ��vector  
		int maxcolorsum = max_element(v1.begin(), v1.end()) - v1.begin(); // ��������������ɫ  
		for (w = 0; w < sz.width; w++)
		{
			for (h = 0; h < sz.height; h++)
			{
				if (CV_IMAGE_ELEM(grayIpl, unsigned char, h, w) == maxcolorsum)
				{
					CV_IMAGE_ELEM(grayIpl, unsigned char, h, w) = 0;    // ֻ�������������ɫ��Ϊ0  
				}
				else
				{
					CV_IMAGE_ELEM(grayIpl, unsigned char, h, w) = 255;      // ������Ϊ255  
				}
			}
		}
		cvNamedWindow("�����ͨ��");
		cvThreshold(grayIpl, grayIpl, 180, 255, CV_THRESH_BINARY_INV);
		cvShowImage("�����ͨ��", grayIpl);    // ��ʾ�����ͨ��  
	}

	
	
	//https://blog.csdn.net/futurewu/article/details/10047409
	//cvErode(grayIpl, grayIpl, 0, 1);//0��Ĭ��3x3�ṹ��ʴ��1��������ظ�����1��
	//��ȡ��ֵ��ͼ��Ǽ�
	zhangM=cvarrToMat(grayIpl);
	zhangSkeleton(zhangM);//Zhang�㷨��ȡ��ֵ��ͼ��Ǽ�
	//cvNamedWindow("��ֵ���Ǽ�");
	//cvShowImage("��ֵ���Ǽ�", zhangM);
	imshow("��ֵ���Ǽ�",zhangM);
	cvWaitKey(0);

	//return grayIpl;
	
}






//����
int main()
{
	Mat Src;
	IplImage *before=0, *after=0;
	//������ֵ����ֵ��200
	Src = imread("F:/ustcsse/AdvancedImageProcessing/experiment/picture/rivers.jpg");//��ȡͼƬ 
	
	//Src = imread("../rivers.jpg");
	if (Src.empty())
	{
		return -1;
	}
	//threshold(Src, Src, 180, 255, CV_THRESH_BINARY_INV);

	SelectMaxRegion(Src);  //�׵׺���

	

	return 0;
	//cvWaitKey(0);
}
