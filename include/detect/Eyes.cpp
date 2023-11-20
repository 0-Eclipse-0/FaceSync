//
// Created by Matthew Hambrecht on 11/19/23.
//

#include "Eyes.h"

Eyes::Eyes() {
    _frame = nullptr;
    _loaded = false;
    _cascade = {};
}

Eyes::Eyes(Mat & frame, std::string & cascadeFile) {
    _frame = &frame;
    _loaded = false;
    _cascade.load(cascadeFile);

    getEyes();
}

void Eyes::getEyes() {
    if (_frame == nullptr) { // No image loaded
        return;
    }

    std::vector<Rect> found;
    _cascade.detectMultiScale(*_frame, found);

    if (found.size() != 2) { // Eyes found must be equal to two
        return;
    }

    for (auto const& rect : found) { // Store eye location data
        _eyes.emplace_back(Eye(rect.x, rect.y, rect.height, rect.width));
    }

    _loaded = true;
}

bool Eyes::getLoaded() const {
    return _loaded;
}

std::vector <Eye> Eyes::returnEyes() {
    return _eyes;
}