//
// Created by Matthew Hambrecht on 12/2/23.
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

void CCTV::testCCTV() { // View stream (debugging purposes)
    if (!_camera.isOpened() || _url == "") { // Invalid stream
        throw std::runtime_error("[Error] Stream failed to open, check path: \"" + _url +"\"");
    }

    cv::Mat frame;
    namedWindow("CCTV_1", cv::WINDOW_NORMAL);

    while (true) { // Open stream window (100 frames)
        if (!_camera.read(frame)) {
            throw std::runtime_error("[Error] Frame read failed...");
        }

        // Test one frame
        putText(frame,
                _cctvName,
                cv::Point(15, 15),
                cv::FONT_HERSHEY_PLAIN,
                1.0,
                CV_RGB(0,255,0),
                2.0);
        cv::imshow("CCTV (Debug)", frame);

        if (cv::waitKey(1) == 'q') { // 'q' to close
            break;
        }
    }

    cv::destroyAllWindows();
}

cv::VideoCapture &CCTV::getCamera() {
    return _camera;
}

void CCTV::setCamera(const cv::VideoCapture &camera) {
    CCTV::_camera = camera;
}

const std::string &CCTV::getCaptureUrl() const {
    return _url;
}

void CCTV::setCaptureUrl(const std::string &captureUrl) {
    _url = captureUrl;
}

const std::string &CCTV::getCctvName() const {
    return _cctvName;
}

void CCTV::setCctvName(const std::string &cctvName) {
    _cctvName = cctvName;
}