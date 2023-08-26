cmake_minimum_required(VERSION 3.5)

project(noncentral-plotter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(noncentral-plotter main.cpp)

target_link_libraries(noncentral-plotter
    ${OpenCV_LIBRARIES}
)

install(TARGETS noncentral-plotter
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
