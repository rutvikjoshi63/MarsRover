1. Running the Demo
--->roslaunch turtle_tf2 turtle_tf2_demo.launch
This demo is using the tf2 library to create three coordinate frames: a world frame, a turtle1 frame, and a turtle2 frame. This tutorial uses a tf2 broadcaster to publish the turtle coordinate frames and a tf2 listener to compute the difference in the turtle frames and move one turtle to follow the other. 

2. Using view_frames
view_frames creates a diagram of the frames being broadcast by tf2 over ROS
--->rosrun tf2_tools view_frames.py
Here a tf2 listener is listening to the frames that are being broadcast over ROS and drawing a tree of how the frames are connected

--->evince frames.pdf

3. Using tf_echo
tf_echo reports the transform between any two frames broadcast over ROS
--->rosrun tf tf_echo [reference_frame] [target_frame]
rosrun tf tf_echo turtle1 turtle2

4. rviz is a visualization tool that is useful for examining tf2 frames
--->rosrun rviz rviz -d `rospack find turtle_tf2`/rviz/turtle_rviz.rviz
































