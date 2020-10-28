#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	VideoCapture cap(0);

	double scale = 0.5;

	double i_minH = 0;
	double i_maxH = 20;

	double i_minS = 43;
	double i_maxS = 255;

	double i_minV = 55;
	double i_maxV = 255;

	while (1)
	{
		Mat frame;
		Mat hsvMat;
		Mat detectMat;
		Mat ZHONGZHI;
		Mat JUNZHI;
		Mat GAOSI;
		Mat BIANYUAN;

		cap >> frame;
		Size ResImgSiz = Size(frame.cols*scale, frame.rows*scale);
		Mat rFrame = Mat(ResImgSiz, frame.type());
		resize(frame, rFrame, ResImgSiz, INTER_LINEAR);

		cvtColor(rFrame, hsvMat, COLOR_BGR2HSV);

		rFrame.copyTo(detectMat);

		cv::inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), detectMat);

		medianBlur(detectMat , ZHONGZHI, 3);

		blur(detectMat, JUNZHI, Size(3,3), Point(-1, -1), BORDER_DEFAULT);

		GaussianBlur(detectMat, GAOSI, Size(3, 3), 0, 0, BORDER_DEFAULT);

		
		Sobel(detectMat, BIANYUAN, CV_8UC1, 0, 1, 3,1,0, BORDER_DEFAULT);

		imshow("ZHONGZHI", ZHONGZHI);  //中值
		imshow("JUNZHI", JUNZHI);    //均值
		imshow("GAOSI", GAOSI);      //高斯
		imshow("BIANYUAN", BIANYUAN); //边缘提取
		imshow("frame", rFrame);

		waitKey(30);
	}

}