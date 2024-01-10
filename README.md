># FaceSync
```
This project focuses on simplifying surveillance analysis by implementing body detection on multiple CCTV feeds concurrently.
The goal is to facilitate the review process and streamline the identification of events, such as burglaries, by providing time-stamped data on human presence. The system
employs advanced computer vision algorithms for efficient processing and offers a user-friendly logging solution. With a focus on retrospective analysis, and
makes it easier to pinpoint the time a specific event occurred, enhancing the overall utility of surveillance data. FaceSync can be used on any network camera, placing
hardware limitations solely on the host computer.
```

### Requirements
- C++17
- OpenCV 4.8.1+
- YOLOv4 Data Set ([download here](https://github.com/AlexeyAB/darknet/tree/master/cfg))([whitepaper](https://pjreddie.com/media/files/papers/YOLOv3.pdf))

### Setup
1. Set paths in *config.ini* to required locations. (**Optional**: Default files and locations are provided)
2. Modify `THRESHOLD` in `include/device/Display.h` with the delay you want the program to use before logging new detections on each specific feed after each detection. (Recommended: 300000ms = 5 minutes).
3. Build with `cmake CMakeLists.txt && make`
4. Fill camera file with camera addresses using the format `Camera Name::protocol://username:password@ip:port`. For specific details on your camera review the model.
5. Run executable. (Window size can be modified in `display.h` as `DISPLAY_SIZE`.

### Samples
#### Test run on python servers hosting gifs
![](https://github.com/0-Eclipse-0/FaceSync/blob/main/docs/preview.gif?raw=true)

#### Logging sample from test run
![](https://github.com/0-Eclipse-0/FaceSync/blob/main/docs/logging.png?raw=true)
