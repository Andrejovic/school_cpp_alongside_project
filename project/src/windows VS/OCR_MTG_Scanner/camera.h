
#include <tesseract/baseapi.h>
#include <iostream>
#include <string>
#include <fstream>
#include "ocr.h"

class camera
{
public:
    std::vector<std::string> start_scanning(std::string path_to_out);
    cv::VideoCapture start_camera();
private:
    std::string outText;
};