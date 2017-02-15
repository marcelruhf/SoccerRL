/**
* @Author: Marcel Ruhf <marcelruhf>
* @Date:   2017-01-26T17:36:58+00:00
* @Email:  marcel@marcelruhf.me
* @Project: SoccerRL
* @Filename: RobotTracker.cpp
* @Last modified by:   marcel
* @Last modified time: 2017-02-15T22:20:03+00:00
* @License: Licensed under the Apache 2.0 license (see LICENSE.md)
* @Copyright: Copyright (c) 2017 Marcel Ruhf
*/

#include <iostream>
#include <vector>
#include <tuple>
#include <opencv2/imgproc.hpp>
#include "MarkerFinder.cpp"

using namespace std;

class RobotTracker {
private:
    cv::Mat image;
    MarkerFinder marker;
public:
    void setImage(cv::Mat);
    vector< vector<cv::Point2f> > getPos();
};

void RobotTracker::setImage(cv::Mat img) {
    image = img;
}

vector< vector<cv::Point2f> > RobotTracker::getPos() {
    //cv::Mat thrImg;
    //cv::cvtColor(this->image, thrImg, cv::COLOR_BGR2GRAY);
    //cv::threshold(thrImg, thrImg, 128, 255, cv::THRESH_BINARY);
    marker.setImage(image);
    return marker.getPos();
}
