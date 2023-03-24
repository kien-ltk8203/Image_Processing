#include <opencv2/core/core.hpp>
#include <codecvt>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>
#include<opencv2/opencv.hpp>
//#include "Channels.h"
//#include "YUV_space.h"
#include "Equal_His.h"
//#include "MedianFilter.h"
#include "MeanFilter.h"
#include "Sobel_Filter.h"
#include "Canny_Filter.h"
//#include "DCT_Transform.h"
#include "Gaussian_Filter.h"
#include "USM.h"
//#include "Segmentation.h"
//#include "Remove_Drawing.h"
#include "Serial_Detection.h"
#include "Anomaly.h"
typedef int ll;

using namespace cv;
using namespace std;


void Display_Histogram(Mat img, string Diagram_Name) {
	int histSize = 256;
	float range[] = { 0, 255 }; //Pham vi gia tri muon do
	const float* ranges[] = { range };
	// Tinh histogram
	MatND hist;
	calcHist(&img, 1, 0, Mat(), hist, 1, &histSize, ranges, true, false);
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);
	Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0));
	normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	for (int i = 1; i < histSize; i++)
	{
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(hist.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0);
	}
	imshow(Diagram_Name, histImage);
}

void fft(const Mat& src, Mat& dst)
{
	// convert to a 32F mat and take log
	Mat logimg;
	src.convertTo(logimg, CV_32F);
	log(logimg + 1, logimg);

	// resize to optimal fft size
	Mat padded;
	int m = getOptimalDFTSize(src.rows);
	int n = getOptimalDFTSize(src.cols);
	copyMakeBorder(logimg, padded, 0, m - logimg.rows, 0, n - logimg.cols, BORDER_CONSTANT, Scalar::all(0));

	// add imaginary column to mat and apply fft
	Mat plane[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
	Mat imgComplex;
	merge(plane, 2, imgComplex);
	dft(imgComplex, dst);
}

Mat butterworth(const Mat& img, int d0, int n, int high, int low)
{
	Mat single(img.rows, img.cols, CV_32F);
	int cx = img.rows / 2;
	int cy = img.cols / 2;
	float upper = high * 0.01;
	float lower = low * 0.01;

	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			double radius = sqrt(pow(i - cx, 2) + pow(j - cy, 2));
			single.at<float>(i, j) = ((upper - lower) * (1 / pow(d0 / radius, 2 * n))) + lower;
		}
	}
	return single;
}

Mat homomorphic(Mat src)
{
	vector<Mat> hlsimg;
	Mat tmphls;
	cvtColor(src, tmphls, COLOR_RGB2HLS);
	split(tmphls, hlsimg);
	Mat img = hlsimg[0];

	// apply FFT
	Mat fftimg;
	fft(img, fftimg);

	// apply Butterworth HPS
	Mat filter = butterworth(fftimg, 10, 4, 100, 30);
	Mat bimg;
	Mat bchannels[] = { Mat_<float>(filter), Mat::zeros(filter.size(), CV_32F) };
	merge(bchannels, 2, bimg);
	mulSpectrums(fftimg, bimg, fftimg, 0);

	// apply inverse FFT
	Mat ifftimg;
	idft(fftimg, ifftimg, CV_HAL_DFT_REAL_OUTPUT);

	Mat expimg;
	exp(ifftimg, expimg);

	Mat final;
	hlsimg[0] = Mat(expimg, Rect(0, 0, src.cols, src.rows));
	hlsimg[0].convertTo(hlsimg[0], CV_8U);

	merge(&hlsimg[0], 3, img);
	cvtColor(img, final, COLOR_HLS2BGR);
	return final;
}

int main()
{
	////Display_After_Removing_Drawing();
	////ll d = 0;
	////Mat O_img = imread("1.jpg", IMREAD_COLOR);
	////Mat cop = O_img.clone();
	//////Mat crop_1 = O_img(Rect(25, 220, 57, 320));
	//////Mat crop_2 = O_img(Rect(950, 587, 300, 50));
	////for (ll i = 0; i < O_img.rows; i++) {
	////	for (ll j = 0; j < O_img.cols; j++) {
	////		if ((j >= 25 && i >= 220 && j <= 82 && i <= 540) || (j >= 950 && i >= 587 && j <= 1250 && i <= 637))
	////			d = 0;
	////		else {
	////			cop.at<Vec3b>(i, j)[0] = 0.0;
	////			cop.at<Vec3b>(i, j)[1] = 0.0;
	////			cop.at<Vec3b>(i, j)[2] = 0.0;
	////		}
	////	}
	////}
	////Display_Serial(O_img, cop);
	///*cop = Display_Canny(cop);
	////imshow("O", cop);*/
	////resize(img, resized_img, Size(img.cols / 2, img.rows / 2), INTER_LINEAR);
	//Mat O_img = imread("1.jpg", IMREAD_COLOR);
	//Mat	D_img = imread("4.jpg", IMREAD_COLOR);
	//Mat cop = D_img.clone();
	//cvtColor(O_img, O_img, COLOR_BGR2GRAY);
	//cvtColor(D_img, D_img, COLOR_BGR2GRAY);
	//ll h = O_img.rows, w = O_img.cols;
	//ll threshold = (O_img.at<uchar>(0, 0) + D_img.at<uchar>(0, 0)) / 2;
	//Mat tmp = O_img.clone();
	//O_img = Equalize_Hist_Red(O_img);
	//D_img = Equalize_Hist_Red(D_img);
	//O_img = Display_Segmentation(O_img);
	//for (ll i = 0; i < h; i++) {
	//	for (ll j = 0; j < w; j++) {
	//		tmp.at<uchar>(i, j) = abs(O_img.at<uchar>(i, j) - D_img.at<uchar>(i, j));
	//	}
	//}
	//imshow("00", O_img);
	//imshow("11", D_img);
	//Display_Serial(cop, tmp);
	Mat img = imread("1.jpg", IMREAD_GRAYSCALE);
	Mat cop = imread("4.jpg", IMREAD_GRAYSCALE);
	ll h = img.rows, w = img.cols;
	Mat tmp = cop.clone();
	threshold(img, img, 89, 255, THRESH_BINARY);
	threshold(cop, cop, 50, 255, THRESH_BINARY);
	for (ll i = 0; i < h; i++) {
		for (ll j = 0; j < w; j++) {
			tmp.at<uchar>(i, j) = abs(cop.at<uchar>(i, j) - img.at<uchar>(i, j));
		}
	}
	for (ll i = 1; i < h - 1; i++) {
		for (ll j = 1; j < w - 1; j++) {
			if (tmp.at<uchar>(i - 1, j - 1) == 0 && tmp.at<uchar>(i - 1, j) == 0 && tmp.at<uchar>(i - 1, j + 1) == 0 &&
				tmp.at<uchar>(i, j - 1) == 0 && tmp.at<uchar>(i, j) == 255 && tmp.at<uchar>(i, j + 1) == 0 &&
				tmp.at<uchar>(i + 1, j - 1) == 0 && tmp.at<uchar>(i + 1, j) == 0 && tmp.at<uchar>(i + 1, j + 1) == 0)
				tmp.at<uchar>(i, j) = 0;
		}
	}
	for (ll i = 1; i < h - 1; i++) {
		for (ll j = 1; j < w - 1; j++) {
			if (tmp.at<uchar>(i - 1, j - 1) == 0 && tmp.at<uchar>(i - 1, j) == 0 && tmp.at<uchar>(i - 1, j + 1) == 0 &&
				tmp.at<uchar>(i, j - 1) == 0 && tmp.at<uchar>(i, j) == 255 && tmp.at<uchar>(i, j + 1) == 0 &&
				tmp.at<uchar>(i + 1, j - 1) == 0 && tmp.at<uchar>(i + 1, j) == 0 && tmp.at<uchar>(i + 1, j + 1) == 0)
				tmp.at<uchar>(i, j) = 0;
		}
	}
	for (ll i = 1; i < h - 1; i++) {
		for (ll j = 1; j < w - 1; j++) {
			if (tmp.at<uchar>(i - 1, j - 1) == 0 && tmp.at<uchar>(i - 1, j) == 0 && tmp.at<uchar>(i - 1, j + 1) == 0 &&
				tmp.at<uchar>(i, j - 1) == 0 && tmp.at<uchar>(i, j) == 255 && tmp.at<uchar>(i, j + 1) == 0 &&
				tmp.at<uchar>(i + 1, j - 1) == 0 && tmp.at<uchar>(i + 1, j) == 0 && tmp.at<uchar>(i + 1, j + 1) == 0)
				tmp.at<uchar>(i, j) = 0;
		}
	}
	for (ll i = 1; i < h - 1; i++) {
		for (ll j = 1; j < w - 1; j++) {
			if (tmp.at<uchar>(i - 1, j - 1) == 0 && tmp.at<uchar>(i - 1, j) == 0 && tmp.at<uchar>(i - 1, j + 1) == 0 &&
				tmp.at<uchar>(i, j - 1) == 0 && tmp.at<uchar>(i, j) == 255 && tmp.at<uchar>(i, j + 1) == 0 &&
				tmp.at<uchar>(i + 1, j - 1) == 0 && tmp.at<uchar>(i + 1, j) == 0 && tmp.at<uchar>(i + 1, j + 1) == 0)
				tmp.at<uchar>(i, j) = 0;
		}
	}
	imshow("1", img);
	imshow("2", cop);
	Mat obj = imread("4.jpg", IMREAD_COLOR);
	Mat white_img = img.clone();
	for (ll i = 1; i < h - 1; i++) {
		for (ll j = 1; j < w - 1; j++) {
			white_img.at<uchar>(i, j) = 255;
		}
	}
	tmp = Display_Serial(white_img, tmp);
	tmp = Display_Canny(tmp);
	imshow("2.5", tmp);
	Mat matElement = getStructuringElement(MORPH_RECT, Size(1, 1));
	morphologyEx(tmp, tmp, MORPH_OPEN, matElement);
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(tmp, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);
	drawContours(obj, contours, -1, Scalar(0, 255, 0), 23);
	imshow("3", obj);
	waitKey(0);
}