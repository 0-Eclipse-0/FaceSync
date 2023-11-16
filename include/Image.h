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

using namespace std;
using namespace cv;

const double SCALE = 1.0;

class Image {
public:
    Image();
    Image(string path);
    ~Image();
    void viewImage();
    void loadImage(const string& path);
    void deleteImages();
    friend class Eye;
    friend class Face;
    friend class People;
private:
    Mat * _image = nullptr;
};


#endif //FACESYNC_IMAGE_H
