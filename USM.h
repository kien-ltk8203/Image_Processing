#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <math.h>
#include<opencv2/opencv.hpp>
typedef int ll;

using namespace cv;
using namespace std;

void Unsharp_Mask(Mat in, long size, float a, float thresh);