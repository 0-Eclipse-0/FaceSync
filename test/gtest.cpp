#include <string>
#include <filesystem>
#include <chrono>
#include <thread>

#include "gtest/gtest.h"
#include "../include/detect/People.h"
#include "../include/detect/Body.h"
#include "../include/device/Stream.h"
#include "../include/device/Config.h"
#include "../include/device/CCTV.h"
#include "../include/device/Display.h"

// Test Images
string PEOPLE_IMAGE = static_cast<string>(std::__fs::filesystem::current_path()) + "/test/images/people_test1.jpeg";

// Config Tests
TEST (ConfigTest, NormalCase) {
    EXPECT_NO_THROW(Config());
}

// Stream Tests
TEST (StreamTest, StartStreamTest) { // Start stream from webcam
    Stream webcam;

    EXPECT_NO_THROW(Config());
    ASSERT_EQ(true, webcam.testStream());
}

// People Tests
TEST (PeopleTests, ConstructTest) {
    Config config = Config();
    Mat people = Mat(imread(PEOPLE_IMAGE));

    EXPECT_NO_THROW(People validPeople(config, people));
}

// CCTV Tests
TEST (CCTVTests, ViewStream) { //  Connect to random rtsp stream
    CCTV testStream("CCTV_1", "rtsp://666666:666666@145.255.4.135:554/cam/realmonitor?channel=1&subtype=0");

    ASSERT_NO_THROW(testStream.testCCTV());
}

TEST (CCTVTests, DefaultConstructViewStreamError) { //  Attempt to open invalid stream of default
    CCTV testStream;

    ASSERT_ANY_THROW(testStream.testCCTV());
}

TEST (CCTVTests, InvalidURLViewStreamError) { //  Attempt to open invalid stream of default
    CCTV testStream("CCTV_1", "rtsp://198.168.1.1:554");

    ASSERT_ANY_THROW(testStream.testCCTV());
}

// Display For CCTVs
TEST (DisplayTests, AddStreamsTest) {
    Display display;
    CCTV invalidCCTVDefaultConstruct;
    CCTV invalidCCTVInvalidURL("CCTV_2", "rtsp://198.168.1.1:554");

    ASSERT_FALSE(display.addDisplay(invalidCCTVDefaultConstruct));
    ASSERT_FALSE(display.addDisplay(invalidCCTVInvalidURL));
}

TEST (DisplayTest, DisplayStreamsTest) {
    Display testDisplay;

    std::thread camFeed(std::system, "nohup python3 test/server.py");
    std::this_thread::sleep_for(5s);

    vector<CCTV> cctvList = { // List of identical displays // 207.111.165.53 145.255.4.135
            CCTV("CCTV_1", "http://127.0.0.1:5000"),
            CCTV("CCTV_2", "http://127.0.0.1:5001"),
            CCTV("CCTV_3", "http://127.0.0.1:5002"),
            CCTV("CCTV_4", "http://127.0.0.1:5003"),
            CCTV("CCTV_5", "http://127.0.0.1:5004"),
            CCTV("CCTV_6", "http://127.0.0.1:5005"),
            CCTV("CCTV_7", "http://127.0.0.1:5006"),
    };

    // Add all cctvs to display
    for (vector<CCTV>::iterator it = cctvList.begin(); it != cctvList.end(); it++) {
        ASSERT_TRUE(testDisplay.addDisplay(*it));
    }

    ASSERT_NO_THROW(testDisplay.openDisplay());
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

