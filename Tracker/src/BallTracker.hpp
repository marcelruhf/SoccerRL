/**
* @Author: Marcel Ruhf <marcelruhf>
* @Email:  m.ruhf@protonmail.ch
* @Project: SoccerRL
* @Filename: BallTracker.hpp
* @License: Licensed under the Apache 2.0 license (see LICENSE.md)
* @Copyright: Copyright (c) 2017 Marcel Ruhf
*/

#ifndef SOCCERRL_TRACKER_BALLTRACKER_HPP_
#define SOCCERRL_TRACKER_BALLTRACKER_HPP_

#include <boost/optional.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>

namespace mr
{
    class BallTracker
    {
    private:
        cv::Mat src;  // Holds the image provided by the caller (either a static image or a video frame)
        boost::optional<cv::Point2f> previous;  // Previous centre point of ball
        boost::optional<cv::Point2f> current;  // Current centre point
    public:
        void setImage(cv::Mat);  // Replaces the stored image within the object (used by the caller)
        std::vector< std::vector<cv::Point> > getPossibleContours();
        boost::optional<cv::Point2f> getCentrePoint();  // Returns the position of the centre point of te ball
        int getVelocity();  // Returns velocity of the ball
    };
}

#endif  // SOCCERRL_TRACKER_BALLTRACKER_HPP_
