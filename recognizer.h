#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d.hpp>
#include <string>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

class Recognizer{
	Mat img;
public:
	Recognizer();
	void load(string fname);
	vector<vector<int>> recognise();
};

