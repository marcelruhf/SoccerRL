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
    void RobotTracker::preprocess(cv::Mat image)
    {
        marker.preprocess(image);

        // Determine marker vertices, rotation and translation vectors...
        markerCorners = marker.getCorners(ROBOT_MARKER_ID);
        rvec = marker.getRotationVector(ROBOT_MARKER_ID);
        tvec = marker.getTranslationVector(ROBOT_MARKER_ID);
    }

    boost::optional<cv::Vec3d> RobotTracker::getRotationVector()
    {
        return rvec;
    }

    boost::optional<cv::Vec3d> RobotTracker::getTranslationVector()
    {
        return tvec;
    }

    boost::optional<cv::Point2f> RobotTracker::getCentrePoint()
    {
        if (!markerCorners)
        {
            return boost::optional<cv::Point2f>{};
        }

        // Compute Centroid of the robot...
        cv::Moments mu              = cv::moments(*markerCorners, true);
        cv::Point2f robot_centroid  = cv::Point2f(mu.m10/mu.m00, mu.m01/mu.m00);

        return robot_centroid;
    }
}  // namespace mr