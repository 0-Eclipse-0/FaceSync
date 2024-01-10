cmake_minimum_required(VERSION 3.23)
project(FaceSync)

set(CMAKE_CXX_STANDARD 14)

# Findable Packages
find_package(OpenCV REQUIRED)

# Manually include files
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(FaceSync
        FaceSync.cpp
        include/device/Config.cpp
        include/detect/People.cpp
        include/detect/Body.cpp
        include/device/Config.cpp
        include/device/CCTV.cpp
        include/device/Display.cpp
        include/device/Log.cpp
)

target_link_libraries(FaceSync ${OpenCV_LIBS})