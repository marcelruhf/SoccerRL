/**
* @Author: Marcel Ruhf <marcelruhf>
* @Date:   2017-02-16T22:00:59+00:00
* @Email:  marcel@marcelruhf.me
* @Project: SoccerRL
* @Filename: MarkerFinder.hpp
* @Last modified by:   marcelruhf
* @Last modified time: 2017-02-19T17:51:23+00:00
* @License: Licensed under the Apache 2.0 license (see LICENSE.md)
* @Copyright: Copyright (c) 2017 Marcel Ruhf
*/

#ifndef SOCCERRL_COORDINATOR_MARKERFINDER_H_
#define SOCCERRL_COORDINATOR_MARKERFINDER_H_

#define MARKER_ID 29

#include <vector>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>

namespace mr
{
    class MarkerFinder
    {
    private:
        cv::Mat image;
    public:
        void setImage(cv::Mat);
        std::vector< std::vector<cv::Point2f> > getPos();
    };
}  // namespace mr

#endif
