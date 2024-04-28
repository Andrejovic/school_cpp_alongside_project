
#include "ocr.h"

using namespace cv;
using namespace std;

//this method finds the largest contour of a given image by area
vector<Point> myocr::find_max_contour(Mat frame) { //by not being a reference i create a copy, i would have to make a copy either way
    Mat edges;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    
    cvtColor(frame, frame, COLOR_BGR2GRAY);
    blur(frame, frame, Size(3, 3));

    Canny(frame, edges, 10, 100, 3);
    cv::findContours(edges, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
    Mat cont = Mat::zeros(frame.size(), CV_8UC3);
    size_t max = 0;
    for (size_t i = 0; i < contours.size(); i++) {
        if (contourArea(contours[max]) < contourArea(contours[i])) {
            max = i;
        }
        drawContours(cont, contours, (int)i, Scalar(255), 1, LINE_8, hierarchy, 0);
    }
    Mat cont_max = Mat::zeros(frame.size(), CV_8UC3);
    drawContours(cont_max, contours, (int)max, Scalar(255));
    return contours[max];
}
 
//parent function, doesnt do anything by itself
void myocr::upright_box_detection(Mat& frame) {
    vector<Point> contour = find_max_contour(frame);
    this->fix_perspective(frame, contour);
}

//self-explanatory
void myocr::image_processing(Mat& frame) {
    cv::cvtColor(frame, frame, COLOR_BGR2GRAY);
    cv::GaussianBlur(frame, frame, Size(3, 3), 1000);
    //cv::Mat sorted;
    /*cv::sort(frame, sorted, SORT_EVERY_COLUMN + SORT_EVERY_ROW);
    double median;
    median = sorted.at<uchar>(static_cast<int>(sorted.total()) / 2);
    double sigma = 0.55;
    double lower = std::max(0.0, (1.0 - sigma) * median);
    double upper = std::min(255.0, (1.0 + sigma) * median); // take a look at if this helps */
    cv::threshold(frame, frame, 130, 220, THRESH_BINARY);
}

//rotate image according to the angle of the contour
void myocr::rotate_image(Mat& frame, vector<Point>& contour){
    RotatedRect rect = minAreaRect(contour);
    Mat box;
    boxPoints(rect, box);

    float angle = rect.angle;
    if (angle < 90.0 && angle > 45) { // working fine, if the image scanned is semi-upright (until about 30 degrees either way)
        angle -= 90.0;
    }
    Mat rotMatrix = getRotationMatrix2D(rect.center, angle, 1.0);

    vector<Point2f> points;
    for (int i = 0; i < box.rows; i++) {
        Point2f point(box.at<float>(i, 0), box.at<float>(i, 1));
        points.push_back(point);
    }
    warpAffine(frame, frame, rotMatrix, frame.size());
}

//crops image to the area of the rotated contour
void myocr::crop_image(Mat& frame) {
    vector<Point> contour = find_max_contour(frame);
    Rect bounding = boundingRect(contour);

    frame = frame(Range(bounding.y, bounding.y + bounding.height),
        Range(bounding.x, bounding.x + bounding.width));
}

//parent function, gets contour
void myocr::fix_perspective(Mat& frame, vector<Point>& contour) {
    vector<vector<Point>> contour_list = { contour };
    drawContours(frame, contour_list, 0, Scalar(255, 255, 255), 2);

    rotate_image(frame, contour);
    crop_image(frame);
}