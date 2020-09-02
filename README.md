# Intel Realsense LCM driver 

Inteal Realsense LCM driver connects to a Realsense device and publishes RGB and depth images as LCM messages.  

The driver is tested only with Realsense D435 in Ubuntu 18.04. But it should work for any D400 series device. The lcmtypes of RGB and depth images are in `lcmtypes` folder. The channels for RGB and depth images are **SENSOR_RGB_IMAGE** and **SENSOR_DEPTH_IMAGE** repsectively.

## Prerequisites

Before you begin, ensure you have met the following requirements:
<!--- These are just example requirements. Add, duplicate or remove as required --->

* You have a `Linux` machine. 
* [librealsense 2.36.0](https://github.com/IntelRealSense/librealsense) 
* [lcm 1.4.0](https://github.com/lcm-proj/lcm)

## Installing

To install the project, follow these steps:

```
git clone https://github.com/saiprakash-c/real-sense-lcm-driver.git
cd real-sense-lcm-driver
mkdir {build,bin,lib}
cd build
cmake ..
make
```
## Usage

To use real sense driver, follow these steps:

1. Connect the realsense device 
2. Run `realsense-viewer` to check if the realsense is connected
```
realsense-viewer
```
3. Once you know realsense is connected, run `realsense-driver` to publish the messages
```
 ./bin/realsense-driver
```
3. Run `lcm-spy` to check if the messages are getting published
```
./buildjar.sh
./runspy.sh
```
To subscribe to the message and use it, please refer to the `Receiving LCM Message` section [here](https://lcm-proj.github.io/tut_cpp.html) 

## Contact

If you want to contact me, you can reach me at saip@umich.edu
