/**
* @Author: Marcel Ruhf <marcelruhf>
* @Date:   2017-01-27T21:04:39+00:00
* @Email:  marcel@marcelruhf.me
* @Project: SoccerRL
* @Filename: MarkerFinder.cpp
* @Last modified by:   marcelruhf
* @Last modified time: 2017-02-16T14:29:27+00:00
* @License: Licensed under the Apache 2.0 license (see LICENSE.md)
* @Copyright: Copyright (c) 2017 Marcel Ruhf
*/

#include <iostream>
#include <vector>
#include <opencv2/imgproc.hpp>
#include <opencv2/aruco.hpp>
#include "MarkerFinder.hpp"

namespace mr
{
    void MarkerFinder::setImage(cv::Mat img)
    {
        image = img;
    }

    std::vector< std::vector<cv::Point2f> > MarkerFinder::getPos()
    {
        std::vector<int> ids;
        std::vector< std::vector<cv::Point2f> > corners;
        cv::Ptr<cv::aruco::Dictionary> dict = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_7X7_50);
        cv::aruco::detectMarkers(image, dict, corners, ids);

        if (ids.size() > 0)
        {
            if (ids.at(0) == MARKER_ID)
            {
                // Then it has successfully detected our robot...
                // ...or hasn't detected any
                return corners;
            }
        }

        // Else, the corners vector contains rejected markers...
        // ...so reject them
        return std::vector< std::vector<cv::Point2f> >();
    }
}  // namespace mr
