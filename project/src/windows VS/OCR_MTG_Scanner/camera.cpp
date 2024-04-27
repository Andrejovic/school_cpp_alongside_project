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
    ocr->Init("", "mtg");

    bool scanning = true;
    while (scanning) {
        
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
                outfile.open(path_to_out, ios::app); //closes after each scan for dataloss prevention
                frame = imread("bestcase.png"); //testing with an image
                myocr frame_text_recognition;
                Mat processedFrame;
                frame = frame_text_recognition.upright_box_detection(frame);
                cv::imshow("press R to rescan", frame);
				char key = cv::waitKey(0);
                if (key == 'r') { //rescan
                    continue;
                }

                processedFrame = frame_text_recognition.image_processing(frame);

                processedFrame = processedFrame(Range(round(processedFrame.rows * 0.05), round(processedFrame.rows * 0.1)), 
                                                Range(round(processedFrame.cols * 0.08), round(processedFrame.cols * 0.92)));
                ocr->SetPageSegMode(tesseract::PSM_AUTO);
                ocr->SetImage(processedFrame.data, processedFrame.cols, processedFrame.rows, 1, static_cast<int>(processedFrame.step));
                outText = string(ocr->GetUTF8Text());
                if (outText != "") {
                    size_t pos = outText.find('\n');
                    if (pos != string::npos) {
						outText = outText.erase(pos);
                    }
                    scanned_cards.emplace_back(outText);
                    outfile << outText << endl;
                }
                
            }
            outfile.close();
            
        }
        if (scanning != false) {
            
            scanning = getWindowProperty("camera", WND_PROP_VISIBLE) > 0;
        }
    }
    ocr->End();
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