//
// Created by Matthew Hambrecht on 11/18/23.
//
#include <thread>
#include "Stream.h"
bool Stream::openStream() { // open webcam
    VideoCapture _cam(0);
    int counter = 0;
    People frameData;
    Stream tempStream;
    Mat frame;
    bool status = false;
    std::promise<void> completionPromise;

    if (!_cam.isOpened()) { //  check if cam failed to open
        return false;
    }

    namedWindow("Webcam", WINDOW_NORMAL);

    while (true) { // run recognition test
        _cam >> frame; // insert frame

        if (!status) {  // Every tenth frame is analyzed
            status = true; // Thread in progress
            std::thread analysisThread(ref(tempStream.analyzeFrame), ref(frame), ref(frameData), ref(status));
            analysisThread.detach();
        }

        if (!frameData._rects.empty()) { // overlay person on stream
            for (auto const rect : frameData._rects) {
                rectangle(frame, rect, Scalar(0, 165, 255), 2);
            }
        }

        imshow("Webcam", frame);
        counter++;

        if (waitKey(1) == 'q') { // Exit on keypress
            frameData = People(); // Avoid double free
            break;
        }
    }

    _cam.release();
    destroyAllWindows();

    return true;
}

void Stream::analyzeFrame(Mat & frame, People & frameData, bool & status) {
    People temp = People(frame,
                         static_cast<string>(std::__fs::filesystem::current_path()) +
                         "/data/yolo/yolov4-csp-swish.cfg",
                         static_cast<string>(std::__fs::filesystem::current_path()) +
                         "/data/yolo/yolov4-csp-swish.weights");

    frameData = temp;
    status = false;
}
