/**
* @Author: Marcel Ruhf <marcelruhf>
* @Date:   2017-02-16T22:07:04+00:00
* @Email:  marcel@marcelruhf.me
* @Project: SoccerRL
* @Filename: BallTracker.hpp
* @Last modified by:   marcelruhf
* @Last modified time: 2017-02-19T17:49:53+00:00
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
        cv::Point2f getPos();  // Returns the position of the centre point of te ball to the caller
    };
}  // namespace mr

#endif
