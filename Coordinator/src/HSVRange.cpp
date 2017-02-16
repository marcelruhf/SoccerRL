/**
* @Author: Marcel Ruhf <marcel>
* @Date:   2017-02-16T11:53:56+00:00
* @Email:  marcel@marcelruhf.me
* @Project: SoccerRL
* @Filename: HSVRange.cpp
* @Last modified by:   marcel
* @Last modified time: 2017-02-16T12:17:08+00:00
* @License: Licensed under the Apache 2.0 license (see LICENSE.md)
* @Copyright: Copyright (c) 2017 Marcel Ruhf
*/

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

#define IMG "/users/marcel/Downloads/ball.jpg"

using namespace std;

int main(int argc, char** argv)
{
    cv::Mat image = cv::imread(IMG);
    cv::cvtColor(image, image, cv::COLOR_BGR2HSV);
    vector<cv::Mat> hsv_planes;
    cv::split(image, hsv_planes);
    cv::Mat hue = hsv_planes[0];
    cv::imwrite("/users/marcel/Downloads/ball_hue.jpg", hue);
}
