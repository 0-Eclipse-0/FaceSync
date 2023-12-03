//
// Configuration class for Model data files
//

#ifndef FACESYNC_CONFIG_H
#define FACESYNC_CONFIG_H

#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <regex>
#include <exception>
#include <unordered_map>
#include <vector>

const std::vector <std::string> EXPECTED_VALUES = {
        "yoloWeight",
        "yoloConfig",
};

class Config {
public:
    Config();
    std::string getFullPath(const std::string& relativePath);
    void checkFileExists(const std::string& fullPath);
    void compareExpected();
    std::unordered_map<std::string, std::string> returnConfig() { return _filePaths; }
private:
    std::unordered_map <std::string, std::string> _filePaths;
};


#endif //FACESYNC_CONFIG_H
