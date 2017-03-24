/**
* @Author: Marcel Ruhf <marcelruhf>
* @Email:  m.ruhf@protonmail.ch
* @Project: SoccerRL
* @Filename: RobotTracker.cpp
* @License: Licensed under the Apache 2.0 license (see LICENSE.md)
* @Copyright: Copyright (c) 2017 Marcel Ruhf
*/

#include <iostream>
#include <vector>
#include <tuple>
#include <boost/optional.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include "MarkerFinder.hpp"
#include "RobotTracker.hpp"
#include "Constants.hpp"

namespace mr
{
    void RobotTracker::setImage(cv::Mat img)
    {
        image = img;
    }

    boost::optional< std::tuple<cv::Point2f, cv::Vec3d, cv::Vec3d> > RobotTracker::getPos()
    {
        marker.setImage(image);

        // Determine marker vertices, rotation and translation vectors...
        boost::optional< std::tuple< std::vector<cv::Point2f>, std::vector<cv::Vec3d>, std::vector<cv::Vec3d> > >
                markerPos = marker.getPos();

        if (!markerPos)
        {
            return boost::optional< std::tuple< cv::Point2f,
                    cv::Vec3d, cv::Vec3d > >{};
        }

        cv::Vec3d rvec = static_cast<cv::Vec3d>(std::get<1>(*markerPos).at(0));
        cv::Vec3d tvec = static_cast<cv::Vec3d>(std::get<2>(*markerPos).at(0));

        // Compute Centroid of the robot...
        cv::Moments mu = cv::moments(std::get<0>(*markerPos), true);
        cv::Point2f robot_centroid = cv::Point2f(mu.m10/mu.m00, mu.m01/mu.m00);

        return std::make_tuple(robot_centroid, rvec, tvec);
    }
}  // namespace mr