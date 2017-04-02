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

#include <string>
#include <opencv2/opencv.hpp>
#include "RobotTracker.hpp"
#include "BallTracker.hpp"

namespace mr
{
    template <typename T> int signum(T val);
    double distEuclidPixels(cv::Point2f p1, cv::Point2f p2);
    double distEuclidMM(cv::Point2f p1, cv::Point2f p2);
    boost::optional<cv::Point2f> initialize_goal_centre(const cv::Mat& frame);
    void get_vars(int vars_array[2], const cv::Mat& src, RobotTracker& robot, BallTracker& ball);
}

#endif  // SOCCERRL_TRACKER_FUNCTIONS_HPP_
