/**
* @Author: Marcel Ruhf <marcelruhf>
* @Date:   2017-02-07T11:12:16+00:00
* @Email:  marcel@marcelruhf.me
* @Project: SoccerRL
* @Filename: main.cpp
* @Last modified by:   marcelruhf
* @Last modified time: 2017-02-07T13:05:56+00:00
* @License: Licensed under the Apache 2.0 license (see LICENSE.md)
* @Copyright: Copyright (c) 2017 Marcel Ruhf
*/

/**
* This is a file that tests the tracking capability of the current classes:
* RobotTracker, which attempts to track the position of a robot using MarkerFinder
* MarkerFinder, which attempts to detect aruco markers
* BallTracker, which attempts to track the position of a yellow ball.
*/

#include <iostream>
#include "RobotTracker.cpp"
#include "BallTracker.cpp"
#include <opencv2/opencv.hpp>  // include everything, for simplicity...

using namespace std;

int main(int argc, char** argv) {
    // Instantiate classes
    RobotTracker robot;
    BallTracker ball;

    cv::VideoCapture cap;
    cap.open(0);  // try to start capturing from USB camera...

    if (!cap.isOpened()) {
        // Display an error, quit the application...
        cerr << "ERROR! Unable to open video stream!" << endl;
        return -1;
    } // otherwise, continue...

    cv::Mat frame;
    cv::namedWindow("Live", cv::WINDOW_AUTOSIZE);

    for (;;) {
        cap.read(frame);

        if (frame.empty()) {  // stop program execution, since camera disconnected...
            cout << "No more frames..." << endl;
            return 0;
        } // ... else, continue...

        robot.setImage(frame);  // set image to the current frame
        ball.setImage(frame);   // set image to the current frame

        // Retrieve contours
        auto robotCnts = robot.getPos();
        cout << "Size of robotCnts: " << robotCnts.size() << endl;
        auto ballCnts = ball.getPos();
        cout << "Size of ballCnts: " << ballCnts.size() << endl;

        // Draw contours
        cv::Mat newFrame = frame.clone();
        cv::drawContours(newFrame, robotCnts, -1, cv::Scalar(99), cv::FILLED);
        cv::drawContours(newFrame, ballCnts, -1, cv::Scalar(99), cv::FILLED);

        // Display
        cv::imshow("Live", newFrame);
        if (cv::waitKey(30) == 'q') {
            break;
        }
    }

    return 0;

}
