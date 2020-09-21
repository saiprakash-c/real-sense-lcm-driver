#include <librealsense2/rs.hpp> // Includes real sense cross platform API
#include <lcm/lcm-cpp.hpp>
#include "DepthImage.hpp"
#include "Image.hpp"
#include "ImageDisplay.h"


int main(int argc, char* argv[])
{
    // create an lcm instance
    lcm::LCM lcmInstance;
    // create image display instance
    ImageDisplay displayer(lcmInstance);
    // lcm subscribe
    displayer.subscribe();
    // handle lcm in a loop
    while(true)
    {
        lcmInstance.handle();
    }
    return 0;
}