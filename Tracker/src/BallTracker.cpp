/**
* @Author: Marcel Ruhf <marcelruhf>
* @Date:   2017-01-28T08:34:17+00:00
* @Email:  marcel@marcelruhf.me
* @Project: SoccerRL
* @Filename: BallTracker.cpp
* @Last modified by:   marcelruhf
* @Last modified time: 2017-02-16T14:02:06+00:00
* @License: Licensed under the Apache 2.0 license (see LICENSE.md)
* @Copyright: Copyright (c) 2017 Marcel Ruhf
*/

/**
* This class implements a ball tracking mechanism by thresholding the image
* based on its HSV color space values (using a lower and upper limit).
* Hough transformations were previously considered as well, but I determined
* that the method implemented here is more suitable for this project.
*/

#include <iostream>
#include <tuple>
#include <vector>
#include <opencv2/imgproc.hpp>
#include "BallTracker.hpp"

namespace mr
{
    void BallTracker::setImage(cv::Mat img)
    {
        src = img;
    }

    cv::Point2f BallTracker::getPos()
    {
        cv::Mat image, mask;

        cv::Scalar thresh_lower = cv::Scalar(29, 86, 6);
        cv::Scalar thresh_upper = cv::Scalar(64, 255, 255);

        // Convert the image to grayscale
        cv::cvtColor(src, image, cv::COLOR_BGR2HSV);

        // Create a "range" for the green color
        cv::inRange(image, thresh_lower, thresh_upper, mask);
        cv::erode(mask, mask, cv::Mat());
        cv::dilate(mask, mask, cv::Mat());

        // Initialize contours vector
        std::vector< std::vector<cv::Point> > contours;
        std::vector<cv::Vec4i> hierarchy;

        // Compute contours
        cv::findContours(mask, contours, hierarchy,
          cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

        // Compute the largest contour
        int largest_area = -1;
        int largest_index = -1;
        if (contours.size() > 0)
        {
            for (int i = 0; i < contours.size(); ++i)
            {
                double area = cv::contourArea(contours[i]);
                if (area > largest_area)
                {
                    largest_area = area;
                    largest_index = i;
                }
            }
        }

        // Now, use momets to get the center of the image
        if (largest_index >= 0)
        {
            mu = cv::moments(contours[largest_index], true);
            return cv::Point2f(mu.m10/mu.m00, mu.m01/mu.m00);
        }

        return cv::Point2f(-1, -1);  // no ball present, return negative result
    }
}  // namespace mr
