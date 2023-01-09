#include<ros/ros.h>
#include "sensor_msgs/Image.h"
#include "ball_chaser/DriveToTarget.h"

class process_image_
{
public:
  process_image_()
  {
    image_recieve = n.subscribe("/camera/rgb/image_raw",10,&process_image_::process_image_callback,this);
    client_ = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");
  }
  void process_image_callback(const sensor_msgs::Image& img)
  {
     int white_pixel = 255;
     for(int i = 0; i< img.height * img.step; i++)
     { if(img.data[i]==white_pixel) {check_ball_position(i, img); break;}}
  }
  void check_ball_position(int i, const sensor_msgs::Image& img)
  {
     int ball_position_horizontal = i % img.step; 
     float angularZ = (ball_position_horizontal )/img.step - 0.5;
     float linearX;
     if(angularZ < 0.2 && angularZ > -0.2) linearX = 1; 
     else linearX = 0.5;
     
     //Service requests to the robot in the simulator.
     ball_chaser::DriveToTarget srv;
     srv.request.linear_x = linearX;
     srv.request.angular_z = angularZ;
     if(!client_.call(srv)){ROS_ERROR("Service message not passed to the motors");}
     ROS_INFO_STREAM(std::to_string(angularZ));
     
  }

private:
  ros::NodeHandle n;
  ros::Subscriber image_recieve;
  ros::ServiceClient client_;
  
};

int main(int argc, char** argv)
{
  ros::init(argc,argv,"process_image");
  
  process_image_ obj;
  
  ros::spin();
  
  return 0;
}

