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
#include <chrono>
#include <thread>
#include <opencv2/opencv.hpp>  // include everything, for simplicity...
#include <opencv2/aruco.hpp>
#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/optional.hpp>
#include "BallTracker.hpp"
#include "RobotTracker.hpp"
#include "Functions.hpp"
#include "Constants.hpp"

int main(int argc, char **argv)
{
    // Instantiate classes
    mr::RobotTracker robot;
    mr::BallTracker ball;
    cv::VideoCapture cap;

    cap.open(1);  // try to start capturing from USB camera...
    if (!cap.isOpened())
    {
        // Display an error, quit the application...
        std::cerr << "ERROR! Unable to open video stream!" << std::endl;
        return 1;
    }  // otherwise, continue...

    cv::Mat frame;
    //cv::namedWindow("Live", cv::WINDOW_GUI_NORMAL);

    cap.read(frame);
    boost::optional<cv::Point2f> goalCentrePoint = mr::initialize_goal_centre(frame);

    if (!goalCentrePoint)
    {
        std::cerr << "ERROR! Unable to initialize goal centre point!" << std::endl;
        std::cerr << "Exiting now..." << std::endl;
        return 1;
    }  // Goal marker wasn't found, so exit...

    std::cout << "Goal centre initialized, press any key to start server..." << std::endl;
    std::cin.get();
    bool robotInPosition = false;

    try
    {
        boost::asio::io_service io_service;
        boost::asio::ip::tcp::socket socket(io_service);
        boost::asio::ip::tcp::acceptor acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 2323));
        boost::system::error_code write_error;

        std::cout << "Waiting for a connection..." << std::endl;
        acceptor.accept(socket);
        std::cout << "Connection established." << std::endl;

        while (!robotInPosition)
        {
            cap.read(frame);

            if (frame.empty())
            {  // stop program execution, since camera disconnected...
                std::cout << "No more frames..." << std::endl;
                return 1;
            }  // ... else, continue...

            robot.preprocess(frame);

            if (!robot.getCentrePoint())
            {
                std::cout << "Waiting for robot..." << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                continue;
            }

            std::string message;

            int distance = static_cast<int>(std::fabs((std::floor(robot.getCentrePoint()->x) - std::floor(goalCentrePoint->x))/mr::PIXELS_PER_MM));

            if (distance > 10 && (robotInPosition == false))
            {
                if (std::floor(robot.getCentrePoint()->x) < std::floor(goalCentrePoint->x))
                {
                    message = "w";
                }
                else if (std::floor(robot.getCentrePoint()->x) > std::floor(goalCentrePoint->x))
                {
                    message = "s";
                }
                else
                {
                    std::cerr << "ERROR! Something went wrong with the calculations!" << std::endl;
                    std::cerr << "Exiting now..." << std::endl;
                    return 1;
                }
            }
            else
            {
                robotInPosition = true;
                message = "z";
            }

            boost::asio::write(socket, boost::asio::buffer(message), write_error);
            if (write_error.value() != boost::system::errc::success)
            {
                std::cerr << "ERROR: Unable to send message!" << std::endl;
                std::cerr << "Exiting now..." << std::endl;
                return 1;
            }
        }

        for (;;)
        {
            cap.read(frame);

            if (frame.empty())
            {  // stop program execution, since camera disconnected...
                std::cout << "No more frames..." << std::endl;
                return 1;
            }  // ... else, continue...

            std::string message;
            int vars_array[2] = {0};

            mr::get_vars(vars_array, frame, robot, ball);

            if (vars_array[1] == 0) {
                message = "z";
            } else {
                if (vars_array[0] < 0) {
                    message = "s";
                } else if (vars_array[0] > 0) {
                    message = "w";
                } else {
                    message = "z";
                }
            }

            boost::asio::write(socket, boost::asio::buffer(message), write_error);

            if (write_error.value() != boost::system::errc::success)
            {
                std::cerr << "ERROR: Unable to send message!" << std::endl;
                std::cerr << "Exiting now..." << std::endl;
                return 1;
            }

            //cv::imshow("Live", frame);
            if (cv::waitKey(1) == 'q' || cv::waitKey(1) == 27) break;
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