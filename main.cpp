#include <librealsense2/rs.hpp> // Includes real sense cross platform API
#include <lcm/lcm-cpp.hpp>
#include "DepthImage.hpp"
#include "Image.hpp"

int main()
{
    lcm::LCM lcm_object; // keep the correct address
    rs2::pipeline p;     // create a pipe-line
  

    //Create a configuration for configuring the pipeline with a non default profile
    rs2::config cfg;

    //Add desired streams to configuration
    cfg.enable_stream(RS2_STREAM_COLOR, 640, 480, RS2_FORMAT_BGR8, 15);
    cfg.enable_stream(RS2_STREAM_DEPTH, 640, 480, RS2_FORMAT_Z16, 15);

    p.start(cfg);           // start the pipeline

    // Capture 30 frames to give autoexposure, etc. a chance to settle
    for (auto i = 0; i < 30; ++i)
    {
        p.wait_for_frames();
    }
    Image color_img;
    DepthImage depth_img;

    while (true)
    {
        rs2::frameset frames = p.wait_for_frames();
        //get a frame of depth image
        rs2::video_frame color_frame = frames.get_color_frame();
        rs2::depth_frame depth_frame = frames.get_depth_frame();

        // get color image info
        const int w_color = color_frame.get_width();
        const int h_color = color_frame.get_height();
        uint8_t *color_pixel_data = (uint8_t *)color_frame.get_data();

        // get depth image info
        const int w_depth = depth_frame.get_width();
        const int h_depth = depth_frame.get_height();
        uint8_t *depth_pixel_data = (uint8_t *)depth_frame.get_data();

        // publish color image
        color_img.utime = color_frame.get_timestamp();
        color_img.width = w_color;
        color_img.height = h_color;
        color_img.line_stride = color_frame.get_stride_in_bytes();
        color_img.bytes_per_pixel = color_frame.get_bytes_per_pixel();
        color_img.num_bytes = color_frame.get_data_size();
        color_img.pixel_data.clear();
        std::copy(color_pixel_data, color_pixel_data + (color_img.num_bytes), std::back_inserter(color_img.pixel_data));
        lcm_object.publish("SENSOR_RGB_IMAGE", &color_img);

        // publish depth image
        depth_img.utime = depth_frame.get_timestamp();
        depth_img.width = w_depth;
        depth_img.height = h_depth;
        depth_img.line_stride = depth_frame.get_stride_in_bytes();
        depth_img.bytes_per_pixel = depth_frame.get_bytes_per_pixel();
        depth_img.num_bytes = depth_frame.get_data_size();
        depth_img.pixel_data.clear();
        std::copy(depth_pixel_data, depth_pixel_data + (depth_img.num_bytes), std::back_inserter(depth_img.pixel_data));
        depth_img.meters_per_unit = depth_frame.get_units(); // conversion ratio from pixel value to distance in meters
        lcm_object.publish("SENSOR_DEPTH_IMAGE", &depth_img);
    }
}
