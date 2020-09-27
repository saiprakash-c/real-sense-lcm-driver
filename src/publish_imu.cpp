#include <librealsense2/rs.hpp>
#include <string>
// include ros
#include <ros/ros.h>
#include <sensor_msgs/Imu.h>

int main(int argc, char* argv[])
{
    // consts
    std::string ACCEL_CHANNEL="accel/data";
    std::string GYRO_CHANNEL="gyro/data";

    // ROS
    // create ros node
    ros::init(argc,argv,"publish_imu");
    // create ros handler
    ros::NodeHandle h("~");
    // create ros publishers
    ros::Publisher accelPublisher=h.advertise<sensor_msgs::Imu>(ACCEL_CHANNEL,1);
    ros::Publisher gyroPublisher=h.advertise<sensor_msgs::Imu>(GYRO_CHANNEL,1);


    // create a configuration 
    rs2::config cfg;
    cfg.enable_stream(RS2_STREAM_ACCEL,RS2_FORMAT_XYZ32F,250);
    cfg.enable_stream(RS2_STREAM_GYRO,RS2_FORMAT_XYZ32F,200);
    // start a pipeline with the above configuration 
    rs2::pipeline p;
    p.start(cfg);
    // enter into loop 
    while(true)
    {
        rs2::frameset frames=p.wait_for_frames();
        // publish acceleration and gyroscope info
        if(rs2::motion_frame accel_frame=frames.first_or_default(RS2_STREAM_ACCEL))
        {
            sensor_msgs::Imu imuData;
            rs2_vector accel_data = accel_frame.get_motion_data();
            // copy into ros msg
            double timestamp=accel_frame.get_timestamp(); // in microsecs
            imuData.header.stamp.sec = (uint64_t)timestamp/1e3;// in secs
            uint64_t diffNSecs = (timestamp-imuData.header.stamp.sec*1e3)*1e6;// in nanosecs
            imuData.header.stamp.nsec = diffNSecs;
            imuData.linear_acceleration.x=accel_data.x;
            imuData.linear_acceleration.y=accel_data.y;
            imuData.linear_acceleration.z=accel_data.z;
            // publish acceleration 
            accelPublisher.publish(imuData);
        }

        if(rs2::motion_frame gyro_frame=frames.first_or_default(RS2_STREAM_GYRO))
        {
            sensor_msgs::Imu imuData;
            rs2_vector gyro_data = gyro_frame.get_motion_data();
            // copy into ros msg
            double timestamp=gyro_frame.get_timestamp(); // in microsecs
            imuData.header.stamp.sec = (uint64_t)timestamp/1e3; // in secs
            uint64_t diffNSecs = (timestamp-imuData.header.stamp.sec*1e3)*1e6;//in nanosecs
            imuData.header.stamp.nsec = diffNSecs;
            imuData.angular_velocity.x=gyro_data.x;
            imuData.angular_velocity.y=gyro_data.y;
            imuData.angular_velocity.z=gyro_data.z;
            // pubish gyroscope
            gyroPublisher.publish(imuData);
        }

    }
    return 0;  
}