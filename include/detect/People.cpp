//
// Created by Matthew Hambrecht on 11/14/23.
//

#include "People.h"

People::People() {
    _original = nullptr;
}

People::People(Config& config, Mat& frame) {
    _original = &frame;
    _loaded = false;
    _net = dnn::readNetFromDarknet(config.returnConfig()["yoloConfig"], config.returnConfig()["yoloWeight"]);

    // Preparation
    _net.setPreferableBackend(DNN_BACKEND_OPENCV);
    _net.setPreferableTarget(DNN_TARGET_CPU);

    getPeople(config);
}

void People::getPeople(Config& config) {
    if (!_original) { // Validate that image and cascade have been loaded properly
        return;
    }

    float confThreshold = 0.4;
    float nmsThreshold = 0.5;

    vector<float> confidences;
    vector<Rect> boxes;
    vector<int> indices;

    if (_loaded) { //  Clear pre-existing vector
        _bodies.clear();
    }

    vector<Mat> found;
    Mat blob = blobFromImage(*_original,
                             0.00392,
                             Size(416, 416),
                             Scalar(0, 0, 0),
                             true,
                             false);

    // Run algorithm
    _net.setInput(blob);
    _net.forward(found, _net.getUnconnectedOutLayersNames());

    for (const auto &item: found) { // Get results from detection
        auto *data = (float *) item.data;

        for (int j = 0; j < item.rows; ++j, data += item.cols) {
            Mat scores = item.row(j).colRange(5, item.cols);
            Point classIdPoint;
            double confidence;

            minMaxLoc(scores, 0, &confidence, &classIdPoint);

            if (confidence > confThreshold && classIdPoint.x == 1) { // 0 is "person" in dataset
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
                boxes.emplace_back(Rect(left, top, width, height));
            }
        }
    }

    NMSBoxes(boxes,   // Non-max supression
             confidences,
             confThreshold,
             nmsThreshold,
             indices);

    for (const auto &index: indices) { // Crop bodies and add to body count
        // Add coords to detections
        _detections.emplace_back(boxes[index].x, boxes[index].y);

        if (boxes[index].x >= 0 && boxes[index].y >= 0 && // verify box size is within bounds
            boxes[index].x + boxes[index].width <= _original->cols &&
            boxes[index].y + boxes[index].height <= _original->rows) {
            Mat cropped = (*_original)(boxes[index]);

            _bodies.emplace_back(Body(cropped, config,
                                      boxes[index].x,
                                      boxes[index].y,
                                      boxes[index].height,
                                      boxes[index].width));
            _rects.emplace_back(boxes[index]);
        }
    }

    _loaded = true;
}


void People::showPeople() const { // DEBUG
    if (!_loaded) {
        return;
    }

    for (const auto& body : _bodies) { //  display all bodies (for debugging)
        body.showBody();
    }
}

const vector<pair<int, int>> &People::getDetections() const {
    return _detections;
}

void People::setDetections(const vector<pair<int, int>> &detections) {
    _detections = detections;
}

Mat *People::getOriginal() const {
    return _original;
}

void People::setOriginal(Mat *original) {
    _original = original;
}

const vector<Body> &People::getBodies() const {
    return _bodies;
}

void People::setBodies(const vector<Body> &bodies) {
    _bodies = bodies;
}

const Net &People::getNet() const {
    return _net;
}

void People::setNet(const Net &net) {
    _net = net;
}

const vector<Rect> &People::getRects() const {
    return _rects;
}

void People::setRects(const vector<Rect> &rects) {
    _rects = rects;
}

bool People::isLoaded() const {
    return _loaded;
}

void People::setLoaded(bool loaded) {
    _loaded = loaded;
}
