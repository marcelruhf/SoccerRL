/**
* @Author: Marcel Ruhf <marcelruhf>
* @Email:  m.ruhf@protonmail.ch
* @Project: SoccerRL
* @Filename: MarkerFinder.hpp
* @License: Licensed under the Apache 2.0 license (see LICENSE.md)
* @Copyright: Copyright (c) 2017 Marcel Ruhf
*/

#ifndef SOCCERRL_TRACKER_MARKERFINDER_HPP_
#define SOCCERRL_TRACKER_MARKERFINDER_HPP_

#define MARKER_ID 29

#include <tuple>
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
        std::tuple< std::vector<cv::Point2f>, std::vector<cv::Vec3d>, std::vector<cv::Vec3d> > getPos();
    };
}

#endif  // SOCCERRL_TRACKER_MARKERFINDER_HPP_