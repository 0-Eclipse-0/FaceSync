//
// Class for displaying CCTV streams
//

#ifndef FACESYNC_DISPLAY_H
#define FACESYNC_DISPLAY_H

#include <vector>
#include <filesystem>
#include <utility>

#include "../detect/People.h"
#include "CCTV.h"
#include "Config.h"
#include "Log.h"

const int THRESHOLD = 10000; // Logging threshold (5s)
const int DISPLAY_SIZE = 20002;

class Display {
public:
    Display();

    bool addDisplay(CCTV& cctv);
    void openDisplay();
    void buildMatrix(const bool & keyMapped, cv::Mat & currFrame,
                     cv::Mat & image, cv::VideoCapture & staticGIF,
                     std::pair<std::string, unsigned long long> key[]);
    void logData(People & frameData,  std::pair<std::string,
                          unsigned long long> key[], Log & log);

private:
    std::vector<CCTV> _streams{};
    int _activeStreams;
    int _matrixDimensions;
    Config _config;

    // Private functions
    int normalizePoint(int x, int y);
};


#endif //FACESYNC_DISPLAY_H
