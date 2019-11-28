# project name
project(real_sense)

# required cmake and c++ version
cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)



# set where to keep executables and libs
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# include directories
include_directories(${PROJECT_SOURCE_DIR}/lcmtypes)


find_package(OpenCV REQUIRED)
find_package(realsense2 REQUIRED)
find_package(lcm REQUIRED)

include(${LCM_USE_FILE})

set(DEPENDENCIES ${realsense2_LIBS} ${OpenCV_LIBS} lcm)

add_executable(realsense_driver realsense_driver.cpp)
target_link_libraries(realsense_driver ${DEPENDENCIES})