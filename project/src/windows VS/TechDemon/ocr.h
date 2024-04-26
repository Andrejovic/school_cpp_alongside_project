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
	cv::Mat upright_box_detection(cv::Mat frame);
	cv::Mat image_processing(cv::Mat frame);
	cv::Mat fix_perspective(cv::Mat frame, std::vector<cv::Point> contour);
private:
	std::vector<cv::Point> find_max_contour(cv::Mat);
	cv::Mat rotate_image(cv::Mat frame, std::vector<cv::Point> contour);
	cv::Mat crop_image(cv::Mat frame);
};

