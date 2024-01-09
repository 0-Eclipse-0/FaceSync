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
private:
    std::vector<CCTV> _streams{};
    int _activeStreams;
    int _displayX;
    int _displayY;
    Config _config;
};


#endif //FACESYNC_DISPLAY_H
