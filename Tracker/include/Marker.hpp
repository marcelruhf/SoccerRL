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

#include <tuple>
#include <vector>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>

namespace mr
{
    class MarkerFinder
    {
    private:
        std::vector<int> ids;
        std::vector< std::vector<cv::Point2f> > corners;
        std::vector<cv::Vec3d> rvecs, tvecs;
    public:
        void preprocess(const cv::Mat&);
        boost::optional<std::vector<cv::Point2f>> getCorners(const int&);
        boost::optional<cv::Vec3d> getRotationVector(const int&);
        boost::optional<cv::Vec3d> getTranslationVector(const int&);
    };
}

#endif  // SOCCERRL_TRACKER_MARKERFINDER_HPP_