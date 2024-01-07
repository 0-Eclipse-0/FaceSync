//
// Created by Matthew Hambrecht on 12/3/23.
//

#include "Display.h"
#include <QApplication>

Display::Display() {
    _streams = {};
    _activeStreams = 0;
    _displayX = 1500;
    _displayY = 1500;
    _config = Config();
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

    std::string frameLabel{};
    cv::Point topLeft{};
    cv::Mat currFrame{};
    cv::VideoCapture staticGIF(
            static_cast<std::string>(std::__fs::filesystem::current_path())
                            + "/data/images/static.gif");
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
                putText(image,
                        frameLabel,
                        cv::Point(j * frameSize + 5, i * frameSize + 25),
                        cv::FONT_HERSHEY_PLAIN,
                        2,
                        CV_RGB(0, 0, 0),
                        6.0);
                putText(image,
                        frameLabel,
                        cv::Point(j * frameSize + 5, i * frameSize + 25),
                        cv::FONT_HERSHEY_PLAIN,
                        2,
                        CV_RGB(255, 255, 255),
                        2.0);
            }
        }

        // For static frame incrementing
        staticFrameCount++;

        // Detection
        if (!image.empty()) {
            frameData = People(_config, image);
        } else {
            std::cout << "Empty" << std::endl;
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

    std::cout << "End" << std::endl;
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
