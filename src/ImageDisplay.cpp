#include "ImageDisplay.h"

void ImageDisplay::handleColor(const lcm::ReceiveBuffer* buf, const std::string& channel, const Image* img)
{
    cv::Mat newImg(img->height,img->width, CV_8UC3, (void*)&(img->pixel_data[0]), img->line_stride);
    colorImg_ = newImg;
    std::string timestamp = std::to_string(img->utime);
    std::string fName = "/home/vulcan/03_sai/04_data/image_data/homo_matrix/color/" + timestamp + ".png";
    cv::imwrite(fName, colorImg_);
    std::ofstream file;
    file.open("/home/vulcan/03_sai/04_data/image_data/homo_matrix/color/times.txt",std::ios::app);
    if(!file.is_open()){std::cout << "times.txt could not be opened for color" << std::endl;}
    file << timestamp << "\n";
    file.close();
    // Display in a GUI
    // cv::namedWindow("RGB Image", cv::WINDOW_AUTOSIZE);
    // cv::imshow("RGB Image", colorImg_);
    // cv::waitKey(1);
}

void ImageDisplay::handleDepth(const lcm::ReceiveBuffer* buf, const std::string& channel, const DepthImage* img)
{
    cv::Mat newImg(img->height,img->width, CV_16UC1, (void*)&(img->pixel_data[0]));
    depthImg_ = newImg;
    std::cout<< img->meters_per_unit << "\n";
    std::string timestamp = std::to_string(img->utime);
    std::string fName = "/home/vulcan/03_sai/04_data/image_data/homo_matrix/depth/" + timestamp + ".png";
    cv::imwrite(fName, depthImg_);
    std::ofstream file;
    file.open("/home/vulcan/03_sai/04_data/image_data/homo_matrix/depth/times.txt",std::ios::app);
    if(!file.is_open()){std::cout << "times.txt could not be opened for depth" << std::endl;}
    file << timestamp << "\n";
    file.close();
    // Display in a GUI
    // cv::imshow("Depth Image", depthImg_);
    // cv::waitKey(1);
}

void ImageDisplay::subscribe()
{
    lcmInstance_.subscribe("SENSOR_RGB_IMAGE",&ImageDisplay::handleColor,this);
    lcmInstance_.subscribe("SENSOR_DEPTH_IMAGE",&ImageDisplay::handleDepth,this);
}

ImageDisplay::ImageDisplay(lcm::LCM& instance):
lcmInstance_(instance)
{
    // cv::namedWindow("RGB Image", cv::WINDOW_AUTOSIZE);
    // cv::namedWindow("Depth Image", cv::WINDOW_AUTOSIZE);
}