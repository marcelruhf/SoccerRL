/**
* @Author: Marcel Ruhf <marcelruhf>
* @Date:   2017-01-28T08:34:17+00:00
* @Email:  marcel@marcelruhf.me
* @Project: SoccerRL
* @Filename: BallTracker.cpp
* @Last modified by:   marcelruhf
* @Last modified time: 2017-02-07T12:34:10+00:00
* @License: Licensed under the Apache 2.0 license (see LICENSE.md)
* @Copyright: Copyright (c) 2017 Marcel Ruhf
*/

#include <iostream>
#include <tuple>
#include <vector>
#include <opencv2/imgproc.hpp>

using namespace std;

class BallTracker {
private:
    cv::Mat image;
public:
    void setImage(cv::Mat);
    vector< vector<cv::Point> > getPos();
};

void BallTracker::setImage(cv::Mat img) {
    image = img;
}

vector< vector<cv::Point> > BallTracker::getPos() {
    cv::Mat thrImg;
    cv::cvtColor(this->image, thrImg, cv::COLOR_BGR2HSV);
    cv::inRange(thrImg, cv::Scalar(20,100,100), cv::Scalar(30,255,255), thrImg);
    vector< vector<cv::Point> > contours;
    vector<cv::Vec4i> hierarchy;
    cv::findContours(thrImg, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    return contours;
}
