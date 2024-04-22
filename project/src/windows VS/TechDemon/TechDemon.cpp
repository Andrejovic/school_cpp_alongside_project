// TechnologicDemo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <tesseract/baseapi.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "camera.h"

using namespace cv;
using namespace std;

int main()
{
    //comparing to a set database

    //pressing chars for different things?
    //Space - scan
    //r - retry scan
    //n - next card
    //Esc - exit
    //camera cam;
    //cam.start_scanning();
    

    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        cout << "cannot open camera";
        return -1;
    }

    string outText;
    ofstream outfile("test.txt");
    bool scanning = true;
    tesseract::TessBaseAPI* ocr = new tesseract::TessBaseAPI(); //TODO unsafe pointer, change to unique if catching
    ocr->Init("", "eng");
    
    while (scanning) {
        cv::Mat frame;
        cv::namedWindow("camera", WINDOW_AUTOSIZE);
        cap.read(frame);
        cv::imshow("camera", frame);
        char key = cv::waitKey(1);
        if (key == 'r' || key == 'n' || key == ' ') {
            if (key == 'r') {
                
            }
            else if (key == 'n') {
                
            }
            else {
                Mat grayFrame;
                vector<vector<Point>> contours;
                vector<Vec4i> hierarchy;
                double min, max;
                cv::cvtColor(frame, grayFrame, COLOR_BGR2GRAY);
                imshow("frame", grayFrame);
                cv::waitKey(0);
                cv::GaussianBlur(grayFrame, grayFrame, Size(1, 1), 1000);
                imshow("frame", grayFrame);
                cv::waitKey(0);
                cv::threshold(grayFrame, grayFrame, 115, 255, THRESH_BINARY);
                imshow("frame", grayFrame);
                cv::waitKey(0);
                cv::findContours(grayFrame, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
                for (size_t i = 0; i < contours.size(); i++) {
                    cv::drawContours(grayFrame, contours, (int)i, Scalar(255), 1, LINE_8, hierarchy, 0);
                }
                //RotatedRect box = cv::minAreaRect(grayFrame);
                //cv::boxPoints(box,grayFrame);


                imshow("frame", grayFrame);
                cv::waitKey(0);
                ocr->SetPageSegMode(tesseract::PSM_AUTO);
                ocr->SetImage(grayFrame.data, grayFrame.cols, grayFrame.rows, 3, grayFrame.step);
                outText = string(ocr->GetUTF8Text());
                outfile << outText;
                
                
            }
            outfile.close();
            ocr->End();
            return 0;
        }
       
        scanning = getWindowProperty("camera", WND_PROP_VISIBLE) > 0;
    }

    

    /*cv::Mat img = cv::imread("C:/Users/ajdro/Downloads/ilovecpp.png");
    cv::namedWindow("Loving cpp", WINDOW_AUTOSIZE);
    cv::imshow("Loving cpp", img);
    cv::moveWindow("Loving cpp", 0, 45);
    cv::waitKey(0);*/
    cv::destroyAllWindows();
    return 0;
}
