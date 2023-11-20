#include <string>
#include <filesystem>
#include <chrono>

#include "gtest/gtest.h"
#include "../include/detect/Image.h"
#include "../include/detect/Face.h"
#include "../include/detect/Eye.h"
#include "../include/detect/People.h"
#include "../include/detect/Body.h"
#include "../include/device/Stream.h"
#include "../include/device/Config.h"

// Test Images
Image IMAGE_NORMAL(static_cast<string>(std::__fs::filesystem::current_path()) + "/test/images/test5.webp");
string PEOPLE_IMAGE = static_cast<string>(std::__fs::filesystem::current_path()) + "/test/images/people_test1.jpeg";

// Config Tests
TEST (ConfigTest, NormalCase) {
    EXPECT_NO_THROW(Config());
}

// Stream Tests
TEST (StreamTest, StartStreamTest) { // Start stream from webcam
    Stream webcam;

    EXPECT_NO_THROW(Config());
    ASSERT_EQ(true, webcam.openStream());
}

// People Tests
TEST (PeopleTests, ConstructTest) {
    Config config = Config();
    Mat people = Mat(imread(PEOPLE_IMAGE));

    EXPECT_NO_THROW(People validPeople(config, people));
}

TEST (PeopleTests, TimeTest) { // Ensure (22 fps is plausible)
    Config config = Config();
    Mat people = Mat(imread(PEOPLE_IMAGE));

    auto start = chrono::steady_clock::now();

    People validPeople(config, people);

    auto stop = chrono::steady_clock::now();

    auto duration =
            std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    double expected = 100000; // time per frame at 10fps

    EXPECT_LT(duration.count(), expected);

    auto secs = std::chrono::duration_cast<
            std::chrono::milliseconds>(stop - start);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

