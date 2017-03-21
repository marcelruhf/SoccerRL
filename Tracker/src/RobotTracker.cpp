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

    std::tuple< cv::Point3f, std::vector<cv::Vec3d>, std::vector<cv::Vec3d> >
    RobotTracker::getPos()
    {
        marker.setImage(image);

        // Determine marker vertices, rotation and translation vectors...
        std::tuple< std::vector<cv::Point2f>, std::vector<cv::Vec3d>, std::vector<cv::Vec3d> >
                markerPos = marker.getPos();

        cv::Mat rotation_matrix;
        cv::Vec3d rvecs = std::get<1>(markerPos).at(0);
        cv::Vec3d tvecs = std::get<2>(markerPos).at(0);
        cv::Mat rvec2 = cv::Mat(3, 1, cv::DataType<double>::type);
        rvec2.at<double>(0, 0) = rvecs[0];
        rvec2.at<double>(1, 0) = rvecs[1];
        rvec2.at<double>(2, 0) = rvecs[2];
        cv::Mat tvec2 = cv::Mat(3, 1, cv::DataType<double>::type);
        tvec2.at<double>(0, 0) = tvecs[0];
        tvec2.at<double>(1, 0) = tvecs[1];
        tvec2.at<double>(2, 0) = tvecs[2];
        cv::Rodrigues(rvec2, rotation_matrix);

        // Compute Centroid of the robot...
        cv::Moments mu = cv::moments(std::get<0>(markerPos), true);
        cv::Point2f relative_robot_centroid = cv::Point2f(mu.m10/mu.m00, mu.m01/mu.m00);

        cv::Mat uvPoint = cv::Mat::ones(3, 1, cv::DataType<double>::type);
        uvPoint.at<double>(0, 0) = relative_robot_centroid.x;
        uvPoint.at<double>(1, 0) = relative_robot_centroid.y;

        cv::Mat rMat = rotation_matrix.inv() * CAMERA_MATRIX.inv() * uvPoint;
        cv::Mat tMat = rotation_matrix.inv() * tvec2;

        double s = tMat.at<double>(2, 0) / rMat.at<double>(2, 0);
        cv::Mat wcPoint = rotation_matrix.inv() * (s * CAMERA_MATRIX.inv() * uvPoint - tvecs);

        cv::Point3f robot_centroid = cv::Point3f(wcPoint.at<double>(0,0), wcPoint.at<double>(1,0), wcPoint.at<double>(2,0));

        // Return world coordinates for robot centroid, rotation and translation vectors...
        return std::make_tuple(robot_centroid, std::get<1>(markerPos), std::get<2>(markerPos));
    }
}  // namespace mr