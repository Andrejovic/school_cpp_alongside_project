
#include "ocr.h"

using namespace cv;
using namespace std;

vector<Point> find_max_contour(Mat frame) {
    Mat edges;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    cvtColor(frame, frame, COLOR_BGR2GRAY);
    Canny(frame, edges, 40, 200, 3);
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
 
Mat myocr::box_detection(Mat frame) {
    vector<Point> contour = find_max_contour(frame);

    Mat img = Mat::zeros(frame.size(), CV_8UC3);
    

    vector<vector<Point>> contour_list = { contour };
    drawContours(frame, contour_list, 0, Scalar(255, 255, 255), 2);
    cv::imshow("Contours", frame);
    cv::waitKey(0);
    RotatedRect rect = minAreaRect(contour);
    Mat box;
    boxPoints(rect, box);

    float angle = rect.angle;
    if (angle < 90.0) {
        angle -= 90.0;
    }
    Mat rotMatrix = getRotationMatrix2D(rect.center, angle, 1.0);

    vector<Point2f> points;
    for (int i = 0; i < box.rows; i++) {
        Point2f point(box.at<float>(i, 0), box.at<float>(i, 1));
        points.push_back(point);
    }

    

    Mat mask = Mat::zeros(frame.size(), CV_8U);
    Mat cropped;
    drawContours(mask, contour_list, 0, Scalar(255), FILLED);
    frame.copyTo(cropped, mask);
    warpAffine(cropped, frame, rotMatrix, cropped.size());

    contour = find_max_contour(frame);
    Rect bounding = boundingRect(contour);

    frame = frame(Range(bounding.y, bounding.y + bounding.height),
                  Range(bounding.x, bounding.x + bounding.width));
    cv::imshow("Contours", frame);
    cv::waitKey(0);
    return frame;
}

Mat myocr::image_processing(Mat frame) {
    Mat grayFrame;
    cv::cvtColor(frame, grayFrame, COLOR_BGR2GRAY);
    cv::GaussianBlur(grayFrame, grayFrame, Size(1, 1), 1000);
    cv::threshold(grayFrame, grayFrame, 75, 200, THRESH_BINARY);
    return grayFrame;
}

Mat myocr::fix_perspective(Mat frame, Mat pts) {
    Mat fixed;
    return fixed;
}

