#include "DepthImage.hpp"
#include "Image.hpp"
#include "opencv2/opencv.hpp"
#include "lcm/lcm-cpp.hpp"

class ImageDisplay
{
    public:
        void handleColor(const lcm::ReceiveBuffer* buf, const std::string& channel, const Image* img);
        void handleDepth(const lcm::ReceiveBuffer* buf, const std::string& channel, const DepthImage* img);
        ImageDisplay(lcm::LCM& instance);
        void subscribe();
    private:
        cv::Mat colorImg_;
        cv::Mat depthImg_;
        lcm::LCM& lcmInstance_;
};