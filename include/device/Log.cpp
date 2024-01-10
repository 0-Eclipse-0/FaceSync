//
// Class to hold and handle logging of detections
//

#include "Log.h"

Log::Log() {
    _log.open("log.txt", std::ios::app);
}
// Open filestream
Log::Log(std::string logFile) {
    _log.open(logFile, std::ios::app);
}

// Format timestamp
std::string Log::getTimeStr() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%m-%d-%Y %H:%M:%S");
    auto str = oss.str();

    return str;
}

// Output log message to file
void Log::write(std::string cameraName) {
    // Write to log
    _log << "[" << getTimeStr() << "] Detection on camera: "
    << cameraName << std::endl;

    // Write to stdout
    std::cout << "\e[1;34m[" << getTimeStr() <<
    "]\033[0m Detection on camera: \e[1;37m" << cameraName <<
    "\033[0m" << std::endl;
}
