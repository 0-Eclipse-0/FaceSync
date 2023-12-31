//
// Created by Matthew Hambrecht on 11/18/23.
//
#include "Stream.h"
#include <mutex>

Stream::Stream() { // Configure models to ensure stream can be started
    Config();
}

bool Stream::testStream() { // open webcam
    VideoCapture _cam(0);
    People frameData;
    Mat frame;
    std::mutex lock;

    bool syncroStatus = false; // Used for synchronization of detached threads

    if (!_cam.isOpened()) { //  check if cam failed to open
        return false;
    }

    namedWindow("Webcam", WINDOW_NORMAL);

    while (true) { // run recognition test
        _cam >> frame; // insert frame

        if (!syncroStatus) {  // Frame is only analyzed when previous frame is done
            syncroStatus = true;
            std::thread analysisThread(&Stream::analyzeFrame,
                                       std::ref(frame),
                                       std::ref(frameData),
                                       std::ref(syncroStatus),
                                       std::ref(_config),
                                       std::ref(lock));
            lock.lock();
            analysisThread.detach();
        }

        if (!frameData._bodies.empty()) { // Overlay person on stream
            for (auto body : frameData._bodies) {
                    body.drawBody(frame);
            }
        }

        imshow("Webcam", frame);


        if (waitKey(1) == 'q') { // Exit on keypress
            while(syncroStatus) { // Sleep until thread death
                sleep_for(10ns);
                sleep_until(system_clock::now() + 1s);
            }
            frameData = People(); // Avoid double free
            break;
        }
    }

    _cam.release();
    destroyAllWindows();

    return true;
}

void Stream::analyzeFrame(Mat & frame, People & frameData, bool & syncroStatus, Config & config, std::mutex& lock) {
    People temp = People(config, frame);

    syncroStatus = false;
    frameData = temp;
    lock.unlock();
}

