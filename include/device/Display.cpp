//
// Created by Matthew Hambrecht on 12/3/23.
//

#include "Display.h"

Display::Display() {
    _streams = {};
    _activeStreams = 0;
    _matrixDimensions = 0;
    _config = Config();
}

// Flatten pixel coordinates and scale to matrix
int Display::normalizePoint(int x, int y) { // Normalize points for mapping to key
    int x_n = x / (DISPLAY_SIZE / _matrixDimensions);
    int y_n = y / (DISPLAY_SIZE / _matrixDimensions);

    return x_n + y_n * _matrixDimensions;
}

// Bild stream vector
bool Display::addDisplay(CCTV &cctv) {
    if (!cctv.getCamera().isOpened()) { // Confirm camera is active
        return false;
    }

    _streams.emplace_back(cctv); // Add to stream vector
    _activeStreams++; // Used to determine size of display matrix

    return true;
}

// Build matrix from data
void Display::buildMatrix(const bool & keyMapped, cv::Mat & currFrame,
                          cv::Mat & image, cv::VideoCapture & staticGIF,
                          std::pair<std::string, unsigned long long> key[]) {
    int frameSize = DISPLAY_SIZE / _matrixDimensions;
    std::string frameLabel = "";

    for (int i = 0, counter = 0; i < _matrixDimensions; i++) {
        for (int j = 0; j < _matrixDimensions; j++) {
            // Update region of interest for each frame
            cv::Point topLeft = cv::Point(j * frameSize, i * frameSize);

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
                        std::cout << "\e[1;31m[Error]\033[0m " << "Problem updating frame from: \e[1;37m"
                        << _streams[counter].getCctvName() << "\033[0m" << std::endl;
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
    }
}

// Parse through obtained data for logging
void Display::logData(People & frameData,
                      std::pair<std::string, unsigned long long> key[], Log & log) {
    // Time since epoch for logging threshold
    unsigned long long currTime = std::chrono::duration_cast<std::chrono::milliseconds>
            (std::chrono::system_clock::now().time_since_epoch()).count();

    std::pair<std::string, unsigned long long> * found;

    // Iterate through detections for data to log
    for (auto & i : frameData.getDetections()) {
        found = &key[normalizePoint(i.first, i.second)]; // Store detection info

        // Determine if this is a relatively 3323new detection (for logging)
        if ((found->second + THRESHOLD) <= currTime) {
            // Reset time for camera
            found->second = currTime;
            log.write(
                    found->first);
        }
    }
}

// Open user interface
void Display::openDisplay() {
    if (_streams.size() == 0) { // Ensure there are streams to view
        throw std::runtime_error("[Error] No streams opened!");
    }

    Log log(_config.returnConfig()["log"]);
    bool keyMapped = false; // Variable to determine if we've already mapped the cameras to locations on grid
    std::pair<std::string, unsigned long long> key[_activeStreams];
    cv::Mat currFrame{};
    cv::VideoCapture staticGIF(
            static_cast<std::string>(std::__fs::filesystem::current_path())
                            + "/data/static.gif");
    cv::namedWindow("CCTV Dashboard", cv::WINDOW_NORMAL);
    cv::Mat image(DISPLAY_SIZE,
                  DISPLAY_SIZE,
                  CV_8UC3,
                  cv::Scalar(0, 0, 0));
    _matrixDimensions = ceil(sqrt(_activeStreams));
    int staticFrameCount = 0;
    People frameData(_config, image);

    std::cout << "\e[1;92m[FaceSync]\033[0m " << "Opening display: " <<
    _matrixDimensions << "x" << _matrixDimensions << std::endl;

    while (true) {
        // Set static frame
        staticGIF.set(cv::CAP_PROP_POS_FRAMES,
                      staticFrameCount %
                      (int) staticGIF.get(cv::CAP_PROP_FRAME_COUNT));

        // Update image
        cv::imshow("CCTV Dashboard", image);
        // Build 2D matrix from 1D vector
        buildMatrix(keyMapped, currFrame, image, staticGIF, key);

        // For static frame incrementing
        keyMapped = true;
        staticFrameCount++;

        // Detection
        if (!image.empty()) {
            frameData = People(_config, image);
            if (!frameData.getDetections().empty()) logData(frameData, key, log);
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