#ifndef SOCCERRL_COORDINATOR_MARKERFINDER_H_
#define SOCCERRL_COORDINATOR_MARKERFINDER_H_

#define MARKER_ID 29

class MarkerFinder {
private:
    cv::Mat image;
public:
    void setImage(cv::Mat);
    vector< vector<cv::Point2f> > getPos();
};

#endif
