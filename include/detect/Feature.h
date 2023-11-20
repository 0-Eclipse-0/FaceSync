//
// Created by Matthew Hambrecht on 11/13/23.
//

#ifndef FACESYNC_FEATURE_H
#define FACESYNC_FEATURE_H
#include <opencv2/opencv.hpp>
#include <string>
#include <exception>
#include <opencv2/highgui.hpp>
#include <opencv2/face/facerec.hpp>
#include "Image.h"

class Feature {
public:
    Feature();
    Feature(Image & faceImage, std::string & cascadeFile);
protected:
    Image * _faceImage;
    CascadeClassifier _cascade;

    // Measurements
    int _height;
    int _width;
    int _x;
    int _y;

    // Colors
    Scalar YELLOW = Scalar(255,255,0);
    Scalar LIME = Scalar(173,255,47);
    Scalar BLUE = Scalar(0,0,255);
    Scalar PURPLE = Scalar(138,43,226);
};


#endif //FACESYNC_FEATURE_H
