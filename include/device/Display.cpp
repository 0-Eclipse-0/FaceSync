//
// Created by Matthew Hambrecht on 12/3/23.
//

#include "Display.h"

Display::Display() {
    _streams = {};
    _activeStreams = 0;
    _displayX = 1500;
    _displayY = 1500;
    _height = 0;
    _config = Config();
}

int Display::normalizePoint(int x, int y) { // Normalize points for mapping to key
    int x_n = x / (_displayX / _height);
    int y_n = y / (_displayY / _height);

    return x_n + y_n * _height;
}

bool Display::addDisplay(CCTV &cctv) {
    if (!cctv.getCamera().isOpened()) { // Confirm camera is active
        return false;
    }

    _streams.emplace_back(cctv); // Add to stream vector
    _activeStreams++; // Used to determine size of display matrix

    return true;
}

void Display::openDisplay() {
    if (_streams.size() == 0) { // Ensure there are streams to view
        throw std::runtime_error("[Error] No streams opened!");
    }

    bool keyMapped = false; // Variable to determine if we've already mapped the cameras to locations on grid
    std::pair<string, unsigned long long> key[_activeStreams];
    std::string frameLabel{};
    cv::Point topLeft{};
    cv::Mat currFrame{};
    cv::VideoCapture staticGIF(
            static_cast<std::string>(std::__fs::filesystem::current_path())
                            + "/data/static.gif");
    cv::namedWindow("CCTV Dashboard", cv::WINDOW_NORMAL);
    cv::Mat image(_displayY,
                  _displayX,
                  CV_8UC3,
                  cv::Scalar(0, 0, 0));
    int matrixDimension = ceil(sqrt(_activeStreams));
    int frameSize = _displayY / matrixDimension;
    int staticFrameCount = 0;
    People frameData(_config, image);

    while (true) {
        // Set static frame
        staticGIF.set(cv::CAP_PROP_POS_FRAMES,
                      staticFrameCount %
                      (int) staticGIF.get(cv::CAP_PROP_FRAME_COUNT));

        // Update image
        cv::imshow("CCTV Dashboard", image);
        // Build 2D matrix from 1D vector
        for (int i = 0, counter = 0; i < matrixDimension; i++) {
            for (int j = 0; j < matrixDimension; j++) {
                // Update region of interest for each frame
                topLeft = cv::Point(j * frameSize, i * frameSize);

                // Map cameras to key for later
                if (!keyMapped && counter < _activeStreams) {
                    key[counter] = make_pair(_streams[counter].getCctvName(), 0);
                }

                cv::Rect roi(topLeft,
                             cv::Size(frameSize, frameSize));
                cv::Mat destRoi = image(roi);

                if (counter < _activeStreams) { // only fill active frames with images
                    if (!_streams[counter].getCamera().read(currFrame)) { // Image read failed
                        if (!staticGIF.read(currFrame)) { // Image read failed (reached last frame)
                            staticGIF.set(cv::CAP_PROP_POS_FRAMES, 0);
                            staticGIF.read(currFrame);
                        } else {
                            throw std::runtime_error("[Error] Error updating frame, check connection...");
                        }
                        frameLabel = "Not Connected";

                    } else {
                        frameLabel = _streams[counter].getCctvName();
                    }

                    counter++;
                } else { // fill inactive frames with static
                    if (!staticGIF.read(currFrame)) { // Image read failed (reached last frame)
                        staticGIF.set(cv::CAP_PROP_POS_FRAMES, 0);
                        staticGIF.read(currFrame);
                    }

                    frameLabel = "Not Connected";
                }

                // Overlay frame
                cv::resize(currFrame,
                           currFrame,
                           cv::Size(frameSize, frameSize));
                currFrame.copyTo(destRoi);

                // Add label
                // Bold background
                putText(image,
                        frameLabel,
                        cv::Point(j * frameSize + 5, i * frameSize + 25),
                        cv::FONT_HERSHEY_PLAIN,
                        2,
                        CV_RGB(0, 0, 0),
                        6.0);

                // White foreground
                putText(image,
                        frameLabel,
                        cv::Point(j * frameSize + 5, i * frameSize + 25),
                        cv::FONT_HERSHEY_PLAIN,
                        2,
                        CV_RGB(255, 255, 255),
                        2.0);
            }
            if (!keyMapped) _height++;
        }

        // For static frame incrementing
        keyMapped = true;
        staticFrameCount++;

        // Detection
        if (!image.empty()) {
            frameData = People(_config, image);
            unsigned long long currTime = std::chrono::duration_cast<std::chrono::milliseconds>
                    (std::chrono::system_clock::now().time_since_epoch()).count();

            if (!frameData.getDetections().empty()) { // Log if detections found
                for (auto & i : frameData.getDetections()) {
                    // Determine if this is a relatively new detection (for logging)
                    if ((key[normalizePoint(i.first, i.second)].second + THRESHOLD)
                    <= currTime) {
                        // Reset time for camera
                        key[normalizePoint(i.first, i.second)].second = currTime;

                        // ADD TO LOG (TODO)
                        std::cout << "New detection on " <<
                            key[normalizePoint(i.first, i.second)].first << std::endl;
                    }
                }
            }
        }

        // Draw bodies
        if (!frameData._bodies.empty()) { // Overlay person on stream
            for (auto body : frameData._bodies) {
                body.drawBody(image);
            }
        }

        if (cv::waitKey(1) == 'q') { // 'q' to close
            staticGIF.release();
            break;
        }
    }
}

int Display::getDisplayX() const {
    return _displayX;
}

void Display::setDisplayX(int displayX) {
    _displayX = displayX;
}

int Display::getDisplayY() const {
    return _displayY;
}

void Display::setDisplayY(int displayY) {
    _displayY = displayY;
}

const std::vector<CCTV> &Display::getStreams() const {
    return _streams;
}

void Display::setStreams(const std::vector<CCTV> &streams) {
    _streams = streams;
}

int Display::getActiveStreams() const {
    return _activeStreams;
}

void Display::setActiveStreams(int activeStreams) {
    _activeStreams = activeStreams;
}

int Display::getHeight() const {
    return _height;
}

void Display::setHeight(int height) {
    _height = height;
}

const Config &Display::getConfig() const {
    return _config;
}

void Display::setConfig(const Config &config) {
    _config = config;
}
