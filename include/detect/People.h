//
// Created by Matthew Hambrecht on 11/14/23.
//

#ifndef FACESYNC_PEOPLE_H
#define FACESYNC_PEOPLE_H

#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
#include <filesystem>
#include <opencv2/highgui.hpp>
#include <opencv2/dnn.hpp>
#include "../device/Config.h"
#include "Image.h"
#include "Body.h"

using namespace std;
using namespace cv;
using namespace dnn;

class People {
public:
    People();
    People(Config& config, const Mat& frame);
    ~People();
    void getPeople(Config& config);
    void showPeople() const;
    friend class Stream;
private:
    Image * _original;
    vector<Body> _bodies;
    dnn::Net _net;
    vector<Rect> _rects;

    bool _loaded;
};


#endif //FACESYNC_PEOPLE_H
