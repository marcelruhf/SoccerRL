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
        boost::optional<std::vector<cv::Point2f>> markerCorners;
        boost::optional<cv::Vec3d> rvec;
        boost::optional<cv::Vec3d> tvec;
    public:
        void setImage(cv::Mat);
        boost::optional<cv::Point2f> getCentrePoint();
        boost::optional<cv::Vec3d> getRotationVector();
        boost::optional<cv::Vec3d> getTranslationVector();
    };
}  // namespace mr

#endif  // SOCCERRL_TRACKER_ROBOTTRACKER_HPP_