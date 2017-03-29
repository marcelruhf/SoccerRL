/**
* @Author: Marcel Ruhf <marcelruhf>
* @Email:  m.ruhf@protonmail.ch
* @Project: SoccerRL
* @Filename: Functions.cpp
* @License: Licensed under the Apache 2.0 license (see LICENSE.md)
* @Copyright: Copyright (c) 2017 Marcel Ruhf
*/

#include <cmath>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/optional.hpp>
#include <opencv2/opencv.hpp>
#include "RobotTracker.hpp"
#include "BallTracker.hpp"
#include "Constants.hpp"
#include "Functions.hpp"

namespace mr
{
    template <typename T> int signum(T val) {
        return (T(0) < val) - (val < T(0));
    }

    double distEuclidPixels(cv::Point2f p1, cv::Point2f p2)
    {
        return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
    }

    double distEuclidMM(cv::Point2f p1, cv::Point2f p2)
    {
        double distPx = distEuclidPixels(p1, p2);
        return (distPx / PIXELS_PER_MM);
    }

    void get_vars(int vars_array[2], const cv::Mat& src, const RobotTracker& robot, const BallTracker& ball)
    {
        //double len1 = std::hypot(robot_centroid.x, robot_centroid.y);
        //double len2 = std::hypot(ball_centroid.x, ball_centroid.y);
        //double dot = robot_centroid.ddot(ball_centroid);
        //double a = dot/(len1*len2);
        //double arb = acos(a) / (180 * 3.141592653589793);
        //root.add("arb", arb);

        // Determine distance between robot and ball in terms of the X axis
        boost::optional<cv::Point2f> ball_centroid = ball.getCentrePoint();
        boost::optional<cv::Point2f> robot_centroid = robot.getCentrePoint();
        if (!ball_centroid || !robot_centroid)
        {
            vars_array = {0, 0};
        }
        else
        {
            double drbx = ((*ball_centroid).x - (*robot_centroid).x) / PIXELS_PER_MM;
            vars_array[0] = std::round(drbx);
            vars_array[1] = ball.getVelocity();
        }
    }
}