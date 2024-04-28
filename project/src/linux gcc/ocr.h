#pragma once
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <tuple>
#include <utility>
#include <vector>
#include <algorithm>
class myocr
{
public:
	void upright_box_detection(cv::Mat& frame);
	void image_processing(cv::Mat& frame);
	void fix_perspective(cv::Mat& frame, std::vector<cv::Point>& contour);
private:
	std::vector<cv::Point> find_max_contour(cv::Mat);
	void rotate_image(cv::Mat& frame, std::vector<cv::Point>& contour);
	void crop_image(cv::Mat& frame);
};