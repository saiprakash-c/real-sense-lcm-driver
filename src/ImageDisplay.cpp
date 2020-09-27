#include "ImageDisplay.h"

void ImageDisplay::handleColor(const lcm::ReceiveBuffer* buf, const std::string& channel, const Image* img)
{
    cv::Mat newImg(img->height,img->width, CV_8UC3, (void*)&(img->pixel_data[0]), img->line_stride);
    colorImg_ = newImg;
    std::string timestamp = std::to_string(img->utime);
    std::string fName = saveToFolder_+"/color/" + timestamp + ".png";
    cv::imwrite(fName, colorImg_);
    std::ofstream file;
    file.open(saveToFolder_+"/color/times.txt",std::ios::app);
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
    std::string fName = saveToFolder_+"/depth/" + timestamp + ".png";
    cv::imwrite(fName, depthImg_);
    std::ofstream file;
    file.open(saveToFolder_+"/depth/times.txt",std::ios::app);
    if(!file.is_open()){std::cout << "times.txt could not be opened for depth" << std::endl;}
    file << timestamp << "\n";
    file.close();
    // Display in a GUI
    // cv::imshow("Depth Image", depthImg_);
    // cv::waitKey(1);
}

/**
 * callback function to receive angular velocities from gyroscope
 */
void ImageDisplay::handleGyro(const lcm::ReceiveBuffer* buf, const std::string& channel, const imu_t* imuData)
{
    std::ofstream file;
    file.open(saveToFolder_+"/angular_velocities.txt",std::ios::app);
    if(!file.is_open()){std::cout << "angular_velocities.txt could not be opened" << std::endl;}
    file << imuData->utime << "," << imuData->gyro[0] << "," << imuData->gyro[1] << "," << imuData->gyro[2] << '\n';
    file.close();
}

/**
 * callback function to receive accelerations from accelerometer
 */
void ImageDisplay::handleAccel(const lcm::ReceiveBuffer* buf, const std::string& channel, const imu_t* imuData)
{
    std::ofstream file;
    file.open(saveToFolder_+"/accelerations.txt",std::ios::app);
    if(!file.is_open()){std::cout << "accelerations.txt could not be opened" << std::endl;}
    file << imuData->utime << "," << imuData->accel[0] << "," << imuData->accel[1] << "," << imuData->accel[2] << '\n';
    file.close();
}

void ImageDisplay::subscribe()
{
    lcmInstance_.subscribe("SENSOR_RGB_IMAGE",&ImageDisplay::handleColor,this);
    lcmInstance_.subscribe("SENSOR_DEPTH_IMAGE",&ImageDisplay::handleDepth,this);
    lcmInstance_.subscribe("SENSOR_CAMERA_GYRO",&ImageDisplay::handleGyro,this);
    lcmInstance_.subscribe("SENSOR_CAMERA_ACCEL",&ImageDisplay::handleAccel,this);
}

ImageDisplay::ImageDisplay(lcm::LCM& instance, std::string saveToFolder):
lcmInstance_(instance),
saveToFolder_(saveToFolder)
{
    // cv::namedWindow("RGB Image", cv::WINDOW_AUTOSIZE);
    // cv::namedWindow("Depth Image", cv::WINDOW_AUTOSIZE);
}