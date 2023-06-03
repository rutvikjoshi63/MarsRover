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
-1 after pub  will send a single message to the topic then exit

rostopic pub – This commands ROS to publish a new topic
/hello – This is the name of the new topic.
std_msgs/String – This is the topic type if we want to publish a string topic.
“Hello Robot” – This is the actual data contained by the topic. I.E. the message itself.


3. help option to get the available sub-commands for rostopic 
-->rostopic -h

Check list of all ROS topics
-->rostopic list

-->rostopic type [topic]
returns the message type of any topic being published

-->rostopic hz [topic]
rostopic hz reports the rate at which data is published. 

4. Check the topic to see the message
-->rostopic echo /hello

5. Check list of all ROS Nodes
-->rosnode list

rosnode command, ping, to test that it
-->rosnode ping [node_name]

Because we asked rostopic to publish the /hello topic, ROS went ahead and created a node to do so.

6. look into details of Ros node and topic
-->rosnode info <Name of the concerned node>

-->rostopic info <Name of the concerned topic>

7. Using the package name to directly run a node within a package (without having to know the package path). 
-->rosrun [package_name] [node_name]
you can reassign Names from the command-line by Remapping Argument to change the node's name:
-->rosrun [package_name] [node_name] __name:=[new name]

8. Using rqt_graph
rqt_graph creates a dynamic graph of what's going on in the system. rqt_graph is part of the rqt package
-->rosrun rqt_graph rqt_graph

Using rqt_plot
rqt_plot displays a scrolling time plot of the data published on topics
-->rosrun rqt_plot rqt_plot

9. Using rosservice
Services are another way that nodes can communicate with each other. Services allow nodes to send a request and receive a response
-->rosservice list

Find type of Ros service
-->rosservice type [service]
std_srvs/Empty means when the service call is made it takes no arguments (i.e. it sends no data when making a request and receives no data when receiving a response).
-->rosservice type /spawn | rossrv show
guessing that rossrv show needed to input spawn location??
##Need to confirm  rossrv show

Call ROS service
-->rosservice call [service] [args]
rosservice call /spawn 2 2 0.2 ""
"" for name of turtule decided by ROS

10. Using rosparam
rosparam allows you to store and manipulate data on the ROS Parameter Server. The Parameter Server can store integers, floats, boolean, dictionaries, and lists
rosparam uses the YAML markup language for syntax
1 is an integer, 
1.0 is a float, 
one is a string, 
true is a boolean, 
[1, 2, 3] is a list of integers, and 
{a: b, c: d} is a dictionary
Usage:
rosparam set            set parameter
rosparam get            get parameter
rosparam load           load parameters from file
rosparam dump           dump parameters to file
rosparam delete         delete parameter
rosparam list           list parameter names

rosparam dump and rosparam load
-->rosparam dump [file_name] [namespace]
-->rosparam load [file_name] [namespace]

11. Using rqt_console and roslaunch
rqt_console attaches to ROS's logging framework to display output from nodes. rqt_logger_level allows us to change the verbosity level (Fatal
Error
Warn
Info
Debug) of nodes as they run

-->rosrun rqt_console rqt_console
-->rosrun rqt_logger_level rqt_logger_level

12. Using roslaunch
roslaunch starts nodes as defined in a launch file
-->roslaunch [package] [filename.launch]

The Launch File
<launch>
Here we start the launch file with the launch tag, so that the file is identified as a launch file. 

<group ns="turtlesim1">
    <node pkg="turtlesim" name="sim" type="turtlesim_node"/>
</group>
Here we start many groups with a namespace tag of turtlesim1 and turtlesim2 with a turtlesim node with a name of sim. This allows us to start many simulators without having name conflicts

 <node pkg="turtlesim" name="mimic" type="mimic">
  <remap from="input" to="turtlesim1/turtle1"/>
  <remap from="output" to="turtlesim2/turtle1"/>
 </node>

























subscribe to a message


























































