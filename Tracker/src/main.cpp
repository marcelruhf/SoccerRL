/**
* @Author: Marcel Ruhf <marcelruhf>
* @Email:  m.ruhf@protonmail.ch
* @Project: SoccerRL
* @Filename: main.cpp
* @License: Licensed under the Apache 2.0 license (see LICENSE.md)
* @Copyright: Copyright (c) 2017 Marcel Ruhf
*/

/**
* This file raws the contours retrieved from the marker and ball trackers onto
* each frame and displays it to the user of the application.
* It is being used, at the moment, for testing purposes only;
* I will eventually replace it with a server providing the coordinates to the
* robot.
*/

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <opencv2/opencv.hpp>  // include everything, for simplicity...
#include <opencv2/aruco.hpp>
#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/optional.hpp>
#include "BallTracker.hpp"
#include "RobotTracker.hpp"
#include "Constants.hpp"
#include "Functions.hpp"

int main(int argc, char **argv)
{
    // Instantiate classes
    mr::RobotTracker robot;
    mr::BallTracker ball;
    cv::VideoCapture cap;
    cap.set(cv::CAP_PROP_FPS, 25);  // Allows us to calculate velocity...

    cap.open(0);  // try to start capturing from USB camera...
    if (!cap.isOpened())
    {
        // Display an error, quit the application...
        std::cerr << "ERROR! Unable to open video stream!" << std::endl;
        return -1;
    }  // otherwise, continue...

    cv::Mat frame;
    cv::namedWindow("Live", cv::WINDOW_GUI_NORMAL);

    boost::asio::io_service io_service;
    boost::asio::ip::tcp::socket socket(io_service);
    boost::asio::ip::tcp::resolver resolver(io_service);
    boost::asio::ip::tcp::resolver::iterator endpoint;

    try
    {
        endpoint = resolver.resolve(boost::asio::ip::tcp::resolver::query("localhost", "2323"));
        boost::system::error_code connect_error, write_error;
        boost::asio::connect(socket, endpoint, connect_error);

        // Check if connection was established successfully, else quit
        if (connect_error.value() != boost::system::errc::success)
        {
            std::cerr << "ERROR: Unable to connect!" << std::endl;
            std::cerr << "Exiting now..." << std::endl;
            return 1;
        }

        for (;;)
        {
            cap.read(frame);

            if (frame.empty())
            {  // stop program execution, since camera disconnected...
                std::cout << "No more frames..." << std::endl;
                return 0;
            }  // ... else, continue...

            robot.setImage(frame);  // set image to the current frame
            ball.setImage(frame);   // set image to the current frame

            boost::optional< std::tuple< cv::Point2f, cv::Vec3d, cv::Vec3d > >
                    rdata = robot.getPos();

            cv::Point2f robot_centroid;
            cv::Vec3d   rvec;
            cv::Vec3d   tvec;
            cv::Point2f ball_centroid;

            // If rdata is NULL, no robot was found, so skip the loop...
            if (rdata)
            {
                robot_centroid      = static_cast<cv::Point2f>(std::get<0>(*rdata));
                rvec                = static_cast<cv::Vec3d>(std::get<1>(*rdata));
                tvec                = static_cast<cv::Vec3d>(std::get<2>(*rdata));

                cv::aruco::drawAxis(frame, mr::CAMERA_MATRIX, mr::DISTORTION_COEFFICIENTS, rvec, tvec, 0.1);
            }
            else
            {
                std::cout << "No robot found" << std::endl;
                continue;
            }

            boost::optional<cv::Point2f> bdata = ball.getPos();

            // If ball_centre is NULL, no ball was found
            if (bdata)
            {
                ball_centroid = static_cast<cv::Point2f>(*bdata);
                std::cout << "Coordinates: (" << ball_centroid.x << "," << ball_centroid.y << ")" << std::endl;
            }
            else
            {
                std::cout << "No ball found" << std::endl;
                continue;
            }

            if (rdata && bdata)
            {
                cv::arrowedLine(frame, robot_centroid, ball_centroid, cv::Scalar(0,0,0));
                std::string message = mr::data_string(frame, robot_centroid, rvec, tvec, ball_centroid);
                //std::cout << message << std::endl;
                boost::asio::write(socket, boost::asio::buffer(message), write_error);

                if (write_error.value() != boost::system::errc::success)
                {
                    std::cerr << "ERROR: Unable to send message!" << std::endl;
                    std::cerr << "Exiting now..." << std::endl;
                    break;
                }
            }

            cv::imshow("Live", frame);
            if (cv::waitKey(0) == 'q' || cv::waitKey(0) == 27) break;
        }

        boost::system::error_code close_error;
        socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, close_error);
        socket.close();
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}