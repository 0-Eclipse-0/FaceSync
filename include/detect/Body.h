//
// Created by Matthew Hambrecht on 11/14/23.
//

#ifndef FACESYNC_BODY_H
#define FACESYNC_BODY_H

#include "../device/Config.h"
#include <opencv2/opencv.hpp>
#include <string>
#include <exception>
#include <opencv2/highgui.hpp>
#include <opencv2/face/facerec.hpp>

using namespace cv;

class Body {
public:
    Body();
    Body(Mat& body, Config& config, int x, int y, int height, int width);
    Mat returnBody();
    void showBody() const;
    void drawBody(Mat& frame);
    const Mat &getBody() const;
    void setBody(const Mat &body);
    bool isLoaded() const;
    void setLoaded(bool loaded);

private:
    Mat _body{};
    bool _loaded{};

    // Attributes
    int _x;
    int _y;
    int _height;
    int _width;
};


#endif //FACESYNC_BODY_H
