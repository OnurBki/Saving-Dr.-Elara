cmake_minimum_required(VERSION 3.26)
project(Assignment_1)

set(CMAKE_CXX_STANDARD 14)

include_directories(PA1_template/src)

add_executable(Assignment_1
        PA1_template/src/Convolution.cpp
        PA1_template/src/Convolution.h
        PA1_template/src/DecodeMessage.cpp
        PA1_template/src/DecodeMessage.h
        PA1_template/src/EdgeDetector.cpp
        PA1_template/src/EdgeDetector.h
        PA1_template/src/EncodeMessage.cpp
        PA1_template/src/EncodeMessage.h
        PA1_template/src/ImageLoader.cpp
        PA1_template/src/ImageLoader.h
        PA1_template/src/ImageMatrix.cpp
        PA1_template/src/ImageMatrix.h
        PA1_template/src/ImageProcessor.cpp
        PA1_template/src/ImageProcessor.h
        PA1_template/src/ImageSharpening.cpp
        PA1_template/src/ImageSharpening.h
        PA1_template/src/main.cpp)
