#pragma once
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <tuple>
#include <utility>
#include <vector>
class myocr
{
public:
	cv::Mat box_detection(cv::Mat frame);
	cv::Mat image_processing(cv::Mat frame);
	cv::Mat fix_perspective(cv::Mat frame, cv::Mat pts);
};

