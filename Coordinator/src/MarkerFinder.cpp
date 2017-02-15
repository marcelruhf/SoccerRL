/**
* @Author: Marcel Ruhf <marcelruhf>
* @Date:   2017-01-27T21:04:39+00:00
* @Email:  marcel@marcelruhf.me
* @Project: SoccerRL
* @Filename: MarkerFinder.cpp
* @Last modified by:   marcel
* @Last modified time: 2017-02-15T22:22:23+00:00
* @License: Licensed under the Apache 2.0 license (see LICENSE.md)
* @Copyright: Copyright (c) 2017 Marcel Ruhf
*/

#include <iostream>
#include <vector>
#include <opencv2/imgproc.hpp>
#include <opencv2/aruco.hpp>

using namespace std;

#define MARKER_ID 29

class MarkerFinder {
private:
    cv::Mat image;
public:
    void setImage(cv::Mat);
    vector< vector<cv::Point2f> > getPos();
};

void MarkerFinder::setImage(cv::Mat img) {
    image = img;
}

vector< vector<cv::Point2f> > MarkerFinder::getPos() {
    vector<int> ids;
    vector< vector<cv::Point2f> > corners;
    cv::Ptr<cv::aruco::Dictionary> dict = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_7X7_50);
    cv::aruco::detectMarkers(image, dict, corners, ids);
    if (ids.at(0) == MARKER_ID || corners.size() == 0) {
        // Then it has successfully detected our robot...
        // ...or hasn't detected any
        return corners;
    }

    // Else, the corners vector contains rejected markers...
    // ...so reject them
    return vector< vector<cv::Point2f> >();
}
