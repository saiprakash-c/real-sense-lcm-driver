#include "ImageDisplay.h"

void ImageDisplay::handleColor(const lcm::ReceiveBuffer* buf, const std::string& channel, const Image* img)
{
    cv::Mat newImg(img->height,img->width, CV_8UC3, (void*)&(img->pixel_data[0]), img->line_stride);
    colorImg_ = newImg;
    std::string timestamp = std::to_string(img->utime);
    std::string fName = "../images/" + timestamp + ".png";
    cv::imwrite(fName, colorImg_ );
    std::ofstream file;
    file.open("../images/rgb.txt",std::ios::app);
    if(!file.is_open()){std::cout << "rgb.txt could not be opened" << std::endl;}
    file << time << "\n";
    file.close();
    // Display in a GUI
    // cv::namedWindow("RGB Image", cv::WINDOW_AUTOSIZE);
    // cv::imshow("RGB Image", colorImg_);
    // cv::waitKey(1);
}

void ImageDisplay::handleDepth(const lcm::ReceiveBuffer* buf, const std::string& channel, const DepthImage* img)
{
    cv::Mat newImg(img->height,img->width, CV_16SC1, (void*)&(img->pixel_data[0]));
    depthImg_ = newImg;
    std::cout<< img->meters_per_unit << "\n";
    std::string timestamp = std::to_string(img->utime);
    std::string fName = "../images/" + timestamp + ".png";
    cv::imwrite(fName, depthImg_ );
    //  file.open("../images/depth.txt",std::ios::app);
    // if(!file.is_open()){std::cout << ".txt could not be opened" << std::endl;}
    // file << time << " " << fName << "\n";
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