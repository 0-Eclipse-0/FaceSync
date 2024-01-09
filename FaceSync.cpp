//
// Created by Matthew Hambrecht on 1/6/24.
//

#include "include/device/Display.h"
#include "include/device/Config.h"

#include <fstream>
#include <vector>
#include <string>
#include <regex>

int main() {
    // Variables
    Display display;
    Config config;
    fstream cameras;
    std::smatch key;
    std::smatch value;
    CCTV stream;

    cameras.open(config.returnConfig()["cameras"], ios::in); // Read file

    std::string streamData;
    while(getline(cameras, streamData)){
        if (std::regex_search(streamData, key, std::regex(".*::"))) {
            // Regex for kv pairs
            std::regex_search(streamData, key, std::regex("([^:]+)::"));
            std::regex_search(streamData, value, std::regex("::\\s*(.*)"));

            stream = CCTV(key[1], value[1]);

            std::cout << "Connecting to " << value[1] << ". Please wait...\n";
            display.addDisplay(stream);
        } else { // Avoid bad addresses
            throw std::runtime_error("[Error] Invalid camera file format"
                                     "... (ex. name::address)");
        }
    }
    cameras.close(); // Close the file object.

    cout << "Opening display..." << std::endl;
    display.openDisplay();

    return 0;
}