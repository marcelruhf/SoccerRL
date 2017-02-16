#ifndef SOCCERRL_COORDINATOR_ROBOTTRACKER_H_
#define SOCCERRL_COORDINATOR_ROBOTTRACKER_H_

class RobotTracker {
private:
    cv::Mat image;
    MarkerFinder marker;
public:
    void setImage(cv::Mat);
    vector< vector<cv::Point2f> > getPos();
};

#endif
