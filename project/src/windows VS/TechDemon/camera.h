#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <tesseract/baseapi.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <string>

class camera
{
public:
    void start_scanning(std::string path_to_out){
        cv::VideoCapture cap = start_camera();

    }

	cv::VideoCapture start_camera() {
        cv::VideoCapture cap(0);
        if (cap.isOpened()) {
            return cap;
            
        }
        std::cout << "cannot open camera";
        exit(-1);
	}
private:

};

