#include "gtest/gtest.h"
#include <string>
#include <filesystem>
#include "../include/Image.h"
#include "../include/Face.h"
#include "../include/Eye.h"
#include "../include/People.h"
#include "../include/Body.h"

// Test Images
Image IMAGE_NORMAL(static_cast<string>(std::__fs::filesystem::current_path()) + "/test/images/test5.webp");
string PEOPLE_IMAGE = static_cast<string>(std::__fs::filesystem::current_path()) + "/test/images/test9.jpg";

// Test Data
string FACE_CASCADE_PATH = static_cast<string>(std::__fs::filesystem::current_path()) + "/data/haarcascades/haarcascade_frontalface_default.xml";
string EYE_CASCADE_PATH = static_cast<string>(std::__fs::filesystem::current_path()) + "/data/haarcascades/haarcascade_eye_tree_eyeglasses.xml";
string YOLO_CFG = static_cast<string>(std::__fs::filesystem::current_path()) + "/data/yolo/yolov3.cfg";
string YOLO_WEIGHTS = static_cast<string>(std::__fs::filesystem::current_path()) + "/data/yolo/yolov3.weights";

// People Tests
TEST (PeopleTests, ExpectedOutcomes) {
    People validPeople(PEOPLE_IMAGE,
                       YOLO_CFG, YOLO_WEIGHTS);

    EXPECT_NO_THROW(validPeople.showPeople());
}

TEST (PeopleTests, ErrorCases) {
    EXPECT_ANY_THROW(People emptyPeople("/err1", "/err2", "/err3"));
}

// Body Tests
TEST (BodyTests, ExpectedOutcomes) {
    return;
}

TEST (BodyTests, ErrorCases) {
    return;
}

// Face Tests
TEST (FaceTests, ExpectedOutcomes) {
    Face face(IMAGE_NORMAL,
              (string &) FACE_CASCADE_PATH);

    ASSERT_EQ(face.getFace(), true);
}

// Eye Tests
TEST (EyeTest, ExpectedOutcomes) {
    Eye eye(IMAGE_NORMAL,
            (string &) EYE_CASCADE_PATH);

    ASSERT_EQ(eye.getEyes(), true);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    auto ret = RUN_ALL_TESTS();
    IMAGE_NORMAL.viewImage();

    return ret;
}

