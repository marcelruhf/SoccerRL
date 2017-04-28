/**
* @Author: Marcel Ruhf <marcelruhf>
* @Email:  m.ruhf@protonmail.ch
* @Project: SoccerRL
* @Filename: Constants.hpp
* @License: Licensed under the Apache 2.0 license (see LICENSE.md)
* @Copyright: Copyright (c) 2017 Marcel Ruhf
*/

#ifndef SOCCERRL_TRACKER_CONSTANTS_HPP_
#define SOCCERRL_TRACKER_CONSTANTS_HPP_

#include <opencv2/core.hpp>
#include <SarsaParams.hpp>

namespace mr
{
    const cv::Mat CAMERA_MATRIX = (cv::Mat1d(3,3) <<
            3.4102199103531979e+02, 0, 8.7588796819694096e+02,
            0, 8.2515646353052045e+02, 5.0852609779195620e+02,
            0, 0, 1
    );
    const cv::Mat DISTORTION_COEFFICIENTS = (cv::Mat1d(1,5) <<
            -3.6814669461805716e-01, -2.8082298275027154e-03,
            -6.6619218845551539e-02, -1.6078474996774328e-01,
            2.6155997675212489e-03
    );

    const double ONE_POUND_PIXELS   = 34.9;                                   // pixels
    const double ONE_POUND_DIAMETER = 22.5;                                   // milimetres
    const double PIXELS_PER_MM      = ONE_POUND_PIXELS / ONE_POUND_DIAMETER;  // pixels

    const short ROBOT_MARKER_ID       = 29;

    const short GOAL_LEFT_MARKER_ID   = 30;
    const short GOAL_CENTRE_MARKER_ID = 31;
    const short GOAL_RIGHT_MARKER_ID  = 32;

    const double EPSILON = 0.2;
    const SarsaParams SARSA_PARAMS = SarsaParams(0.4, 1, 0.99);

    const int NUM_EPISODES = 2000;
}  // namespace mr

#endif  // SOCCERRL_TRACKER_CONSTANTS_HPP_