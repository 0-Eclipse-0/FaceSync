/*
 * Image class for storing base face image
 * */

#ifndef FACESYNC_IMAGE_H
#define FACESYNC_IMAGE_H
#include <opencv2/opencv.hpp>
#include <string>
#include <exception>
#include <opencv2/highgui.hpp>
#include <opencv2/face/facerec.hpp>

using namespace cv;

const double SCALE = 1.0;

class Image {
public:
    Image();
    Image(const std::string& path);
    Image(const Mat& mat);
    ~Image();
    void viewImage();
    void loadImage(const std::string& path);
    void deleteImages();
    Mat returnFrame();
    friend class Eye;
    friend class Face;
    friend class People;
private:
    Mat * _image = nullptr;
};


#endif //FACESYNC_IMAGE_H
