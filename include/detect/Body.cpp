//
// Created by Matthew Hambrecht on 11/14/23.
//

#include "Body.h"

Body::Body() {
    _loaded = false;
};

Body::Body(Mat& body, Config& config, int x, int y, int height, int width) {
    _body = body;
    _loaded = true;

    _x = x;
    _y = y;
    _height = height;
    _width = width;
};

Mat Body::returnBody() {
    return _body;
}

void Body::drawBody(Mat& frame) { //  Overlay known features on image
    // Draw body rectangle
    Rect bodyRectangle = Rect(_x, _y, _width, _height);
    rectangle(frame,
              bodyRectangle,
              Scalar(0, 165, 255),
              2);
}

void Body::showBody() const { // DEBUG
    if (!_loaded) {
        return;
    }

    if (!_body.empty()) {
        imshow("Debug (Body)", _body);
        waitKey(0);
        destroyAllWindows();
    }
}

const Mat &Body::getBody() const {
    return _body;
}

void Body::setBody(const Mat &body) {
    _body = body;
}

bool Body::isLoaded() const {
    return _loaded;
}

void Body::setLoaded(bool loaded) {
    _loaded = loaded;
}