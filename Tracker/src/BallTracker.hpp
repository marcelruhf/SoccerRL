/**
* @Author: Marcel Ruhf <marcelruhf>
* @Email:  m.ruhf@protonmail.ch
* @Project: SoccerRL
* @Filename: BallTracker.hpp
* @License: Licensed under the Apache 2.0 license (see LICENSE.md)
* @Copyright: Copyright (c) 2017 Marcel Ruhf
*/

#ifndef SOCCERRL_COORDINATOR_BALLTRACKER_H_
#define SOCCERRL_COORDINATOR_BALLTRACKER_H_

#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>

namespace mr
{
    class BallTracker
    {
    private:
        cv::Mat src;  // Holds the image provided by the caller (either a static image or a video frame)
    public:
        void setImage(cv::Mat);  // Replaces the stored image within the object (used by the caller)
        cv::Point2f getData();  // Returns the position of the centre point of te ball and its velocity to the caller
    };
}

#endif
