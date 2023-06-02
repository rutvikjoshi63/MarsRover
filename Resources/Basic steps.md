# MarsRover
All files generated while working @Mars Rover IIT-B
##Creating ROS Catkin Package
1. -->cd ~/catkin_ws/src

2. -->catkin_create_pkg <package_name> [depend1] [depend2] [depend3]

3. -->catkin_make

4. source the generated setup file

-->. ~/catkin_ws/devel/setup.bash

5. review  first-order dependencies
-->rospack depends1 <package_name>

##Build ROS Package
1. source your environment setup file
--> source /opt/ros/noetic/setup.bash

2. catkin_make combines the calls to cmake and make in the standard CMake workflow.
-->catkin_make
The above commands will build any catkin projects found in the src folder


##Running basics


Step 1:
 1. Starting the ROS Master 
-->roscore
 
2. publish  to a message
-->rostopic pub /hello std_msgs/String “Hello Robot"

rostopic pub – This commands ROS to publish a new topic
/hello – This is the name of the new topic.
std_msgs/String – This is the topic type if we want to publish a string topic.
“Hello Robot” – This is the actual data contained by the topic. I.E. the message itself.


3. Check list of all ROS topics
-->rostopic list

4. Check the topic to see the message
-->rostopic echo /hello

5. Check list of all ROS Nodes
-->rosnode list

Because we asked rostopic to publish the /hello topic, ROS went ahead and created a node to do so.
6. look into details of Ros node and topic
-->rosnode info <Name of the concerned node>

-->rostopic info <Name of the concerned topic>


ubscribe to a message


























































