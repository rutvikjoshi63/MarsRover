--->roslaunch turtlebot_gazebo turtlebot_world.launch

    Choose the World tab on the Gazebo left panel.
    Click on Models.
    Click on mobile_base and in the window below, you will see two columns: Property and Value.
    Click on the arrowhead at pose.

--->rosservice list | grep mobile_base
services list related to the turtlebot mobile base

--->rosservice call gazebo/get_model_state '{model_name: mobile_base}'
where the robot is located in the environment

--->rosnode list

--->rosnode info /cmd_vel_mux

to make the robot move.
--->roslaunch turtlebot_teleop keyboard_teleop.launch
--->rosnode info /turtlebot_teleop_keyboard

--->rostopic echo /odom
--->rostopic echo /odom/twist
Now you will see only the twist part of the odometry, it has two components, linear and angular, keep moving the turtlebot to see how they change.

/turtlebot_teleop_keyboard node publish to 
/cmd_vel_mux/input/teleop topic

need to kill /turtlebot_teleop_keyboard before it can move

move the TurtleBot in a simple straight line
--->rostopic pub -r 10 <topic> \geometry_msgs/Twist '{linear: {x: 0.1, y: 0, z: 0}, angular: {x: 0, y: 0, z: -0.6}}'

open up a pre-configured RViz file
--->roslaunch turtlebot_rviz_launchers view_robot.launch

Mapping
When using the metro type of representation of the map likely to have topological maps
When using the lateral & longitudinal type of representation of the map likely to have metric maps

The Turtlebot uses a SLAM implementation called “gmapping”, and a laser scanner to gather information about the environment and build a map



Localization methods are grouped into two categories: Global and Local.

Global:

    Give a location with respect to the world
    Often inaccurate compared to local methods
    For example: GPS or Wi-Fi hotspots

Local:

    Give a location with respect to local sensor feedback
    Can be highly accurate compared to global methods
    For example laser scanner and on-board cameras

TurtleBot in simulation

To run the Turtlebot simulator, we will use the files that come with the course installation
--->roslaunch turtlebot_gazebo turtlebot_world.launch

gmapping is a specific SLAM implementation
--->roslaunch turtlebot_gazebo gmapping_demo.launch
--->rosnode info /slam_gmapping
Publications: 
 * /map [nav_msgs/OccupancyGrid]
 * /map_metadata [nav_msgs/MapMetaData]
 * /rosout [rosgraph_msgs/Log]
 * /slam_gmapping/entropy [std_msgs/Float64]
 * /tf [tf2_msgs/TFMessage]

Subscriptions: 
 * /clock [rosgraph_msgs/Clock]
 * /scan [sensor_msgs/LaserScan]
 * /tf [tf2_msgs/TFMessage]
 * /tf_static [tf2_msgs/TFMessage]

Services: 
 * /dynamic_map
 * /slam_gmapping/get_loggers
 * /slam_gmapping/set_logger_level

To visualize the mapping process open up RViz. We can open up a 'blank' RViz window and add our robot model and further settings. However, it's easier to load up a configuration
--->roslaunch turtlebot_rviz_launchers view_navigation.launch

    Set LaserScan/size(m) to 0.06
    Set LaserScan/style to 'flat squares'
    Set Localmap/Costmap/Topic to /map
    Set Globalmap/Costmap/Topic to /map

--->roslaunch turtlebot_teleop keyboard_teleop.launch
After moving around for a while you will have created a great map. This map will be very useful when we want to navigate the world. However, we need to save it somewhere

--->rosrun map_server map_saver -f $HOME/<choose a directory>/test_map


















