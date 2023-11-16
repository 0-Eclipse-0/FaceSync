//
// Created by Matthew Hambrecht on 11/13/23.
//

#include "Eye.h"

bool Eye::getEyes() {
    if (_faceImage == nullptr) { // No image loaded
        return false;
    }

    vector<Rect> found;
    _cascade.detectMultiScale(*_faceImage->_image, found);

    if (found.size() != 2) {
        return false;
    }

    for (const auto& eye : found) { // Draw ellipse around eye
        Point center(eye.x + eye.width / 2, eye.y + eye.height / 2);
        Size axes(eye.width / 2, eye.height / 4);

        ellipse(*_faceImage->_image, center, axes, 0, 0, 360, LIME, 2);
    }

    return true;
}
