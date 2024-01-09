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

const int THRESHOLD = 5000; // Logging threshold (5s)

class Display {
public:
    Display();

    bool addDisplay(CCTV& cctv);
    void openDisplay();

    // Accessors and Mutators
    int getDisplayX() const;
    void setDisplayX(int displayX);
    int getDisplayY() const;
    void setDisplayY(int displayY);
    const std::vector<CCTV> &getStreams() const;
    void setStreams(const std::vector<CCTV> &streams);
    int getActiveStreams() const;
    void setActiveStreams(int activeStreams);
    int getHeight() const;
    void setHeight(int height);
    const Config &getConfig() const;
    void setConfig(const Config &config);

private:
    std::vector<CCTV> _streams{};
    int _activeStreams;
    int _displayX;
    int _displayY;
    int _height;
    Config _config;

    // Private functions
    int normalizePoint(int x, int y);
};


#endif //FACESYNC_DISPLAY_H
