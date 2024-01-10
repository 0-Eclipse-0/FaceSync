//
// Class for storing cctv infomration and feed
//

#include "CCTV.h"

CCTV::CCTV() {
    _url = "";
    _camera = {};
    _cctvName = "";
}

CCTV::~CCTV() {
    if (!_camera.isOpened()) {
        _camera.release();
    }
}

CCTV::CCTV(std::string cctvName, std::string url) {
    _url = url;
    _cctvName = cctvName;
    _camera = cv::VideoCapture(url);
}

cv::VideoCapture &CCTV::getCamera() {
    return _camera;
}

const std::string &CCTV::getCctvName() const {
    return _cctvName;
}