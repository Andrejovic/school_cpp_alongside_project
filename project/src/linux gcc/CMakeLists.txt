# CMakeList.txt : CMake project for OCR_MTG_Scanner_Linux, include source and define
# project specific logic here.
#

# Add source to this project's executable.
cmake_minimum_required(VERSION 3.27)
project(OCR_MTG_Scanner_Linux)
add_executable (OCR_MTG_Scanner_Linux OCR_MTG_Scanner_Linux.cpp
		camera.h
		camera.cpp
		ocr.h
		ocr.cpp
		card_db.h
		card_db.cpp 
		config.h 
		config.cpp)

set(CMAKE_CXX_STANDARD 23 "OpenCV_DIR" "/usr/local/include/opencv4")
find_package(OpenCV CONFIG REQUIRED)
find_package(Tesseract REQUIRED)
find_package(CURL REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS} ${Tesseract_INCLUDE_DIRS})
target_link_libraries(OCR_MTG_Scanner_Linux ${OpenCV_LIBS} ${Tesseract_LIBRARIES} ${CURL_LIBRARIES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET OCR_MTG_Scanner_Linux PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
