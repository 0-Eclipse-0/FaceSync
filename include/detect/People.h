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
#include "Body.h"
#include "../device/Log.h"

using namespace std;
using namespace cv;
using namespace dnn;

class People {
public:
    People();
    People(Config& config, Mat& frame);
    void getPeople(Config& config);
    void showPeople() const;
    Mat *getOriginal() const;
    void setOriginal(Mat *original);
    const vector<Body> &getBodies() const;
    void setBodies(const vector<Body> &bodies);
    const Net &getNet() const;
    void setNet(const Net &net);
    const vector<Rect> &getRects() const;
    void setRects(const vector<Rect> &rects);
    bool isLoaded() const;
    void setLoaded(bool loaded);
    const vector<pair<int, int>> &getDetections() const;
    void setDetections(const vector<pair<int, int>> &detections);

    friend class Stream;
    friend class Display;
private:
    Mat * _original;
    vector<Body> _bodies;
    dnn::Net _net;
    vector<Rect> _rects;
    vector<pair<int, int>> _detections;
    bool _loaded;
};


#endif //FACESYNC_PEOPLE_H
