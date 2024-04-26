#include "camera.h"

using namespace cv;
using namespace std;

vector<string> camera::start_scanning(string path_to_out) {
    vector<string> scanned_cards;
    VideoCapture cap = start_camera();
    ofstream outfile;
    string outText;
    
    tesseract::TessBaseAPI* ocr = new tesseract::TessBaseAPI();
    ocr->Init("", "eng");

    bool scanning = true;
    while (scanning) {
        outfile.open(path_to_out); //closes after each scan for loss of data
        Mat frame;
        namedWindow("camera", WINDOW_AUTOSIZE);
        cap.read(frame);
        imshow("camera", frame);
        char key = cv::waitKey(1);
        if (!(key != ' ' && key != 27)) {
            if (key == 27) { // Escape
                scanning = false;
            }
            else {
                frame = imread("testimg2.jpg");
                myocr frame_text_recognition;
                Mat processedFrame;
                frame = frame_text_recognition.upright_box_detection(frame);
                processedFrame = frame_text_recognition.image_processing(frame);

                //TODO finish OCR


                cv::imshow("frame", processedFrame);
                cv::waitKey(0);
                ocr->SetPageSegMode(tesseract::PSM_AUTO);
                ocr->SetImage(processedFrame.data, processedFrame.cols, processedFrame.rows, 3, processedFrame.step);
                outText = string(ocr->GetUTF8Text());
                if (outText != "") {
                    //scanned_cards.emplace_back(outText); //TODO fix the name with a function
                    outfile << outText;
                }
                
            }
            outfile.close();
            ocr->End();
        }
        if (scanning != false) {
            
            scanning = getWindowProperty("camera", WND_PROP_VISIBLE) > 0;
        }
    }
    cv::destroyAllWindows();
    return scanned_cards;
}

cv::VideoCapture camera::start_camera() {
    cv::VideoCapture cap(0);
    if (cap.isOpened()) {
        return cap;

    }
    std::cout << "cannot open camera";
    exit(-1);
}