//
// Created by Matthew Hambrecht on 1/8/24.
//

#include "Log.h"

Log::Log() {
    _log.open("log.txt", std::ios::app);
}

// Open filestream
Log::Log(std::string logFile) {
    _log.open(logFile, std::ios::app);
}

// Output log message to file
void Log::write(std::pair<std::string, std::string> logInfo) {
    _log << "Hello world\n";
    _log << "Bye world\n";
}
