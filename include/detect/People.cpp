//
// Main class for storing people detected within an image
//

#include "People.h"

People::People() {
    _original = nullptr;
}

People::People(Config& config, cv::Mat& frame) {
    _original = &frame;
    _loaded = false;
    _net = cv::dnn::readNetFromDarknet(config.returnConfig()["yoloConfig"],
                                       config.returnConfig()["yoloWeight"]);

    // Preparation
    _net.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
    _net.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);

    getPeople(config);
}

// Parse results from dnn test
void People::parseResults(std::vector<cv::Mat>& found,
                          std::vector<cv::Rect>& boxes,
                          std::vector<float>& confidences) {
    for (const auto &item: found) { // Get results from detection
        auto *data = (float *) item.data;

        for (int j = 0; j < item.rows; ++j, data += item.cols) {
            cv::Mat scores = item.row(j).colRange(5, item.cols);
            cv::Point classIdPoint;
            double confidence;

            minMaxLoc(scores,
                      0,
                      &confidence,
                      &classIdPoint);

            if (confidence > CONF_THRESHOLD && classIdPoint.x == 1) { // 1 is "person" in dataset
                int centerX = static_cast<int>(data[0]    // get coords
                                               * _original->cols);
                int centerY = static_cast<int>(data[1]
                                               * _original->rows);
                int width = static_cast<int>(data[2]
                                             * _original->cols);
                int height = static_cast<int>(data[3]
                                              * _original->rows);

                int left = centerX - width / 2;
                int top = centerY - height / 2;

                confidences.emplace_back(static_cast<float>(confidence));
                boxes.emplace_back(left, top, width, height);
            }
        }
    }
}

// Convert bounding boxes to rectangles
void People::getBounds(std::vector<int>& indices,
                       std::vector<cv::Rect>& boxes,
                       Config& config) {
    for (const auto &index: indices) { // Crop bodies and add to body count
        // Add coords to detections
        _detections.emplace_back(boxes[index].x, boxes[index].y);

        if (boxes[index].x >= 0 && boxes[index].y >= 0 && // verify box size is within bounds
            boxes[index].x + boxes[index].width <= _original->cols &&
            boxes[index].y + boxes[index].height <= _original->rows) {
            cv::Mat cropped = (*_original)(boxes[index]);

            _bodies.emplace_back(cropped, config,
                                      boxes[index].x,
                                      boxes[index].y,
                                      boxes[index].height,
                                      boxes[index].width);
            _rects.emplace_back(boxes[index]);
        }
    }
}

// Detect people in image
void People::getPeople(Config& config) {
    // Variable validation and clearing
    if (!_original) { // Validate that image and cascade have been loaded properly
        return;
    }

    if (_loaded) {
        _bodies.clear();
    }

    std::vector<float> confidences{};
    std::vector<cv::Rect> boxes{};
    std::vector<int> indices{};
    std::vector<cv::Mat> found{};

    cv::Mat blob = cv::dnn::blobFromImage(*_original,
                             0.00392,
                             cv::Size(416, 416),
                             cv::Scalar(0, 0, 0),
                             true,
                             false);

    // Run algorithm
    _net.setInput(blob);
    _net.forward(found,
                 _net.getUnconnectedOutLayersNames());

    parseResults(found, boxes, confidences); // Parse results from detection

    cv::dnn::NMSBoxes(boxes,   // Non-max supression
             confidences,
             CONF_THRESHOLD,
             NMS_THRESHOLD,
             indices);

    getBounds(indices, boxes, config);

    _loaded = true;
}

const std::vector<std::pair<int, int>>& People::getDetections() const {
    return _detections;
}
