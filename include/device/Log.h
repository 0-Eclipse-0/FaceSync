//
// Class to hold and handle logging of detections
//

#ifndef FACESYNC_LOG_H
#define FACESYNC_LOG_H

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <sstream>

class Log {
public:
    Log();
    Log(std::string logFile);
    void write(std::string cameraName);
    std::string getTimeStr();

private:
    std::fstream _log;
};


#endif //FACESYNC_LOG_H
