#include "lcmtypes/DepthImage.hpp"
#include "lcmtypes/Image.hpp"
#include "opencv2/opencv.hpp"
#include "lcm/lcm-cpp.hpp"
#include "lcmtypes/imu_t.hpp"


// TODO: save into c type classes
// TODO: change the name of the class
class ImageDisplay
{
    public:
        void handleColor(const lcm::ReceiveBuffer* buf, const std::string& channel, const Image* img);
        void handleDepth(const lcm::ReceiveBuffer* buf, const std::string& channel, const DepthImage* img);
        void handleGyro(const lcm::ReceiveBuffer* buf, const std::string& channel, const imu_t* img);
        void handleAccel(const lcm::ReceiveBuffer* buf, const std::string& channel, const imu_t* img);
        ImageDisplay(lcm::LCM& instance,std::string saveToFolder);
        void subscribe();
    private:
        cv::Mat colorImg_;
        cv::Mat depthImg_;
        // std::vector<float> angVelocities_;
        // std::vector<float> accelerations_;
        lcm::LCM& lcmInstance_;
        std::string saveToFolder_;
};