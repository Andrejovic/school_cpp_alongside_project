# CMakeList.txt : CMake project for OCR_MTG_Scanner_Linux, include source and define
# project specific logic here.
#

cmake_minimum_required(VERSION 3.25)
project(OCR_MTG_Scanner_Linux)
set(CMAKE_CXX_STANDARD 23)

find_path(Tesseract_INCLUDE_DIR NAMES tesseract/basiapi.h PATH_SUFFIXES tesseract)

find_package(OpenCV REQUIRED)
find_package(Tesseract CONFIG REQUIRED)
find_package(CURL REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS},${Tesseract_INCLUDE_DIRS})

add_executable (OCR_MTG_Scanner_Linux OCR_MTG_Scanner_Linux.cpp
		camera.cpp
		camera.h
		ocr.h
		ocr.cpp
		card_db.h
		card_db.cpp 
		config.h 
		config.cpp
		camera.cpp
		camera.cpp)

#target_link_libraries(OCR_MTG_Scanner_Linux ${OpenCV_LIBS})
target_link_libraries(OCR_MTG_Scanner_Linux ${OpenCV_LIBS} Tesseract::libtesseract)


# TODO: Add tests and install targets if needed.
