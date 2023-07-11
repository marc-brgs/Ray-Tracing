cmake_minimum_required(VERSION 3.21)
project(Lancer_de_rayon)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE-DIRECTORIES})
add_executable(Lancer_de_rayon main.cpp)

set(CMAKE_CXX_STANDARD 14)
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)

target_link_libraries(Lancer_de_rayon ${OpenCV_LIBS})