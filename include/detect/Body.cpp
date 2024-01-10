//
// Body class for handling detections and their bounding boxes
//

#include "Body.h"

Body::Body(cv::Mat& body, Config& config, int x, int y, int height, int width) {
    _body = body;

    _x = x;
    _y = y;
    _height = height;
    _width = width;
};

void Body::drawBody(cv::Mat& frame) { //  Overlay known features on image
    // Draw body rectangle
    cv::Rect bodyRectangle = cv::Rect(_x, _y, _width, _height);
    rectangle(frame,
              bodyRectangle,
              cv::Scalar(0, 165, 255),
              2);
}