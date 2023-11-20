//
// Configuration class for Model data files
//

#include "Config.h"

Config::Config() {
    std::string line;
    std::ifstream file("config.ini");
    std::smatch key;
    std::smatch value;

    if (file.is_open()) {
        while (getline(file, line)) {
            if (std::regex_search(line, key, std::regex(".*:"))) {
                // Regex for kv pairs
                std::regex_search(line, key, std::regex("([^:]+):"));
                std::regex_search(line, value, std::regex(":\\s*(.*)"));

                checkFileExists(getFullPath(value[1]));
                _filePaths.insert({key[1],
                                   getFullPath(value[1])});
            }
        }
    } else {
        file.close(); // Ensure stream closes on death
        throw std::runtime_error("[Error] Config file not found!");
    }

    file.close();
    compareExpected();
}

std::string Config::getFullPath(const std::string& relativePath) { // Convert relative path to full path
    return static_cast<std::string>(std::__fs::filesystem::current_path())
    + "/"
    + relativePath;
}

void Config::checkFileExists(const std::string& fullPath) { // Death on invalid file
    std::__fs::filesystem::path filePath(fullPath);

    if (!std::__fs::filesystem::exists(filePath)) {
        throw std::runtime_error("[Error] File doesn't exist: " + fullPath);
    }
}

void Config::compareExpected() { //  Death on missing config key
    for (auto const& key : EXPECTED_VALUES) {
        if (_filePaths.find(key) == _filePaths.end()) {
            throw std::runtime_error("[Error] Key not found in config: " + key);
        }
    }
}
