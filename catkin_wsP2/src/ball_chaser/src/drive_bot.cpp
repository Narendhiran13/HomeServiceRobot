#include<ros/ros.h>
#include "geometry_msgs/Twist.h"
#include "ball_chaser/DriveToTarget.h"

class drive_bot_
{
public:
	
	drive_bot_()
	{
		client_ = n.advertiseService("/ball_chaser/command_robot",&drive_bot_::handle_drive_request,this);
		motor_command_publisher = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
	}
	bool handle_drive_request(ball_chaser::DriveToTarget::Request& req, ball_chaser::DriveToTarget::Response& res)
	{
		geometry_msgs::Twist motor_command;
		while(ros::ok()){
			//ball_chaser::DriveToTarget srv;
			motor_command.linear.x = req.linear_x;
			motor_command.angular.z= req.angular_z;
			motor_command_publisher.publish(motor_command);
			ros::Duration(3).sleep();
			res.msg_feedback = "Published the velocities";
			//if(!client_.call(srv)){ROS_ERROR("Error while requesting service");}
		}
		return true;
	}

private:
	ros::NodeHandle n;
	ros::ServiceServer client_;
	ros::Publisher motor_command_publisher;
};

int main(int argc, char** argv)
{
	ros::init(argc,argv,"drive_bot");

	drive_bot_ object;
	
	ros::spin();
	
	return 0;
}
