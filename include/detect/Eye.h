//
// Created by Matthew Hambrecht on 11/13/23.
//

#ifndef FACESYNC_EYE_H
#define FACESYNC_EYE_H

#include "Feature.h"

using namespace cv;

class Eye : public Feature {
public:
    Eye() {};
    Eye(int x, int y, int height, int width);
private:
};


#endif //FACESYNC_EYE_H
