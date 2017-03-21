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

#include <iostream>
#include <tuple>
#include <vector>
#include <cmath>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include "BallTracker.hpp"
#include "Constants.hpp"

namespace mr
{
    void BallTracker::setImage(cv::Mat img)
    {
        src = img;
    }

    cv::Point3f BallTracker::getData()
    {
        cv::Mat image, mask;

        cv::Scalar thresh_lower = cv::Scalar(29, 86, 6);
        cv::Scalar thresh_upper = cv::Scalar(64, 255, 255);

        // Convert the image to HSV
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
        double largest_area = 0.0;
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
            std::vector<cv::Point> largest_contour = contours[largest_index];
            std::vector<cv::Point2f> contour_points(largest_contour.begin(), largest_contour.end());
            cv::Mat rotation_matrix, rvecs, tvecs;
            cv::solvePnP(contour_points, src, CAMERA_MATRIX, DISTORTION_COEFFICIENTS, rvecs, tvecs);
            cv::Rodrigues(rvecs, rotation_matrix);

            cv::Moments mu = cv::moments(contours[largest_index], true);
            cv::Point2f relative_ball_centroid = cv::Point2f(mu.m10/mu.m00, mu.m01/mu.m00);

            cv::Mat uvPoint = cv::Mat::ones(3, 1, cv::DataType<double>::type);
            uvPoint.at<double>(0, 0) = relative_ball_centroid.x;
            uvPoint.at<double>(1, 0) = relative_ball_centroid.y;

            cv::Mat rMat = rotation_matrix.inv() * CAMERA_MATRIX.inv() * uvPoint;
            cv::Mat tMat = rotation_matrix.inv() * tvecs;

            double s = tMat.at<double>(2, 0) / rMat.at<double>(2, 0);
            cv::Mat wcPoint = rotation_matrix.inv() * (s * CAMERA_MATRIX.inv() * uvPoint - tvecs);

            // Ball detected successfully, so return its center
            // and its velocity...
            return cv::Point3f(wcPoint.at<double>(0,0), wcPoint.at<double>(1,0), wcPoint.at<double>(2,0));;
        }

        return cv::Point3f();  // no ball present, return negative result
    }
}