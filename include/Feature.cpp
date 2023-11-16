//
// Created by Matthew Hambrecht on 11/13/23.
//

#include "Feature.h"

Feature::Feature() {
    _faceImage = nullptr;
}

Feature::Feature(Image & faceImage, string & cascadeFile) {
    _faceImage = &faceImage;
    _cascade.load(cascadeFile);

    _height = 0;
    _width = 0;
    _x = 0;
    _y = 0;
}