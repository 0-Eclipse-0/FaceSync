/*
 * Image class for storing base face image
 * */

#include "Image.h"

Image::Image(string path) {
    loadImage(path);
}

Image::Image() {
    _image = nullptr;
}

Image::~Image() {
    deleteImages();
}

void Image::loadImage(const string& path) {
    // Clear existing memory
    deleteImages();

    Mat * loaded = new Mat(imread(path));

    if (loaded->empty()) { // Ensure image was loaded properly
        delete loaded;
        _image = nullptr;
        return;
    }

    _image = loaded;
}

void Image::viewImage() {
    if (_image) { // Ensure not nullptr
        namedWindow("Debug (Base)");
        imshow("Debug (Base)", *_image);
        waitKey(0);
        destroyWindow("Debug (Base)");
    }
}

void Image::deleteImages() { // Clear all memory
    if (_image) {
        delete _image;
        _image = nullptr;
    }
}
