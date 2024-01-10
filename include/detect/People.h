//
// Main class for storing people detected within an image
//

#ifndef FACESYNC_PEOPLE_H
#define FACESYNC_PEOPLE_H

#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
#include <filesystem>
#include <opencv2/highgui.hpp>
#include <opencv2/dnn.hpp>

#include "../device/Config.h"
#include "Body.h"
#include "../device/Log.h"

const float CONF_THRESHOLD = 0.4;
const float NMS_THRESHOLD = 0.5;

class People {
public:
    People();
    People(Config& config, cv::Mat& frame);
    void getPeople(Config& config);
    const std::vector<std::pair<int, int>>& getDetections() const;
    void getBounds(std::vector<int>& indices,
                   std::vector<cv::Rect>& boxes,
                   Config& config);
    void parseResults(std::vector<cv::Mat>& found,
                              std::vector<cv::Rect>& boxes,
                              std::vector<float>& confidences);

    friend class Stream;
    friend class Display;
private:
    cv::Mat * _original;
    std::vector<Body> _bodies;
    cv::dnn::Net _net;
    std::vector<cv::Rect> _rects;
    std::vector<std::pair<int, int>> _detections;
    bool _loaded;
};


#endif //FACESYNC_PEOPLE_H
