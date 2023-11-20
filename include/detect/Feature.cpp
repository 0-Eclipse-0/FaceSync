//
// Created by Matthew Hambrecht on 11/13/23.
//

#include "Feature.h"

Feature::Feature() {
    _frame = nullptr;
}

Feature::Feature(Mat & frame, std::string & cascadeFile) {
    _frame = &frame;
    _loaded = false;
    _cascade.load(cascadeFile);

    _height = 1;
    _width = 1;
    _x = 1;
    _y = 1;
}

int Feature::getHeight() const {
    return _height;
}

void Feature::setHeight(int height) {
    _height = height;
}

int Feature::getWidth() const {
    return _width;
}

void Feature::setWidth(int width) {
    _width = width;
}

int Feature::getX() const {
    return _x;
}

void Feature::setX(int x) {
    _x = x;
}

int Feature::getY() const {
    return _y;
}

void Feature::setY(int y) {
    _y = y;
}

bool Feature::getLoaded() const {
    return _loaded;
}