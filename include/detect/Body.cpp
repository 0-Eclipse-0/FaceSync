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
    _config = config;

    _face = Face(_body, config.returnConfig()["faceFrontCascade"]);
    _eyes = Eyes(_body, config.returnConfig()["eyeCascade"]);

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

    // Draw face
    if (_face.getLoaded()) {
        Point center(_x + _face.getX() + _face.getWidth() / 2,
                     _y + _face.getY() + _face.getHeight() / 2);
        Size axes(_face.getWidth() / 2.5,
                  _face.getHeight() / 2);
        ellipse(frame, center, axes,
                0, 0, 360,
                Scalar(138,43, 226), 2);
    }

    if (_eyes.getLoaded()) {
        for (auto const& eye : _eyes.returnEyes()) {
            Point center(_x +eye.getX() + eye.getWidth() / 2, _y + eye.getY() + eye.getHeight() / 2);
            Size axes(eye.getWidth() / 2, eye.getHeight() / 4);

            ellipse(frame, center, axes, 0, 0, 360, Scalar(0, 255, 0), 2);
        }
    }
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