//
// Created by Matthew Hambrecht on 11/18/23.
//

#ifndef FACESYNC_STREAM_H
#define FACESYNC_STREAM_H
#include <opencv2/opencv.hpp>
#include <string>
#include <exception>
#include <filesystem>
#include <future>
#include "../detect/Image.h"
#include "../detect/People.h"

class Stream {
public:
    bool openStream();
    static void analyzeFrame(Mat & frame, People & frameData, bool & status);
};


#endif //FACESYNC_STREAM_H
