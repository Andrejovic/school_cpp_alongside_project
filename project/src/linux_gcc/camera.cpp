#include "camera.h"

using namespace cv;
using namespace std;

vector<string> camera::start_scanning(string& path_to_out, mode_options& mode, string& path_to_images) {
    vector<string> scanned_cards;
    VideoCapture cap;
    vector<string> images_in_folder;
    vector<Mat> frames;
    if (mode == Camera) {
        cap = start_camera();
    }
    else if (mode == Folder) {
        glob(path_to_images, images_in_folder);
        size_t count = images_in_folder.size();
        for (size_t i = 0; i < count; i++) {
			frames.push_back(imread(images_in_folder[i]));
        }
    }
    ofstream outfile;
    string outText;
    
    tesseract::TessBaseAPI* ocr = new tesseract::TessBaseAPI();
    ocr->Init("", "eng");
    ocr->Init("", "mtg");

    bool scanning = true;
    size_t i = 0;
    while (scanning) {
        
        Mat frame;
        char key;
        if (mode == Camera) {
            namedWindow("camera", WINDOW_AUTOSIZE);
            cap.read(frame);
            imshow("camera", frame);
            key = cv::waitKey(1);
        }
        else if (mode == Folder) {
            frame = frames[i];
            imshow("camera", frame);
            key = cv::waitKey(0);
        }
        
        if (!(key != ' ' && key != 27)) {
            if (key == 27) { // Escape
                scanning = false;
            }
            else {
                outfile.open(path_to_out, ios::app); //closes after each scan for dataloss prevention
                //frame = imread("notbestcase.png"); //testing with an image
                myocr frame_text_recognition;
                frame_text_recognition.upright_box_detection(frame);
                cv::imshow("press R to rescan", frame);
				char key = cv::waitKey(0);
                if (key == 'r') { //rescan
                    continue;
                }

                frame_text_recognition.image_processing(frame);
                frame = frame(Range(static_cast<int>(frame.rows * 0.05), static_cast<int>(frame.rows * 0.1)),
                              Range(static_cast<int>(frame.cols * 0.08), static_cast<int>(frame.cols * 0.8)));
                cv::imshow("press R to rescan", frame);
                cv::waitKey(0);
                ocr->SetPageSegMode(tesseract::PSM_AUTO);
                ocr->SetImage(frame.data, frame.cols, frame.rows, 1, static_cast<int>(frame.step));
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
        if (scanning) {
            //scanning = getWindowProperty("camera", WND_PROP_VISIBLE) > 0;
            if (mode == Folder) {
                if (i < images_in_folder.size() - 1) {
					i++;
                }
                else {
                    scanning = false;
                }
            }
            
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