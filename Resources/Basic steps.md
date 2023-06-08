# MarsRover
All files generated while working @Mars Rover IIT-B
##Creating ROS Catkin Package
1. -->cd ~/catkin_ws/src

2. -->catkin_create_pkg <package_name> [depend1] [depend2] [depend3]
std_msgs rospy roscpp

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

To know Published topics & Subscribed topics
-->rostopic -v

Check list of all ROS topics
-->rostopic list
-->rostopic list | grep counter
to check counter topic 

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

12. Using roslaunch and mimicing nodes.
roslaunch starts nodes as defined in a launch file. Open package directory and run
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

we start the mimic node with the topics input and output renamed to turtlesim1 and turtlesim2. This renaming will cause turtlesim2 to mimic turtlesim1

13. Using rosed
allows you to directly edit a file within a package by using the package name rather than having to type the entire path to the package. 
-->rosed [package_name] [filename]
-->source devel/setup.bash
-->roscd beginner_tutorials

14. msg and srv
msg: msg files are simple text files that describe the fields of a ROS message. They are used to generate source code for messages in different languages.

srv: an srv file describes a service. It is composed of two parts: a request and a response. The two parts are separated by a '---' line.

#Need to understand better//
    Creating a msg-
-->roscd [package_name]
-->mkdir msg
-->echo "int64 num" > msg/Num.msg
Open package.xml
--><build_depend>message_generation</build_depend>
--> <exec_depend>message_runtime</exec_depend>
at build time, we need "message_generation", while at runtime, we only need "message_runtime". 

Open CMakeLists.txt
find_package(catkin REQUIRED COMPONENTS
   roscpp
   rospy
   std_msgs
-->message_generation
)
export the message runtime dependency#How?
find:

 add_message_files(
   FILES
   Num.msg
 )
 ...
 add_service_files(
  FILES
  AddTwoInts.srv
)
...
 ensure the generate_messages() function is called
 generate_messages(
  DEPENDENCIES
  std_msgs
)
...

    Using rosmsg
-->rosmsg show [message type]   
[message type] will be [package_name]/[filename of the msg(without.msg)]

can't remember which Package a msg is in
-->rosmsg show [filename of the msg(without.msg)]

    Creating a srv
-->mkdir srv
Instead of creating a new srv definition copy an existing one
copying files from one package to another
-->roscp [package_name] [file_to_copy_path] [copy_path]
-->roscp rospy_tutorials AddTwoInts.srv srv/AddTwoInts.srv
open package.xml & Open CMakeLists.txt & follow same steps

    Using rossrv
-->rossrv show <service type>
<service type> will be [package_name]/[filename of the srv]
-->rossrv show [filename of the srv]

Now that we have made some new messages we need to make our package again
#Difference?
-->catkin_make/catkin build

    Getting Help
-->rosmsg -h

15. Publishing and subscribing (C++)Don't forget to make the node executable
after writing code in /src

add these few lines to the bottom of your CMakeLists.txt 
eg:
-->add_executable(talker src/talker.cpp)
-->target_link_libraries(talker ${catkin_LIBRARIES})
-->add_dependencies(talker beginner_tutorials_generate_messages_cpp)

This will create two executables, talker and listener, which by default will go into package directory of your devel space

add_dependencies(...) makes sure message headers of this package are generated before being used
you use messages from other packages inside your catkin workspace, you need to add dependencies to their respective generation targets as well, because catkin builds all projects in parallel

use the following variable to depend on all necessary targets: 
target_link_libraries(talker ${catkin_LIBRARIES})

make sure you have sourced your workspace's setup.sh file after calling catkin_make
running subscriber and publisher
-->rosrun [projectname] [filename]


Publishing and subscribing (Python)Don't forget to make the node executable
First create a 'scripts' folder to store our Python scripts in: 
after writing code in /scripts

Edit CMakelist
catkin_install_python(PROGRAMS scripts/talker.py scripts/listener.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

running subscriber and publisher
-->rosrun [projectname] [filename]


16. Writing a Service Node(C++)Don't forget to make the node executable
Create the filename.cpp for service node

Writing a Client Node(C++)Don't forget to make the node executable
Create the filename.cpp for client node
add these few lines to the bottom of your CMakeLists.txt 
eg:
-->add_executable(talker src/talker.cpp)
-->target_link_libraries(talker ${catkin_LIBRARIES})
-->add_dependencies(talker beginner_tutorials_generate_messages_cpp)

make sure you have sourced your workspace's setup.sh file after calling catkin_make

Writing a Service Node & client(Python)Don't forget to make the node executable
-->roscd [projectname]

Create the scripts/[filename].py file within the beginner_tutorials package and write code

17. Recording and playing back data
record data from a running ROS system into a .bag file, and then to play back the data to produce similar behavior in a running system

Recording data (creating a bag file)
First examine the full list of topics that are currently being published in the running system. The list of published topics are the only message types that could potentially be recorded in the data log file, as only published messages are recorded

-->mkdir ~/bagfiles
-->cd ~/bagfiles
-->rosbag record -a
a temporary directory to record data and then running rosbag record with the option -a, indicating that all published topics should be accumulated in a bag file. 

Examining and playing the bag file
-->rosbag info <your bagfile>
info command checks the contents of the bag file without playing it back

First kill the previous program
-->rosbag play <your bagfile>
 If rosbag play publishes messages immediately upon advertising, subscribers may not receive the first several published messages. The waiting period can be specified with the -d option. 

-->rosbag play -r 2 <your bagfile>
change the rate of publishing by a specified factor(-r)
change the start of publishing by a specified factor(-s)

Recording a subset of the data
eg:
rosbag record -O subset /turtle1/cmd_vel /turtle1/pose
-O argument tells to log to a file named subset.bag & arguments cause to only subscribe to these two topics

18. Reading messages from a bag file
manually inspect all published topics and how many messages were published to each topic with this command: 
-->time rosbag info demo.bag  
-->roscore

Subscribe to the topic of interest & echo everything published on this topic while also teeing it to a file for later review, all in yaml format: 
-->rostopic echo <topic of interest> | tee topic1.yaml
-->rostopic echo <topic of interest2> | tee topic2.yaml

Each topic must have its own terminal. 

In another terminal we play the bag file
-->time rosbag play --immediate demo.bag --topics /topic1 /topic2 /topic3 /topicN
/topic1 : <topic of interest>
you'll see the output of all messages for each topic type, in YAML format in terminals which were each subsribed to a topic

19. Getting started with roswtf
roswtf will warn you about things that look suspicious but may be normal in your system. It can also report errors for problems that it knows are wrong

1. Checking your installation
-->roscd rosmaster
-->roswtf

ubuntu open any file from terminal command
-->xdg-open [filename]

to make the node executable
-->chmod +x [filename]



























































