// TechnologicDemo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        cout << "cannot open camera";
        return -1;
    }
    bool scanning = true;
    while (scanning) {
        cv::Mat frame;
        cv::namedWindow("camera", WINDOW_AUTOSIZE);
        cap.read(frame);
        cv::imshow("camera", frame);
        cv::waitKey(100);
        scanning = getWindowProperty("camera", WND_PROP_VISIBLE) > 0;
    }

    cv::Mat img = cv::imread("C:/Users/ajdro/Downloads/ilovecpp.png");
    cv::namedWindow("Loving cpp", WINDOW_AUTOSIZE);
    cv::imshow("Loving cpp", img);
    cv::moveWindow("Loving cpp", 0, 45);
    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;
}
