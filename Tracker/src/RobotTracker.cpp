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
#include <opencv2/imgproc.hpp>
#include "MarkerFinder.hpp"
#include "RobotTracker.hpp"

namespace mr
{
    void RobotTracker::setImage(cv::Mat img)
    {
        image = img;
    }

    std::tuple< cv::Point2f, std::vector<cv::Vec3d>, std::vector<cv::Vec3d>, std::vector< std::vector<cv::Point2f> > >
    RobotTracker::getPos()
    {
        marker.setImage(image);

        // Determine marker vertices, rotation and translation vectors...
        std::tuple< std::vector<cv::Point2f>, std::vector<cv::Vec3d>, std::vector<cv::Vec3d>, std::vector< std::vector<cv::Point2f> > >
                markerData = marker.getData();

        // Compute Centroid of the robot...
        cv::Moments mu = cv::moments(std::get<0>(markerData), true);
        cv::Point2f robotCentroid = cv::Point2f(mu.m10/mu.m00, mu.m01/mu.m00);

        // Return robot centroid, rotation and translation matrix...
        return std::make_tuple(robotCentroid, std::get<1>(markerData), std::get<2>(markerData), std::get<3>(markerData));
    }
}  // namespace mr