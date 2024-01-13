cmake_minimum_required(VERSION 3.27)
project(TechnologicDemo)

set(CMAKE_CXX_STANDARD 23 "OpenCV_DIR" "/usr/local/include/opencv4")
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable(TechnologicDemo main.cpp)
target_link_libraries( TechnologicDemo ${OpenCV_LIBS} )