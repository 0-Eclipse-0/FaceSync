//
// Created by Matthew Hambrecht on 11/13/23.
//

#include "Face.h"

bool Face::getFace() {
    if (_faceImage == nullptr) { // No image loaded
        return false;
    }

    Mat thresh, grayscale, modified;
    vector<Rect> found;

    // Prep image
    cvtColor(*_faceImage->_image, grayscale, COLOR_BGR2GRAY);
    _cascade.detectMultiScale(grayscale, found, 1.1, 3, 0, cv::Size(30, 30)); // Detect face

    if (found.size() != 1) { // Multiple faces found
        return false;
    }

    Rect faceRect = found[0];

    // Increase the size of the rectangle by 10% (ensure full face is encapsulated);
    int increasePercentage = 15;
    int increaseHeight = static_cast<int>(faceRect.height * increasePercentage / 100.0);

    // Make sure the rectangle stays within the image bounds
    faceRect.y -= increaseHeight / 2;
    faceRect.height += increaseHeight;

    // Draw ellipse
    Point center(faceRect.x + faceRect.width / 2, faceRect.y + faceRect.height / 2);
    Size axes(faceRect.width / 2.5, faceRect.height / 2); //  2 and 2.5 to account for ears

    // Coordinates and measurements
    int _height = faceRect.height;
    int _width = faceRect.width;
    int _x =  faceRect.x;
    int _y =  faceRect.y;

    ellipse(*_faceImage->_image, center, axes, 0, 0, 360, PURPLE, 2);

    return true;
}
