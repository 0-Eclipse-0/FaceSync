//
// Haar Cascade Face Finder Class
//

#include "Face.h"

bool Face::getFace(Mat & faceImage, std::string & cascadeFile) {
    if (faceImage.empty()) { // empty matrix
        return false;
    }

    Mat thresh, grayscale, modified;
    std::vector<Rect> found;
    int increasePercentage = 15;
    Rect faceRect;

    // Prep image
    cvtColor(faceImage, grayscale, COLOR_BGR2GRAY);
    _cascade.detectMultiScale(grayscale, found, 1.1, 3, 0, cv::Size(30, 30)); // Detect face

    if (found.size() != 1) { // Multiple faces found
        return false;
    }

    faceRect = found[0];

    // Increase the size of the rectangle by 10% (ensure full face is encapsulated);
    int increaseHeight = static_cast<int>(faceRect.height * increasePercentage / 100.0);

    // Make sure the rectangle stays within the image bounds
    faceRect.y -= increaseHeight / 2;
    faceRect.height += increaseHeight;

    // Coordinates and measurements
    _height = faceRect.height;
    _width = faceRect.width;
    _x =  faceRect.x;
    _y =  faceRect.y;

    return true;
}
