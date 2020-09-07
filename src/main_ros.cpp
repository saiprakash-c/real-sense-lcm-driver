#include <librealsense2/rs.hpp> // Includes real sense cross platform API

int main(int argc, char* argv[])
{
    rs2::config cfg;
    cfg.enable_record_to_file(argv[1]);
    rs2::pipeline p;       // create a pipe-line
    p.start(cfg);             // start the pipeline

    // Capture 30 frames to give autoexposure, etc. a chance to settle
    for (auto i = 0; i < 30; ++i)
    {
        p.wait_for_frames();
    }

    while (true)
    {
        rs2::frameset frames = p.wait_for_frames();
    }
    p.stop();
}
