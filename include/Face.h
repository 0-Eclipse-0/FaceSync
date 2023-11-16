//
// Created by Matthew Hambrecht on 11/13/23.
//

#ifndef FACESYNC_FACE_H
#define FACESYNC_FACE_H
#include "Feature.h"

using namespace std;
using namespace cv;

class Face : public Feature {
public:
    Face() : Feature() {};
    Face(Image & faceImage, string & cascadeFile) : Feature(faceImage, cascadeFile) {}
    bool getFace();

private:
};


#endif //FACESYNC_FACE_H
