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
    Feature(Mat & frame, std::string & cascadeFile);

    // Accessors and mutators
    int getHeight() const;
    void setHeight(int height);
    int getWidth() const;
    void setWidth(int width);
    int getX() const;
    void setX(int x);
    int getY() const;
    void setY(int y);
    bool getLoaded() const;

protected:
    Mat * _frame;
    CascadeClassifier _cascade;
    bool _loaded;

    // Attributes
    int _height;
    int _width;
    int _x;
    int _y;
};


#endif //FACESYNC_FEATURE_H
