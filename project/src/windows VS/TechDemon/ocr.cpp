
#include "ocr.h"

using namespace cv;
using namespace std;

vector<Vec2f> sort_points(Mat pts) {
    vector<Vec2f> ret(4);
    vector<float> sumF(pts.rows);
    vector<float> diffF(pts.rows);

    for (int i = 0; i < pts.rows; i++) {

        Point2f point;
        Point2f pointOld;
        
        Vec2f pointVec = pts.at<float>(i);
        point = Point2f(pointVec[0], pointVec[1]);

        Vec2f pointVecOld;
        if (i > 0) {
            Vec2f pointVecOld = pts.at<float>(i - 1);
            pointOld = Point2f(pointVecOld[0], pointVecOld[1]);
        }
        
        sumF[i] = point.x + point.y;
        diffF[i] = (i > 0) ? point.x - pointOld.x : 0;
    }

    int minSumIdx = min_element(sumF.begin(), sumF.end()) - sumF.begin();
    int minDiffIdx = min_element(diffF.begin(), diffF.end()) - diffF.begin();
    int maxSumIdx = max_element(sumF.begin(), sumF.end()) - sumF.begin();
    int maxDiffIdx = max_element(diffF.begin(), diffF.end()) - diffF.begin();

    ret[0] = pts.at<float>(minSumIdx);
    ret[1] = pts.at<float>(minDiffIdx);
    ret[2] = pts.at<float>(maxSumIdx);
    ret[3] = pts.at<float>(maxDiffIdx);
    return ret;
}

float max_distance(Point2f a1, Point2f a2, Point2f b1, Point2f b2) {
    float dist1 = norm(a1 - a2);
    float dist2 = norm(b1 - b2);

    return dist2 < dist1 ? int(dist1) : int(dist2);
}

Mat myocr::box_detection(Mat frame) {
    
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    frame = image_processing(frame);
    cv::findContours(frame, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
    size_t max = 0;
    for (size_t i = 0; i < contours.size(); i++) {
        if (contourArea(contours[max]) < contourArea(contours[i])) {
            max = i;
        }
        drawContours(frame, contours, (int)i, Scalar(255), 1, LINE_8, hierarchy, 0);
    }
    cv::imshow("frame", contours);
    cv::waitKey(0);
    RotatedRect rect = minAreaRect(contours[max]);
    Mat box;
    boxPoints(rect, box);
    return box;
}

Mat myocr::image_processing(Mat frame) {
    Mat grayFrame;
    cv::cvtColor(frame, grayFrame, COLOR_BGR2GRAY);
    /*imshow("frame", grayFrame);
    cv::waitKey(0);*/
    cv::GaussianBlur(grayFrame, grayFrame, Size(1, 1), 1000);
    /*imshow("frame", grayFrame);
    cv::waitKey(0);*/
    cv::threshold(grayFrame, grayFrame, 100, 255, THRESH_BINARY);
    /*imshow("frame", grayFrame);
    cv::waitKey(0);*/
    return grayFrame;
}

Mat myocr::fix_perspective(Mat frame, Mat pts) {
    vector<Vec2f> sortedPts = sort_points(pts);
    Vec2f tl = sortedPts[0];
    Vec2f tr = sortedPts[1];
    Vec2f br = sortedPts[2];
    Vec2f bl = sortedPts[3];

    float maxW = max_distance(br, bl, tr, tl);
    float maxH = max_distance(tr, br, tl, bl);

    vector<Point2f> dst = { Point2f(0, 0), Point2f(maxW - 1, 0), Point2f(maxW - 1, maxH - 1), Point2f(0, maxH - 1) };

    Mat transform = getPerspectiveTransform(vector<Point2f>{tl, tr, br, bl}, dst);
    Mat fixed = Mat::zeros(Size(maxW, maxH), frame.type());
    warpPerspective(frame, fixed, transform, fixed.size());

    return fixed;
}

