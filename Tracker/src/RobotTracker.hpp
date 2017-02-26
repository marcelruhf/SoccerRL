/**
* @Author: Marcel Ruhf <marcelruhf>
* @Date:   2017-02-16T21:54:26+00:00
* @Email:  marcel@marcelruhf.me
* @Project: SoccerRL
* @Filename: RobotTracker.hpp
* @Last modified by:   marcelruhf
* @Last modified time: 2017-02-19T17:52:18+00:00
* @License: Licensed under the Apache 2.0 license (see LICENSE.md)
* @Copyright: Copyright (c) 2017 Marcel Ruhf
*/

#ifndef SOCCERRL_COORDINATOR_ROBOTTRACKER_H_
#define SOCCERRL_COORDINATOR_ROBOTTRACKER_H_

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
    public:
        void setImage(cv::Mat);
        std::vector< std::vector<cv::Point2f> > getPos();
    };
}

#endif
