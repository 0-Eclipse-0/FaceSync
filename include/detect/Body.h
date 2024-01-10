//
// Body class for handling detections and their bounding boxes
//

#ifndef FACESYNC_BODY_H
#define FACESYNC_BODY_H

#include "../device/Config.h"
#include <opencv2/opencv.hpp>
#include <string>
#include <exception>
#include <opencv2/highgui.hpp>
#include <opencv2/face/facerec.hpp>

class Body {
public:
    Body(cv::Mat& body, Config& config, int x, int y, int height, int width);
    void drawBody(cv::Mat& frame);
private:
    cv::Mat _body{};

    // Attributes
    int _x;
    int _y;
    int _height;
    int _width;
};


#endif //FACESYNC_BODY_H
