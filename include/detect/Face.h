//
// Haar Cascade Face Finder Class
//

#ifndef FACESYNC_FACE_H
#define FACESYNC_FACE_H
#include "Feature.h"

using namespace cv;

class Face : public Feature {
public:
    Face() : Feature() {};
    Face(Mat& frame, std::string& cascadeFile) : Feature(frame, cascadeFile) {
        _loaded = getFace(frame, cascadeFile);
    }

private:
    bool getFace(Mat & faceImage, std::string& cascadeFile);
};


#endif //FACESYNC_FACE_H
