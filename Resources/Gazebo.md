--->roslaunch turtlebot_gazebo turtlebot_world.launch

    Choose the World tab on the Gazebo left panel.
    Click on Models.
    Click on mobile_base and in the window below, you will see two columns: Property and Value.
    Click on the arrowhead at pose.

--->rosservice list | grep mobile_base
--->rosservice call gazebo/get_model_state '{model_name: mobile_base}'
--->rosnode info /cmd_vel_mux

to make the robot move.
--->roslaunch turtlebot_teleop keyboard_teleop.launch
--->rostopic echo /odom

/turtlebot_teleop_keyboard node publish to 
/cmd_vel_mux/input/teleop topic

need to kill /turtlebot_teleop_keyboard before it can move

move the TurtleBot in a simple straight line
--->rostopic pub -r 10 <topic> \geometry_msgs/Twist '{linear: {x: 0.1, y: 0, z: 0}, angular: {x: 0, y: 0, z: -0.6}}'