#include <opencv2/core/core.hpp>
#include <codecvt>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>
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
#include "Rotated_img_Processing.h"
#include "Two_Same_Images.h"
#include "Different_Images.h"
#include "Serial_Different_Processing.h"
#include <opencv2/features2d.hpp>
#include <opencv2/opencv_modules.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
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

ll is_Original(Mat img, ll x, ll y) {
	for (ll i = (720 - x) / 2 - 1; i < (720 - x) / 2 + x + 1; i++) {
		if (img.at<uchar>(i, (720 - y) / 2 - 1) != 0) return 0;
		if (img.at<uchar>(i, (720 - y) / 2 + y) != 0) return 0;
	}
	for (ll j = (720 - y) / 2 - 1; j < (720 - y) / 2 + y + 1; j++) {
		if (img.at<uchar>((720 - x) / 2 - 1, j) != 0) return 0;
		if (img.at<uchar>((720 - x) / 2 + x, j) != 0) return 0;
	}
	return 1;
}

int main()
{
	//Diff_Img_Processing();
	//Same_Img_Processing();
	//Rotated_Img_Processing();
	Serial_Diff_Processing();
	
	//cop = Equalize_Hist_Red(cop);
	//for (ll i = 0; i < h; i++) {
	//	for (ll j = 0; j < w; j++) {
	//		if (cnt[cop.at<uchar>(i, j)] == 0) tmp.at<uchar>(i, j) = cop.at<uchar>(i, j);
	//	}
	//}
	//threshold(tmp, tmp, 127, 255, THRESH_BINARY);
	//for (ll i = 0; i < h; i++) {
	//	for (ll j = 0; j < w; j++) {
	//		if (tmp.at<uchar>(i, j) == 0) tmp.at<uchar>(i, j) = 255;
	//		else tmp.at<uchar>(i, j) = 0;
	//	}
	//}
	//Mat matElement = getStructuringElement(MORPH_RECT, Size(5, 1));
	//morphologyEx(tmp, tmp, MORPH_ERODE, matElement);
	//vector<vector<Point>> contours;
	//vector<Vec4i> hierarchy;
	//findContours(tmp, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);

	//// draw contours on the original image
	//drawContours(v, contours, -1, Scalar(0, 255, 0), 3);
	////threshold(cop, cop, 254, 255, THRESH_BINARY);
	////tmp = Display_Serial(v, tmp);
	////tmp = Display_Canny(tmp);
	////tmp = Display_Serial(v, tmp);
	//imshow("hash", v);
	 
	////////////
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
	/////////////////////////////////////////////////

	//SIFT algorithm
	//-- Step 1: Detect the keypoints using SURF Detector
	//Mat input1 = imread("1.jpg", IMREAD_GRAYSCALE);
	//Mat input2 = imread("6.jpg", IMREAD_GRAYSCALE);
	//ll h = input1.rows, w = input1.cols;
	//resize(input1, input1, Size(w / 2, h / 2), INTER_LINEAR);
	//resize(input2, input2, Size(w / 2, h / 2), INTER_LINEAR);

	//Ptr<SiftFeatureDetector> detector1 = SiftFeatureDetector::create(), detector2 = SiftFeatureDetector::create();
	//vector<KeyPoint> keypoints1, keypoints2;
	//detector1->detect(input1, keypoints1);
	//detector2->detect(input2, keypoints2);

	//// Add results to image and save.
	//Mat output1, output2;
	//drawKeypoints(input1, keypoints1, output1);
	//drawKeypoints(input2, keypoints2, output2);
	//imshow("sift_result1.jpg", output1);
	//imshow("sift_result2.jpg", output2);
	//
	////Step2
	//Ptr<SiftDescriptorExtractor> extractor = SiftDescriptorExtractor::create();
	//Mat descriptors_1, descriptors_2;
	//extractor->compute(input1, keypoints1, descriptors_1);
	//extractor->compute(input2, keypoints2, descriptors_2);
	///*BFMatcher matcher(NORM_L2);
	//vector< DMatch > matches;
	//matcher.match(descriptors_1, descriptors_2, matches);*/

	////-- Draw matches
	////Mat img_matches;
	////drawMatches(input1, keypoints1, input2, keypoints2, matches, img_matches);

	//////-- Show detected matches
	////imshow("Matches", img_matches);

	////step3
	//FlannBasedMatcher matcher;
	//vector< DMatch > matches;
	//matcher.match(descriptors_1, descriptors_2, matches);

	//double max_dist = 0; double min_dist = 100;

	////-- Quick calculation of max and min distances between keypoints
	//for (int i = 0; i < descriptors_1.rows; i++)
	//{
	//	double dist = matches[i].distance;
	//	if (dist < min_dist) min_dist = dist;
	//	if (dist > max_dist) max_dist = dist;
	//}

	//printf("-- Max dist : %f \n", max_dist);
	//printf("-- Min dist : %f \n", min_dist);

	////-- Draw only "good" matches (i.e. whose distance is less than 2*min_dist,
	////-- or a small arbitary value ( 0.02 ) in the event that min_dist is very
	////-- small)
	////-- PS.- radiusMatch can also be used here.
	//std::vector< DMatch > good_matches;

	//for (int i = 0; i < descriptors_1.rows; i++)
	//{
	//	if (matches[i].distance <= max(2 * min_dist, 0.02))
	//	{
	//		good_matches.push_back(matches[i]);
	//	}
	//}

	////-- Draw only "good" matches
	//Mat img_matches;
	//drawMatches(input1, keypoints1, input2, keypoints2,
	//	good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
	//	vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	////-- Show detected matches
	//imshow("Good Matches", img_matches);

	//for (int i = 0; i < (int)good_matches.size(); i++)
	//{
	//	printf("-- Good Match [%d] Keypoint 1: %d  -- Keypoint 2: %d  \n", i, good_matches[i].queryIdx, good_matches[i].trainIdx);
	//}
	waitKey(0);
}