//
// Created by Matthew Hambrecht on 11/14/23.
//

#ifndef FACESYNC_BODY_H
#define FACESYNC_BODY_H

#include "Image.h"
#include "Face.h"
#include "Eye.h"
#include <opencv2/opencv.hpp>
#include <string>
#include <exception>
#include <opencv2/highgui.hpp>
#include <opencv2/face/facerec.hpp>

using namespace std;
using namespace cv;

class Body {
public:
    Body();
    Body(Mat & body);
    void getBody(Mat body);
    void getFeatures();
    Mat returnBody();
    void showBody() const;
private:
    Mat _body;
    Face _face{};
    Eye _eye{};
    bool _loaded{};
};


#endif //FACESYNC_BODY_H
