/**
* @Author: Marcel Ruhf <marcelruhf>
* @Email:  m.ruhf@protonmail.ch
* @Project: SoccerRL
* @Filename: main.cpp
* @License: Licensed under the Apache 2.0 license (see LICENSE.md)
* @Copyright: Copyright (c) 2017 Marcel Ruhf
*/

#ifndef SOCCERRL_CONSTANTS_H_
#define SOCCERRL_CONSTANTS_H_

#include <opencv2/core.hpp>

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
}  // namespace mr

#endif  // SOCCERRL_CONSTANTS_H_
