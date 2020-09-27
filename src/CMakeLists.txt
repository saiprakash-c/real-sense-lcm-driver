# include directories
include_directories(${PROJECT_SOURCE_DIR}/src/lcmtypes)

find_package(OpenCV REQUIRED)
find_package(realsense2 REQUIRED HINTS /usr/lib/x86_64-linux-gnu)
#find_package(lcm REQUIRED)

#include(${LCM_USE_FILE})

# get the library of lcmtypes 
add_library(lcmtypes_lib lcmtypes/Image.c lcmtypes/DepthImage.c lcmtypes/imu_t.c)
# target_link_libraries(lcmtypes_lib lcm)

# set dependencies for executables
set(DEPENDENCIES ${realsense2_LIBRARY} ${OpenCV_LIBS} lcm lcmtypes_lib pthread)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
)

include_directories(${catkin_INCLUDE_DIRS})

add_executable(realsense_driver_lcm main.cpp)
add_executable(realsense_driver_ros main_ros.cpp)
add_executable(realsense_receiver_lcm main_lcm_test.cpp ImageDisplay.cpp)
add_executable(publish_imu publish_imu.cpp)
target_link_libraries(realsense_driver_lcm ${DEPENDENCIES})
target_link_libraries(realsense_driver_ros ${DEPENDENCIES})
target_link_libraries(realsense_receiver_lcm ${DEPENDENCIES})
target_link_libraries(publish_imu ${DEPENDENCIES} ${catkin_LIBRARIES})