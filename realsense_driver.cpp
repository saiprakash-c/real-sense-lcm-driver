#include <librealsense2/rs.hpp> // Includes real sense cross platform API
#include <opencv2/opencv.hpp>
#include <lcm/lcm-cpp.hpp>
#include "rgbd_data.hpp"

void PublishBGRDToLCM(const cv::Mat& bgr_image, const cv::Mat& depth_image, const lcm::LCM& lcm_object)
{
    rgbd_data rgbd_lcm();
    rgbd_lcm.utime = ;
    rgbd_lcm.width = bgr_image.cols;
    rgbd_lcm.height =bgr_image.rows;
    rgbd_lcm.num_pixels = rgbd_lcm.width * rgbd_lcm.height;
    for(int i=0;i<3;++i)
    {
        for(int j=0;j<rgbd_lcm.height;++j)
        {
            for(int k=0;k<rgbd_lcm.width;++k)
            {
                rgbd_lcm.rgb[j*rgbd_lcm.height+k][i] = rgb_image[2-i][j][k];
            }
        }

    } 

    for(int j=0;j<rgbd_lcm.height;++j)
        {
            for(int k=0;k<rgbd_lcm.width;++k)
            {
                rgbd_lcm.depth[j*rgbd_lcm.height+k] = depth_image[j][k];
            }
        }
    }
    lcm_object.publish( "RGBD_DATA_CHANNEL",&rgb_lcm);

}

int main()
{
    lcm::LCM lcm_object(); // keep the correct address
    rs2::pipeline p; // create a pipe-line
    p.start();       // start the pipeline

    // don't store the first few images

    // Capture 30 frames to give autoexposure, etc. a chance to settle
    for (auto i = 0; i < 30; ++i)
        p.wait_for_frames();

    while (true)
    {
        rs2::frameset frames = p.wait_for_frames();
        //get a frame of depth image
        rs2::depth_frame depth = frames.get_depth_frame();
        rs2::video_frame bgr = frames.get_color_frame();

        const int w_depth = depth.as<rs2::video_frame>().get_width();
        const int h_depth = depth.as<rs2::video_frame>().get_height();

        const int w_bgr = bgr.as<rs2::video_frame>().get_width();
        const int h_bgr = bgr.as<rs2::video_frame>().get_height();


        cv::Mat depth_image(cv::Size(w_depth, h_depth),CV_16UC3, (void*)depth.get_data(),cv::Mat::AUTO_STEP);
        cv::Mat bgr_image(cv::Size(w_bgr, h_bgr),CV_8UC3, (void*)bgr.get_data(),cv::Mat::AUTO_STEP);

        // publish to lcm
        PublishBGRDToLCM(bgr_image, depth_image, lcm_object);
    }
}
