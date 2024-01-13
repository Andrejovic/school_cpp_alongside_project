// TechnologicDemo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace cv;

int main()
{
    cv::Mat img = cv::imread("C:/Users/ajdro/Downloads/ilovecpp.png");
    namedWindow("Loving cpp", WINDOW_AUTOSIZE);
    cv::imshow("Loving cpp", img);
    cv::moveWindow("Loving cpp", 0, 45);
    cv::waitKey(0);
    cv::destroyAllWindows();
    std::cout << "Hello";
    return 0;
}