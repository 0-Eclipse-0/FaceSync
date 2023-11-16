//
// Created by Matthew Hambrecht on 11/14/23.
//

#ifndef FACESYNC_PEOPLE_H
#define FACESYNC_PEOPLE_H

#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/dnn.hpp>
#include "Image.h"
#include "Body.h"

using namespace std;
using namespace cv;
using namespace dnn;

class People {
public:
    People();
    People(const string & image, const string & config, const string & weights);
    void getPeople();
    void showPeople() const;
private:
    Image * _original;
    vector<Body> _bodies;
    dnn::Net _net;

    bool _loaded;
};


#endif //FACESYNC_PEOPLE_H
