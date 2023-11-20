//
// Created by Matthew Hambrecht on 11/13/23.
//

#ifndef FACESYNC_EYE_H
#define FACESYNC_EYE_H

#include "Feature.h"

using namespace cv;

class Eye : public Feature {
public:
    Eye() : Feature() {};
    Eye(Image & faceImage, std::string & cascadeFile) : Feature(faceImage, cascadeFile) {}
    bool getEyes();

private:
    int _heuristic;
};


#endif //FACESYNC_EYE_H
