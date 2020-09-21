#include <librealsense2/rs.hpp> // Includes real sense cross platform API
#include <lcm/lcm.h>
#include "lcmtypes/DepthImage.h"
#include "lcmtypes/Image.h"
#include "lcmtypes/imu_t.h"
#include <iostream>
#include <thread>

// create functions that the threads call continuously
void publishAccelerationInfo(int frameRate, lcm_t* lcm_object)
{
    rs2::pipeline p;
    rs2::config cfg;
    cfg.enable_stream(RS2_STREAM_ACCEL, RS2_FORMAT_MOTION_XYZ32F, frameRate);
    p.start(cfg);

    imu_t imu_data;
    while (true)
    {
        rs2::frameset frameset = p.wait_for_frames();
        if (rs2::motion_frame accel_frame = frameset.first_or_default(RS2_STREAM_ACCEL))
        {
            rs2_vector accel_data = accel_frame.get_motion_data();
            imu_data.utime = accel_frame.get_timestamp() * 1e3;
            // embed the info and publish through lcm
            imu_data.accel[0] = accel_data.x;
            imu_data.accel[1] = accel_data.y;
            imu_data.accel[2] = accel_data.z;
            // std::cout << "Accelerations:" << imu_data.utime << "," << imu_data.accel[0] << "," << imu_data.accel[1]
            //           << "," << imu_data.accel[2] << "\n";
            imu_t_publish(lcm_object, "SENSOR_CAMERA_ACCEL", &imu_data);
        }
    }
    p.stop();
}

void publishGyroscopeInfo(int frameRate,lcm_t* lcm_object)
{
    rs2::pipeline p;
    rs2::config cfg;
    cfg.enable_stream(RS2_STREAM_GYRO, RS2_FORMAT_MOTION_XYZ32F, frameRate);
    p.start(cfg);
    imu_t imu_data;
    while (true)
    {
        rs2::frameset frameset = p.wait_for_frames();
        if (rs2::motion_frame gyro_frame = frameset.first_or_default(RS2_STREAM_GYRO))
        {
            rs2_vector gyro_data = gyro_frame.get_motion_data();
            imu_data.utime = gyro_frame.get_timestamp() * 1e3;
            // embed the info and publish through lcm
            imu_data.gyro[0] = gyro_data.x;
            imu_data.gyro[1] = gyro_data.y;
            imu_data.gyro[2] = gyro_data.z;
            // std::cout << "Gyroscope:" << imu_data.utime << "," << imu_data.gyro[0] << "," << imu_data.gyro[1] << ","
            //           << imu_data.gyro[2] << "\n";
            imu_t_publish(lcm_object, "SENSOR_CAMERA_GYRO", &imu_data);
        }
    }
    p.stop();
}

int main(int argc, char **argv)
{
    lcm_t *lcm_object = lcm_create(NULL); // keep the correct address?

    // launch two threads, one to publish acceleration, other to publish gyroscope
    std::thread accelThread(publishAccelerationInfo,250,lcm_object);
    std::thread gyroThread(publishGyroscopeInfo,400,lcm_object);
    // TODO: can we pass same lcm object for all
  
    // main loop is for color and depth images
    // create a pipe-line
    rs2::pipeline p; 
    //Create a configuration for configuring the pipeline with a non default profile
    rs2::config cfg;
    // rs2::config imu_cfg;
    //Add desired streams to configuration
    //TODO: option to add the configurations from the command-line
    cfg.enable_stream(RS2_STREAM_COLOR, 640, 480, RS2_FORMAT_BGR8, 15);
    cfg.enable_stream(RS2_STREAM_DEPTH, 640, 480, RS2_FORMAT_Z16, 15);
    // start the pipeline
    p.start(cfg);
    // Capture 30 frames to give autoexposure, etc. a chance to settle
    for (auto i = 0; i < 30; ++i)
    {
        p.wait_for_frames();
    }
    Image color_img;
    DepthImage depth_img;
    imu_t imu_data;
    rs2::align align_to_color(RS2_STREAM_COLOR);
    while (true)
    {

        rs2::frameset frameset = p.wait_for_frames();
        //align to color frame- refer to https://github.com/IntelRealSense/librealsense/blob/master/examples/align/rs-align.cpp
        frameset = align_to_color.process(frameset);

        // get a frame of depth image
        rs2::video_frame color_frame = frameset.get_color_frame();
        rs2::depth_frame depth_frame = frameset.get_depth_frame();

        // get color image info
        const int w_color = color_frame.get_width();
        const int h_color = color_frame.get_height();
        uint8_t *color_pixel_data = (uint8_t *)color_frame.get_data();

        // get depth image info
        const int w_depth = depth_frame.get_width();
        const int h_depth = depth_frame.get_height();
        uint8_t *depth_pixel_data = (uint8_t *)depth_frame.get_data();

        // publish color image
        color_img.utime = color_frame.get_timestamp() * 1e3;
        color_img.width = w_color;
        color_img.height = h_color;
        color_img.line_stride = color_frame.get_stride_in_bytes();
        color_img.bytes_per_pixel = color_frame.get_bytes_per_pixel();
        color_img.num_bytes = color_frame.get_data_size();
        color_img.pixel_data = color_pixel_data;
        Image_publish(lcm_object, "SENSOR_RGB_IMAGE", &color_img);

        // publish depth image
        depth_img.utime = depth_frame.get_timestamp() * 1e3; // get_timestamp outputs the time in milliseconds
        depth_img.width = w_depth;
        depth_img.height = h_depth;
        depth_img.line_stride = depth_frame.get_stride_in_bytes();
        depth_img.bytes_per_pixel = depth_frame.get_bytes_per_pixel();
        depth_img.num_bytes = depth_frame.get_data_size();
        depth_img.pixel_data = depth_pixel_data;
        depth_img.meters_per_unit = depth_frame.get_units(); // conversion ratio from pixel value to distance in meters
        DepthImage_publish(lcm_object, "SENSOR_DEPTH_IMAGE", &depth_img);
    }
    p.stop();
    accelThread.join();
    gyroThread.join();
    return 0;
}
