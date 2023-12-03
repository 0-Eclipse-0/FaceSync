//
// Created by Matthew Hambrecht on 11/18/23.
//

#ifndef FACESYNC_STREAM_H
#define FACESYNC_STREAM_H

#include <opencv2/opencv.hpp>
#include <string>
#include <filesystem>
#include <thread>

#include "../detect/Image.h"
#include "../detect/People.h"
#include "Config.h"

using namespace std::this_thread;
using namespace std::chrono_literals;
using std::chrono::system_clock;

const int MAX_THREAD_COUNT = 1; // Higher number means more processing power required

class Stream {
public:
    Stream();
    bool openStream();
private:
    static void analyzeFrame(Mat & frame,
                             People & frameData,
                             bool & syncroStatus,
                             Config & config,
                             std::mutex & lock);

    Config _config;
};


#endif //FACESYNC_STREAM_H
