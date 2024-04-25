
#include <tesseract/baseapi.h>
#include <iostream>
#include <string>
#include <fstream>
#include "ocr.h"

using namespace cv;
using namespace std;

class camera
{
public:
    vector<string> start_scanning(std::string path_to_out);
    cv::VideoCapture start_camera();
private:
    std::string outText;
};