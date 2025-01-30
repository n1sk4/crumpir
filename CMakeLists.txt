cmake_minimum_required(VERSION 3.30)
project(crumpir)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)
set(OpenCV_DIR E:/opencv/build/x64/vc16/lib)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(SOURCES 
    src/crumpir.cpp
    src/main.cpp
)

set(HEADERS
    include/crumpir.hpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})