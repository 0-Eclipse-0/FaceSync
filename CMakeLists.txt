cmake_minimum_required(VERSION 3.23)
project(FaceSync)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)
find_package(GTest REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(FaceSync test/gtest.cpp include/device/Config.cpp include/detect/People.cpp include/detect/Body.cpp include/detect/Image.cpp
        include/device/Stream.cpp
        include/device/Config.cpp
        include/device/CCTV.cpp
)

target_link_libraries(FaceSync ${OpenCV_LIBS} ${GTEST_LIBRARIES})
