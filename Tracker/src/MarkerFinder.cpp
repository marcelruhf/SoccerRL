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
#include <opencv2/imgproc.hpp>
#include <opencv2/aruco.hpp>
#include "MarkerFinder.hpp"
#include "Constants.hpp"

namespace mr
{
    void MarkerFinder::setImage(cv::Mat img)
    {
        image = img;
    }

    std::tuple< std::vector<cv::Point2f>, std::vector<cv::Vec3d>, std::vector<cv::Vec3d> >
    MarkerFinder::getPos()
    {
        std::vector<int> ids;
        std::vector< std::vector<cv::Point2f> > corners;
        cv::Ptr<cv::aruco::Dictionary> dict = cv::aruco::getPredefinedDictionary(
                cv::aruco::DICT_7X7_50
        );
        cv::aruco::detectMarkers(image, dict, corners, ids);

        if (ids.size() == 1)
        {
            if (ids.at(0) == MARKER_ID)
            {
                // Then it has successfully detected our robot...
                std::vector<cv::Vec3d> rvecs, tvecs;
                cv::aruco::estimatePoseSingleMarkers(corners, 0.05, CAMERA_MATRIX, DISTORTION_COEFFICIENTS, rvecs, tvecs);

                return std::make_tuple(corners.at(0), rvecs, tvecs);
            }
        }

        // Else, the corners vector contains rejected or no markers...
        // ...so reject them
        return std::make_tuple(std::vector<cv::Point2f>(), std::vector<cv::Vec3d>(), std::vector<cv::Vec3d>());
    }
}