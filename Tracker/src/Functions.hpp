/**
* @Author: Marcel Ruhf <marcelruhf>
* @Email:  m.ruhf@protonmail.ch
* @Project: SoccerRL
* @Filename: Functions.hpp
* @License: Licensed under the Apache 2.0 license (see LICENSE.md)
* @Copyright: Copyright (c) 2017 Marcel Ruhf
*/

#ifndef SOCCERRL_TRACKER_FUNCTIONS_HPP_
#define SOCCERRL_TRACKER_FUNCTIONS_HPP_

#include <opencv2/opencv.hpp>

namespace mr
{
    double distEuclidPixels(cv::Point2f p1, cv::Point2f p2);
    double distEuclidMM(cv::Point2f p1, cv::Point2f p2);
    std::string data_string(
        const cv::Mat&     src,
        const cv::Point2f& robot_centroid,
        const cv::Vec3d&   rvec,
        const cv::Vec3d&   tvec,
        const cv::Point2f& ball_centroid
    );
}

#endif  // SOCCERRL_TRACKER_FUNCTIONS_HPP_
