/**
* @Author: Marcel Ruhf <marcelruhf>
* @Email:  m.ruhf@protonmail.ch
* @Project: SoccerRL
* @Filename: RobotTracker.hpp
* @License: Licensed under the Apache 2.0 license (see LICENSE.md)
* @Copyright: Copyright (c) 2017 Marcel Ruhf
*/

#ifndef SOCCERRL_TRACKER_ROBOTTRACKER_HPP_
#define SOCCERRL_TRACKER_ROBOTTRACKER_HPP_

#include <vector>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include "MarkerFinder.hpp"

namespace mr
{
    class RobotTracker
    {
    private:
        cv::Mat image;
        MarkerFinder marker;
    public:
        void setImage(cv::Mat);
        std::tuple< cv::Point3f, std::vector<cv::Vec3d>, std::vector<cv::Vec3d> > getPos();
    };
}  // namespace mr

#endif  // SOCCERRL_TRACKER_ROBOTTRACKER_HPP_