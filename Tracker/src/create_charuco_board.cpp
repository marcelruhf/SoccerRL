/**
* @Author: Marcel Ruhf <marcelruhf>
* @Date:   2017-02-20T15:03:02+00:00
* @Email:  marcel@marcelruhf.me
* @Project: SoccerRL
* @Filename: create_charuco_board.cpp
* @Last modified by:   marcel
* @Last modified time: 2017-02-20T15:41:47+00:00
* @License: Licensed under the Apache 2.0 license (see LICENSE.md)
* @Copyright: Copyright (c) 2017 Marcel Ruhf
*/

/**
* This file is used to generate a charuco board,
* which is is used to calibrate the camera and
* retrieve the camera and distortion matrices.
This is necessary to estimate the orientation
* of the robot, which is positioned on the "pitch".
*/

#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include <opencv2/aruco/charuco.hpp>

int main(int argc, char** argv)
{
    cv::Ptr<cv::aruco::Dictionary> dict = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_7X7_50);
    cv::Ptr<cv::aruco::CharucoBoard> board = cv::aruco::CharucoBoard::create(8, 8, 0.04, 0.02, dict);
    cv::Mat boardImage;
    board->draw( cv::Size(600, 600), boardImage, 10, 1);
    cv::imwrite("/users/marcel/Downloads/charuco.jpg", boardImage);
}
