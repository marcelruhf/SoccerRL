/**
* @Author: Marcel Ruhf <marcelruhf>
* @Date:   2017-01-28T08:34:17+00:00
* @Email:  marcel@marcelruhf.me
* @Project: SoccerRL
* @Filename: BallTracker.cpp
* @Last modified by:   marcel
* @Last modified time: 2017-02-15T21:33:22+00:00
* @License: Licensed under the Apache 2.0 license (see LICENSE.md)
* @Copyright: Copyright (c) 2017 Marcel Ruhf
*/

/**
* This file uses Hough Circle Transformation to detect the presence of a ball.
* My previous implementation attampted to detect the presence of a ball by applying
* thresholding to a transformed image in HSV color space (hue, saturation, value).
* This was achieved by specifying a range within the HSV color space, and blackening
* everything not within that range so that only the object being tracked is visible.
* However, upon closer inspection, it became clear that colors vary from time to time,
* depending on room brightness (i.e. sunlight coming in at different levels throughout the day).
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

vector<cv::Vec3f> BallTracker::getPos()
{
    cv::Mat image;

    // Convert the image to grayscale (improves )
    cv::cvtColor(src, image, cv::COLOR_BGR2HSV);

    // Blur the image, to remove noise
    cv::GaussianBlur(image, image, cv::Size(5, 5), 0, 0);

    // Initialize circles vector
    vectr<cv:Vec3f> circles;

    // Perform Hough Circle Transformation
    cv::HoughCircles(image, circles, cv::HOUGH_GRADIENT, 2, image.cols/10);

    // For now, return the circles vector; will later be replaced with position on the matrix...
    return cirlces;
}
