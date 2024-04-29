
#include <tesseract/baseapi.h>
#include <iostream>
#include <string>
#include <fstream>
#include "ocr.h"

static std::string DEFAULT_PATH = "";

enum mode_options { Camera , Folder};

class camera
{
public:
    std::vector<std::string> start_scanning(std::string& path_to_out, mode_options& mode, std::string& path_to_images = DEFAULT_PATH);
    cv::VideoCapture start_camera();
private:
    std::string outText;
};