/**
* @Author: Marcel Ruhf <marcelruhf>
* @Email:  m.ruhf@protonmail.ch
* @Project: SoccerRL
* @Filename: MarkerFinder.cpp
* @License: Licensed under the Apache 2.0 license (see LICENSE.md)
* @Copyright: Copyright (c) 2017 Marcel Ruhf
*/

#include <tuple>
#include <vector>
#include <boost/optional.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include "MarkerFinder.hpp"
#include "Constants.hpp"

namespace mr
{
    void MarkerFinder::preprocess(const cv::Mat& image)
    {
        cv::Ptr<cv::aruco::Dictionary> dict = cv::aruco::getPredefinedDictionary(
                cv::aruco::DICT_7X7_50
        );
        cv::aruco::detectMarkers(image, dict, corners, ids);
        cv::aruco::estimatePoseSingleMarkers(corners, 0.05, CAMERA_MATRIX, DISTORTION_COEFFICIENTS, rvecs, tvecs);
    }

    boost::optional<std::vector<cv::Point2f>> MarkerFinder::getCorners(const int& markerId)
    {
        for (int i = 0; i < ids.size(); ++i)
        {
            if (ids.at(i) == markerId)
            {
                return corners.at(i);
            }
        }
        return boost::optional<std::vector<cv::Point2f>>{};
    }

    boost::optional<cv::Vec3d> MarkerFinder::getRotationVector(const int& markerId)
    {
        for (int i = 0; i < ids.size(); ++i)
        {
            if (ids.at(i) == markerId)
            {
                return rvecs.at(i);
            }
        }
        return boost::optional<cv::Vec3d>{};
    }

    boost::optional<cv::Vec3d> MarkerFinder::getTranslationVector(const int& markerId)
    {
        for (int i = 0; i < ids.size(); ++i)
        {
            if (ids.at(i) == markerId)
            {
                return tvecs.at(i);
            }
        }
        return boost::optional<cv::Vec3d>{};
    }
}