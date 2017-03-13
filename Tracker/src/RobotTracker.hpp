/**
* @Author: Marcel Ruhf <marcelruhf>
* @Email:  m.ruhf@protonmail.ch
* @Project: SoccerRL
* @Filename: RobotTracker.hpp
* @License: Licensed under the Apache 2.0 license (see LICENSE.md)
* @Copyright: Copyright (c) 2017 Marcel Ruhf
*/

#ifndef SOCCERRL_COORDINATOR_ROBOTTRACKER_H_
#define SOCCERRL_COORDINATOR_ROBOTTRACKER_H_

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
        std::tuple< cv::Point2f, std::vector<cv::Vec3d>, std::vector<cv::Vec3d>, std::vector< std::vector<cv::Point2f> > > getPos();
    };
}  // namespace mr

#endif