cmake_minimum_required(VERSION "3.10.0")

project("test4pcseq")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

find_package(OpenCV REQUIRED)

include_directories("${OpenCV_INCLUDE_DIRS}")

add_executable("${PROJECT_NAME}" "main.cpp")
target_link_libraries("${PROJECT_NAME}" ${OpenCV_LIBS})

set_property(TARGET "${PROJECT_NAME}" PROPERTY CXX_STANDARD 17)
set_property(TARGET "${PROJECT_NAME}" PROPERTY CXX_STANDARD_REQUIRED 17)
