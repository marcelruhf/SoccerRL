#ifndef SOCCERRL_COORDINATOR_BALLTRACKER_H_
#define SOCCERRL_COORDINATOR_BALLTRACKER_H_

class BallTracker {
private:
    cv::Mat src;  // Holds the image provided by the caller (either a static image or a video frame)
public:
    void setImage(cv::Mat);  // Replaces the stored image within the object (used by the caller)
    vector< vector<cv::Point> > getPos();  // Returns the position of the centre point of te ball to the caller
};

#endif
