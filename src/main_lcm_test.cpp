#include <librealsense2/rs.hpp> // Includes real sense cross platform API
#include <lcm/lcm-cpp.hpp>
#include "DepthImage.hpp"
#include "Image.hpp"
#include "ImageDisplay.h"

// TODO:change the name of the file

int main(int argc, char* argv[])
{
    if(argc!=2)
    {
        std::cout << "Please specify the folder where the data needs to be stored!" << "\n";
    }
    // folder where the data should be stored
    std::string saveToFolder(argv[1]);
    // create an lcm instance
    lcm::LCM lcmInstance;
    // create image display instance
    ImageDisplay displayer(lcmInstance, saveToFolder);
    // lcm subscribe
    displayer.subscribe();
    // handle lcm in a loop
    while(true)
    {
        lcmInstance.handle();
    }
    return 0;
}