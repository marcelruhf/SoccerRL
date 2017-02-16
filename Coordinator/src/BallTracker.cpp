/**
* @Author: Marcel Ruhf <marcelruhf>
* @Date:   2017-01-28T08:34:17+00:00
* @Email:  marcel@marcelruhf.me
* @Project: SoccerRL
* @Filename: BallTracker.cpp
* @Last modified by:   marcel
* @Last modified time: 2017-02-16T14:02:06+00:00
* @License: Licensed under the Apache 2.0 license (see LICENSE.md)
* @Copyright: Copyright (c) 2017 Marcel Ruhf
*/

/**
* This class implements a ball tracking mechanism by thresholding the image
* based on its HSV color space values (using a lower and upper limit).
* Hough transformations were previously considered as well, but I determined
* that the method implemented here is more suitable for this project.
*/

#include <iostream>
#include <tuple>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;

class BallTracker {
private:
    cv::Mat src;  // Holds the image provided by the caller (either a static image or a video frame)
public:
    void setImage(cv::Mat);  // Replaces the stored image within the object (used by the caller)
    vector< vector<cv::Point> > getPos();  // Returns the position of the centre point of te ball to the caller
};

void BallTracker::setImage(cv::Mat img)
{
    src = img;
}

vector< vector<cv::Point> > BallTracker::getPos()
{
    cv::Mat image, mask;

    cv::Scalar thresh_lower = cv::Scalar(29, 86, 6);
    cv::Scalar thresh_upper = cv::Scalar(64, 255, 255);

    // Convert the image to grayscale (improves )
    cv::cvtColor(src, image, cv::COLOR_BGR2HSV);

    // Create a "range" for the green color
    cv::inRange(image, thresh_lower, thresh_upper, mask);
    cv::erode(mask, mask, cv::Mat());
    cv::dilate(mask, mask, cv::Mat());

    // Initialize contours vector
    vector< vector<cv::Point> > contours;
    vector<cv::Vec4i> hierarchy;

    // Compute contours
    cv::findContours(mask, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // For now, return the circles vector; will later be replaced with position on the matrix...
    return contours;
}
