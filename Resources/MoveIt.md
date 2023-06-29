MoveIt is a software for manipulation, which is integrated with ROS
    MoveIt - a ROS package for manipulation
    MoveIt Setup Assistant - configure robot setups to use MoveIt
    Plan and execute motions - the "move_group" ROS node.
    Implement a simple pick and place pipeline



Manipulation consists of multiple successive steps. These steps are also known as functional modules.

    We need to sense the environment somehow.
    We need to plan the motion we wish to perform.
    We need to check we won't collide with anything while moving.
    We need to calculate our trajectory and how fast we want to go.

 Per functional modules, there are many software options. 

        Sensors: [Real Sense](http://wiki.ros.org/RealSense/) or the Ensenso 3D camera
        Motion planning: OMPL or CHOMP
        Collision Checking: Flexible Collision Library (FCL) or Bullet Physics Library
        Trajectory processing: Iterative Parabolic Time Parameterization (IPTP) or Time Optimal Path Paramaterization (TOPP)
        Motion Execution: Various robot drivers that are developed and supported by the ROS-Industrial consortium

Import Note:
These are only a few of the example, more can be found on the ROS Wiki. 
