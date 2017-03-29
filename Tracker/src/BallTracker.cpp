/**
* @Author: Marcel Ruhf <marcelruhf>
* @Email:  m.ruhf@protonmail.ch
* @Project: SoccerRL
* @Filename: BallTracker.cpp
* @License: Licensed under the Apache 2.0 license (see LICENSE.md)
* @Copyright: Copyright (c) 2017 Marcel Ruhf
*/

/**
* This class implements a ball tracking mechanism by thresholding the image
* based on its HSV color space values (using a lower and upper limit).
* Hough transformations were previously considered as well, but I determined
* that the method implemented here is more suitable for this project.
*/

#include <boost/optional.hpp>
#include <cmath>
#include <opencv2/opencv.hpp>
#include "Constants.hpp"
#include "Functions.hpp"
#include "BallTracker.hpp"

namespace mr
{
    void BallTracker::setImage(cv::Mat img)
    {
        src = img;
    }

    int BallTracker::getVelocity()
    {
        if (!previous || !current)
        {
            return 0;
        }
        double distTravelled = distEuclidMM(*previous, *current);
        return static_cast<int>(std::roud(distTravelled));
    }

    std::vector< std::vector<cv::Point> > BallTracker::getPossibleContours()
    {
        cv::Mat image, mask;

        cv::Scalar thresh_lower = cv::Scalar(29, 86, 6);
        cv::Scalar thresh_upper = cv::Scalar(64, 255, 255);

        // Convert the image to HSV
        cv::cvtColor(src, image, cv::COLOR_BGR2HSV);

        // Create a "range" for the green color
        cv::inRange(image, thresh_lower, thresh_upper, mask);
        cv::erode(mask, mask, cv::Mat(), cv::Point(-1, -1), 3);
        cv::dilate(mask, mask, cv::Mat(), cv::Point(-1, -1), 3);

        // Initialize contours vector
        std::vector< std::vector<cv::Point> > contours;
        std::vector<cv::Vec4i> hierarchy;

        // Compute contours
        cv::findContours(mask, contours, hierarchy,
                         cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

        return contours;
    }

    boost::optional<cv::Point2f> BallTracker::getCentrePoint()
    {
        cv::Mat image, mask;

        cv::Scalar thresh_lower = cv::Scalar(29, 86, 6);
        cv::Scalar thresh_upper = cv::Scalar(64, 255, 255);

        // Convert the image to HSV
        cv::cvtColor(src, image, cv::COLOR_BGR2HSV);

        // Create a "range" for the green color
        cv::inRange(image, thresh_lower, thresh_upper, mask);
        cv::erode(mask, mask, cv::Mat(), cv::Point(-1, -1), 3);
        cv::dilate(mask, mask, cv::Mat(), cv::Point(-1, -1), 3);

        // Initialize contours vector
        std::vector< std::vector<cv::Point> > contours;
        std::vector<cv::Vec4i> hierarchy;

        // Compute contours
        cv::findContours(mask, contours, hierarchy,
                         cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

        // Compute the largest contour
        double largest_area = 0.0;
        int largest_index = -1;
        if (contours.size() > 0)
        {
            for (int i = 0; i < contours.size(); ++i)
            {
                std::vector<cv::Point> approx;
                cv::approxPolyDP(contours.at(i), approx,
                                 0.04*cv::arcLength(contours.at(i), true), true);
                if (approx.size() == 3 || approx.size() == 4 || approx.size() == 5)
                {
                    continue;
                }
                double area = cv::contourArea(contours.at(i));
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
            std::vector<cv::Point> largest_contour = contours[largest_index];
            cv::Moments mu = cv::moments(contours[largest_index], true);
            cv::Point2f ball_centroid = cv::Point2f(mu.m10/mu.m00, mu.m01/mu.m00);
            if (!current)
            {
                *current = ball_centroid;
            }
            else if (!previous)
            {
                *previous = *current;
            }
            else
            {
                *previous = *current;
                *current = ball_centroid;
            }
            return ball_centroid;
        }

        return boost::optional<cv::Point2f>{};  // no ball present, return negative result
    }
}