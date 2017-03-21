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
#include "BallTracker.hpp"
#include "RobotTracker.hpp"
#include "Constants.hpp"

std::string data_string(
        const cv::Mat& src,
        const std::tuple< cv::Point2f, std::vector<cv::Vec3d>, std::vector<cv::Vec3d> >& robot_position,
        const std::tuple< cv::Point2f, double >& ball_data)
{
    // TODO: Needs to be completed after managing to compute angles
    boost::property_tree::ptree root;  // root element for json

    cv::Point2f robot_centroid = std::get<0>(robot_position);
    cv::Point2f ball_centroid = std::get<0>(ball_data);
    double len1 = hypot(robot_centroid.x, robot_centroid.y);
    double len2 = hypot(ball_centroid.x, ball_centroid.y);
    double dot = robot_centroid.ddot(ball_centroid);

    double a = dot/(len1*len2);

    double arb = acos(a) / (180 * 3.141592653589793);

    root.add("arb", arb);

    return "";
}

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

    //boost::asio::io_service io_service;
    //boost::asio::ip::tcp::socket socket(io_service);
    //boost::asio::ip::tcp::resolver resolver(io_service);
    //boost::asio::ip::tcp::resolver::iterator endpoint;

    try
    {
        //endpoint = resolver.resolve(boost::asio::ip::tcp::resolver::query("localhost", "2323"));
        //boost::system::error_code connect_error, write_error;
        //boost::asio::connect(socket, endpoint, connect_error);

        // Check if connection was established successfully, else quit
        /*
        if (connect_error != 0)
        {
            std::cerr << "ERROR: Unable to connect!" << std::endl;
            std::cerr << "Exiting now..." << std::endl;
            return 1;
        }
        */

        for (;;)
        {
            cap.read(frame);

            if (frame.empty())
            {  // stop program execution, since camera disconnected...
                std::cout << "No more frames..." << std::endl;
                return 0;
            }  // ... else, continue...

            cv::imwrite("/users/marcelruhf/Documents/output2.jpg", frame);
            std::cout << "Written" << std::endl;
            break;

            robot.setImage(frame);  // set image to the current frame
            ball.setImage(frame);   // set image to the current frame

            //std::tuple< cv::Point3f, std::vector<cv::Vec3d>, std::vector<cv::Vec3d> > rdata = robot.getPos();
            //std::vector<cv::Vec3d> rvecs = (std::vector<cv::Vec3d>) std::get<1>(rdata);
            //std::vector<cv::Vec3d> tvecs = (std::vector<cv::Vec3d>) std::get<2>(rdata);
            //std::cout << "rvecs size: " << rvecs.size() << std::endl;
            //std::cout << rvecs.at(0) << std::endl;
            //cv::Point3f ball_center = ball.getData();
            //std::cout << "Coordinates: (" << ball_center.x << "," << ball_center.y << "," << ball_center.z << ")" << std::endl;

            //if (rvecs.size() > 0 && tvecs.size() > 0)
                //cv::aruco::drawAxis(frame, mr::CAMERA_MATRIX, mr::DISTORTION_COEFFICIENTS, rvecs.at(0), tvecs.at(0), 0.1);

            //std::string message = data_string(frame, robot.getPos(), ball.getData());
            //std::cout << message << std::endl;
            //boost::asio::write(socket, boost::asio::buffer(message), write_error);
            cv::imshow("Live", frame);
            if (cv::waitKey(5) == 'q') break;
        }

        //boost::system::error_code close_error;
        //socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, close_error);
        //socket.close();
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
