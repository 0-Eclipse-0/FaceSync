//
// Created by Matthew Hambrecht on 11/14/23.
//

#include "People.h"

People::People() {
    _original = nullptr;
}

People::People(const string &path, const string &config, const string &weights) {
    _original = new Image(path);
    _loaded = false;
    _net = dnn::readNetFromDarknet(config, weights);

    // Preparation
    _net.setPreferableBackend(DNN_BACKEND_OPENCV);
    _net.setPreferableTarget(DNN_TARGET_CPU);

    getPeople();
}

void People::getPeople() {
    if (!_original->_image) { // Validate that image and cascade have been loaded properly
        return;
    }

    float confThreshold = 0.25;
    float nmsThreshold = 0.4;

    vector<float> confidences;
    vector<Rect> boxes;
    vector<int> indices;

    if (_loaded) { //  Clear pre-existing vector
        _bodies.clear();
    }

    vector<Mat> found;
    Mat blob = blobFromImage(*_original->_image,
                             0.00392,
                             Size(416, 416),
                             Scalar(0, 0, 0),
                             true,
                             false);

    // Run algorithm
    _net.setInput(blob);
    _net.forward(found, _net.getUnconnectedOutLayersNames());

    for (const auto& item : found) { // Get results from detection
        auto * data = (float *) item.data;

        for (int j = 0; j < item.rows; ++j, data += item.cols) {
            Mat scores = item.row(j).colRange(5, item.cols);
            Point classIdPoint;
            double confidence;

            minMaxLoc(scores, 0, &confidence, &classIdPoint);

            if (confidence > confThreshold && classIdPoint.x == 1) { // 0 is "person" in dataset
                int centerX = static_cast<int>(data[0]    // get coords
                        * _original->_image->cols);
                int centerY = static_cast<int>(data[1]
                        * _original->_image->rows);
                int width = static_cast<int>(data[2]
                        * _original->_image->cols);
                int height = static_cast<int>(data[3]
                        * _original->_image->rows);

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

    for (const auto& index : indices) { // Crop bodies and add to body count
        if (boxes[index].x >= 0 && boxes[index].y >= 0 && // verify box size is within bounds
            boxes[index].x + boxes[index].width <= _original->_image->cols &&
            boxes[index].y + boxes[index].height <= _original->_image->rows) {
            Mat cropped = (*_original->_image)(boxes[index]);

            _bodies.emplace_back(Body(cropped));
        }

        // Add rect after to ensure no overlay
        rectangle(*_original->_image, boxes[index], Scalar(255, 0, 0), 2);
    }

    _original->viewImage(); // DEBUG
    _loaded = true;
}

void People::showPeople() const {
    if (!_loaded) {
        return;
    }

    for (const auto& body : _bodies) { //  display all bodies (for debugging)
        body.showBody();
    }
}
