cmake_minimum_required(VERSION "3.10.0")

project("test4pcseq")


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
#set(PHOXI_DIR /opt/phoxi)

find_package(OpenCV REQUIRED)
#find_package(PhoXi REQUIRED)


include_directories("${OpenCV_INCLUDE_DIRS}")
#include_directories("${PHOXI_INCLUDE_DIRS}")


#file( GLOB cpps source/*.cpp)
file( GLOB headers include/*.h)
message("${headers}")


add_executable("${PROJECT_NAME}" "main.cpp" ${headers})
target_link_libraries("${PROJECT_NAME}" ${OpenCV_LIBS})
#target_link_libraries("${PROJECT_NAME}" ${PHOXI_LIBS})

set_property(TARGET "${PROJECT_NAME}" PROPERTY CXX_STANDARD 17)
set_property(TARGET "${PROJECT_NAME}" PROPERTY CXX_STANDARD_REQUIRED 17)
