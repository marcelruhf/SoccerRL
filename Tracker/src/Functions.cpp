/**
* @Author: Marcel Ruhf <marcelruhf>
* @Email:  m.ruhf@protonmail.ch
* @Project: SoccerRL
* @Filename: Functions.cpp
* @License: Licensed under the Apache 2.0 license (see LICENSE.md)
* @Copyright: Copyright (c) 2017 Marcel Ruhf
*/

#include <cmath>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <opencv2/opencv.hpp>
#include "Constants.hpp"
#include "Functions.hpp"

namespace mr
{
    double distEuclidPixels(cv::Point2f p1, cv::Point2f p2)
    {
        return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
    }

    double distEuclidMM(cv::Point2f p1, cv::Point2f p2)
    {
        double distPx = distEuclidPixels(p1, p2);
        return (distPx / PIXELS_PER_MM);
    }

    std::string data_string(
        const cv::Mat&     src,
        const cv::Point2f& robot_centroid,
        const cv::Vec3d&   rvec,
        const cv::Vec3d&   tvec,
        const cv::Point2f& ball_centroid
    )
    {
        boost::property_tree::ptree root;  // root element for json

        // Calculate distance between ball and
        double drb = distEuclidMM(robot_centroid, ball_centroid);
        if (std::floor(std::fabs(drb)) == 0)
        {
            root.add("drb", 0);
        }
        else
        {
            root.add("drb", std::floor(drb));
        }

        //double len1 = std::hypot(robot_centroid.x, robot_centroid.y);
        //double len2 = std::hypot(ball_centroid.x, ball_centroid.y);
        //double dot = robot_centroid.ddot(ball_centroid);
        //double a = dot/(len1*len2);
        //double arb = acos(a) / (180 * 3.141592653589793);
        //root.add("arb", arb);

        // Determine distance between robot and ball in terms of the X axis
        double drbx = (ball_centroid.x - robot_centroid.x) / PIXELS_PER_MM;
        if (std::floor(std::fabs(drbx)) == 0)
        {
            root.add("drbx", 0);
        }
        else
        {
            root.add("drbx", std::floor(drbx));
        }

        std::ostringstream buf;
        boost::property_tree::write_json(buf, root);

        return buf.str();
    }
}