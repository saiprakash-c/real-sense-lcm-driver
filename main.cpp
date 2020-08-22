#include <librealsense2/rs.hpp> // Includes real sense cross platform API
#include <lcm/lcm-cpp.hpp>
#include "ColorImage.hpp"
#include "DepthImage.hpp"

int main()
{
    lcm::LCM lcm_object; // keep the correct address
    rs2::pipeline p;       // create a pipe-line
    p.start();             // start the pipeline

    // Capture 30 frames to give autoexposure, etc. a chance to settle
    for (auto i = 0; i < 30; ++i)
        p.wait_for_frames();

    ColorImage color_img;
    DepthImage depth_img;

    while (true)
    {
        rs2::frameset frames = p.wait_for_frames();
        //get a frame of depth image
        rs2::video_frame bgr = frames.get_color_frame();
        rs2::depth_frame depth = frames.get_depth_frame();

        // get color image info
        const int w_bgr = bgr.get_width();
        const int h_bgr = bgr.get_height();
        uint8_t* color_pixel_data = (uint8_t*)bgr.get_data();
    
        // get depth image info
        const int w_depth = depth.get_width();
        const int h_depth = depth.get_height();
        uint8_t* depth_pixel_data = (uint8_t*)depth.get_data();

        // publish color image
        color_img.utime = bgr.get_timestamp();
        color_img.width = w_bgr;
        color_img.height = h_bgr;
        color_img.bytes_per_pixel = bgr.get_bytes_per_pixel();
        color_img.num_bytes = w_bgr * h_bgr * color_img.bytes_per_pixel;
        std::copy(color_pixel_data, color_pixel_data + (color_img.num_bytes), std::back_inserter(color_img.pixel_data));
        lcm_object.publish("RGB_DATA_CHANNEL", &color_img);

        // publish depth image
        depth_img.utime = depth.get_timestamp();
        depth_img.width = w_depth;
        depth_img.height = h_depth;
        depth_img.bytes_per_pixel = depth.get_bytes_per_pixel();
        depth_img.num_bytes = w_depth * h_depth * depth_img.bytes_per_pixel;
        std::copy(depth_pixel_data, depth_pixel_data + (depth_img.num_bytes), std::back_inserter(depth_img.pixel_data));
        depth_img.meters_per_unit = depth.get_units(); // conversion ratio from pixel value to distance in meters
        lcm_object.publish("DEPTH_DATA_CHANNEL", &depth_img);
    }
}
