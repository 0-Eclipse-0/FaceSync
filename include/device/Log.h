//
// Created by Matthew Hambrecht on 1/8/24.
//

#ifndef FACESYNC_LOG_H
#define FACESYNC_LOG_H

#include <string>
#include <iostream>
#include <fstream>
#include <utility>
class Log {
public:
    Log();
    Log(std::string logFile);
    void write(std::pair<std::string, std::string> logInfo);
    friend class Display;
private:
    std::fstream _log;
};


#endif //FACESYNC_LOG_H
