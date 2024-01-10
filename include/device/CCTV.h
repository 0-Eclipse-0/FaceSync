//
// Class for storing cctv infomration and feed
//

#ifndef FACESYNC_CCTV_H
#define FACESYNC_CCTV_H

#include <string>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <exception>
#include <utility>

class CCTV {
public:
    CCTV();
    CCTV(std::string cctvName, std::string url);
    ~CCTV();

    // Accessors and Mutators
    cv::VideoCapture &getCamera();
    const std::string &getCaptureUrl() const;
    const std::string &getCctvName() const;
    void setCctvName(const std::string &cctvName);

private:
    cv::VideoCapture _camera;
    std::string _url;
    std::string _cctvName;
};


#endif //FACESYNC_CCTV_H
