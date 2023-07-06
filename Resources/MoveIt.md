MoveIt is a software for manipulation, which is integrated with ROS
    MoveIt - a ROS package for manipulation
    MoveIt Setup Assistant - configure robot setups to use MoveIt
    Plan and execute motions - the "move_group" ROS node.
    Implement a simple pick and place pipeline

Maintains information consistency between our ROS application and the different functional modules.
Integrates the kinematic information our robot setups to the motion planning libraries. 
Takes care of the interaction between collision detection and motion  planning.
Accounts for any hardware limitations of the robot.
Keeps track of Robot location.
Communicates with robot hardware/simulation

ROS node: move_group 
This node provides us with several ROS services and actions.

To use the move_group node, it needs to be configured with some parameters:

        robot-description (URDF/XACRO)
        robot semantic description (SRDF)
        joint limits, planners, etc.

These parameters can be setup by using the MoveIt Setup Assistant.

Manipulation consists of multiple successive steps. These steps are also known as functional modules.

    We need to sense the environment somehow.
    We need to plan the motion we wish to perform.
    We need to check we won't collide with anything while moving.
    We need to calculate our trajectory and how fast we want to go.

 Per functional modules, there are many software options. 

        Sensors: [Real Sense](http://wiki.ros.org/RealSense/) or the [Ensenso 3D camera](https://github.com/ensenso/ros_driver)
        Motion planning: [OMPL](https://ompl.kavrakilab.org/) or CHOMP
        Collision Checking: Flexible Collision Library (FCL) or [Bullet Physics Library](https://pybullet.org/Bullet/BulletFull/)
        Trajectory processing: [Iterative Parabolic Time Parameterization (IPTP)](https://github.com/ros-planning/moveit) or [Time Optimal Path Paramaterization (TOPP)](https://github.com/quangounet/TOPP)
        Motion Execution: Various robot drivers that are developed and supported by the ROS-Industrial consortium

Important Note:
These are only a few of the example, more can be found on the ROS Wiki. 
Hardware drivers are only needed when we work with real robot hardware.
The basis for kinematic information of the robot arms is in their URDF/XACRO files. This information is commonly made available to MoveIt through the robot_description parameter which MoveIt! uses to compute and maintain information about the kinematics of our robots.
Open Motion Planning Library (OMPL) is an open source software library for motion planning. It can also be used independently of MoveIt In its default implementation, MoveIt! only leverages OMPL for motion planning
MoveIt can be configureed to use an Octomap created with 3D point cloud data. Sensor information can also be integrated with MoveIt to realize functionalities like unknown obstacle avoidance

launch the setup assistant
-->roslaunch moveit_setup_assistant setup_assistant.launch

    Click on Create New Moveit Configuration Package

    Add the URDF file path of the Robot Model
            Browse to $HOME/hrwros_ws/src/hrwros_support/urdf/hrwros.xacro or add the full path to that file (i.e. replacing $HOME by the actual folder name)
    Click on Load Files to load the model
            On the right side, a graphical view of the factory will be provided
            The TurtleBot will no be seen on your display as we will not use MoveIt to control it

Self-Collision Checking (left pane) here we set up information regarding what pairs of robot links should be checked for collision. This saves execution time.

        Set the Sampling Density to High and Click on Generate Collision Matrix

Self-collisions checking step is useful because the resulting Collision matrix contains information about all link pairs that will never collide either due to their geometric configuration or it is physically impossible for them to collide

MoveIt checks Self-Collision by sampling random joint values and checking if the configuration collides

This is done using the collision geometry of the URDF files. This process provides a list of link pairs that can be disabled because the can never collide with each other.

Virtual joints are an optional step to give MoveIt a fixed reference in our world this is handy for robot arms on mobile platforms.virtual joints are only used to indicate a fixed reference to our robots, but it is not necessary that they are always configured as fixed

    Define that our URDF is a fixed reference point with respect to robot1_base_link. The same needs to be done for robot2_base_link.

Planning Groups indicate a set of links and joints for which we intend to plan motions using MoveIt! We want to do this for our two robot arms.

    Add Group
            Give the group a name
            Kinematic Solver: trac_ik_kinematics_plugin/TRAC_IKKinematicsPlugin
            Group Default Planner: RRTConnect
            Add Kinematic Chain
                    start: robot1_base_link
                    end: vacuum_gripper1_suction_cup

This needs to be done for any number of robots we would like to control with MoveIt.

*MoveIt Setup Assistant*
-->roslaunch moveit_setup_assistant setup_assistant.launch

This gives a graphical interface where you will need to perform the following steps.

Click on Create New Moveit Configuration Package
Add the URDF file path of the Robot Model
Browse to $HOME/hrwros_ws/src/hrwros_support/urdf/hrwros.xacro or add the full path to that file (i.e. replacing $HOME by the actual folder name)
Click on Load Files to load the model
On the right side, a graphical view of the factory will be provided
The TurtleBot will no be seen on your display as we will not use MoveIt to control it
Self-Collision Checking (left pane) here we set up information regarding what pairs of robot links should be checked for collision. This saves execution time.

Set the Sampling Density to High and Click on Generate Collision Matrix
MoveIt checks Self-Collision by sampling random joint values and checking if the configuration collides

This is done using the collision geometry of the URDF files. This process provides a list of link pairs that can be disabled because the can never collide with each other.

Virtual joints are an optional step to give MoveIt a fixed reference in our world this is handy for robot arms on mobile platforms.

Define that our URDF is a fixed reference point with respect to robot1_base_link. The same needs to be done for robot2_base_link.
Planning Groups indicate a set of links and joints for which we intend to plan motions using MoveIt! We want to do this for our two robot arms.

Add Group
Give the group a name
Kinematic Solver: trac_ik_kinematics_plugin/TRAC_IKKinematicsPlugin
Group Default Planner: RRTConnect
Add Kinematic Chain
start: robot1_base_link
end: vacuum_gripper1_suction_cup
This needs to be done for any number of robots we would like to control with MoveIt.

Robot Poses define sets of joint values for particular planning groups. In this context in MoveIt poses are defined as sets of joint values.

Define two sets of joint values:
Robot 1 

Click Add Pose
Planning Group: robot1
robot1_shoulder_pan_joint: Move the slider slightly (0.4143 rad)
robot1_shoulder_lift_joint: -1.57 rad (90deg turn)
robo1_wrist_1_joint: -1.57 rad (90deg turn)
Pose Name: R1Up
Robot 2

Click Add Pose
Planning Group: robot2
robot1_shoulder_pan_joint: Move the slider slightly (0.4143 rad)
robot2_shoulder_lift_joint: -1.57 rad (90deg turn)
robot2_wrist_1_joint: -1.57 rad (90deg turn)
Pose Name: R2Up
Once we define the real controllers the motion will look much smoother.

In the unit End Effectors, we can define the set of links and joints. Also, we can let MoveIt plan our end effectors. 

For now, we leave it empty

Passive Joints specify one or multiple robot joints as passive. MoveIt will then consider these joints as not available for planning. 

Author Information is required as this generates a ROS package.

Generate Configuration Files Displays files with information about the choices we made in the previous steps so the MoveGroup node can use it. 

Specify the desired directory
$HOME/hrwros_ws/src/hrwros/hrwros_moveit_config
Generate Package
Confirm that no end effectors have been added
Let's take a quick look at the generated ROS package.
$ cd src/hrwros/hrwros_moveit_config
$ cd config
$ cd ../launch

First build and inspect the newly created configuration package:

After creating a new package we build it and source our updated setup files. 
$ cd $HOME/hrwros_ws
$ catkin build
$ source $HOME/hrwros_ws/devel/setup.bash

Navigate and look into the package.xml file.
$ roscd hrwros_moveit_config/
$ more package.xml

There you can see the author details and a set of dependencies.

Now let's see the detailed contents of the package.
Open the hrwros_moveit_config package, in an external editor, by looking at the launch files we can see how it works.

Let's begin with the  launch/move_group.launch file.

At the beginning of the file there are two group of settings related to code debugging and logging settings. These will be untouched in this course.

Then we have a few parameters:

pipeline: investigated soon
allow_trajectory_execution: investigated soon
fake_execution: investigated soon
max_safe_path_cost associated: integrating sensory information (not necessary in this course) 
jiggle_fraction: integrating sensory information (not necessary in this course) 
publish_monitored_planning_scene: a parameter used by the PlanningSceneMonitor (not necessary in this course)
Then in the Line 43 we find the planning_context.launch file, mentioned in the video.

Go to launch/planning_context.launch:
Make sure that robot_description file is available. This is usually loaded and thus the default is false.

Go to config/hrwros.srdf:
The robot_description_semantic parameter is located in the config folder and contains the following:

The semantic information (robot1_base_link, vacuum_gripper1_suction_cup...)
The robot configurations or robot poses (R1Up, R2Up)
Virtual joints
The entire list of link pairs that won't be checked for collision
Go to config/joint_limits.yaml:
Joint-specific limits for each of the robot arms are updated here.

Go to config/kinematics.yaml:
Here we have the specifications of the plugin or library we.use. 

Go back to launch/move_group.launch

The next config file mentioned in the video is the planning_pipeline.launch.xml found in line 51.
It uses the pipeline argument from the begging go the file, remember that it was set by default to ompl. 

Go to launch/ompl_planning_pipeline.launch.xml:

You will find a lot of internal settings for using the ompl planning library. 

Go to config/ompl_planning.yaml:

You will find a whole list of available planners. 

Go back to launch/move_group.launch

The next interesting file is on line 73, the trajectory_execution.launch.xml.

It uses the moveit_manage_controllers parameter, which  takes care of trajectory execution and manages controllers, and the aforementioned fake_execution parameter, although we're interested on the real one.

Go to launch/hrwros_moveit_controller_manager.launch.xml:

This unit contains a few additional steps, needed in order to work with MoveIt and the simulation factory.

        These changes are required because we are using a newer version of MoveIt.

        Important Notes:

        1. Only do this steps once, after creating a new MoveIt configuration package using the MoveIt Setup Assistant.

        2. You only need to edit two files:

        hrwros_moveit_config/launch/move_group.launch
        hrwros_moveit_config/launch/trajectory_execution.launch.xml

        1:  Remap /joint_states to /combined_joint_states
        In order to complete the MoveIt configuration, it's necessary to remap the /joint_state topic to /combined_joint_states, this allows us to handle the different robots on the simulations.

        To achieve this, follow the following steps:

        Step 1: Open the file move_group.launch in the newly generated hrwros_moveit_config/launch folder.

        Step 2: Go to line 96, just under the string <param name="disable_capabilities" value="$(arg disable_capabilities)"/>

        Step 3: Add the following string below this line:

        <remap from="/joint_states" to="/combined_joint_states"/>

        After that, Lines 95 and 96 of move_group.launch file should look like this:

        <param name="disable_capabilities" value="$(arg disable_capabilities)" />
        <remap from="/joint_states" to="/combined_joint_states"/>
        2:  Remove unneeded Planning Pipelines
        The MSA generates launch files for two additional Planning Pipelines  (CHOMP  and Pilz Industrial Motion),
        Those are not needed and can generate error messages during launch, so we can remove them,

        To achieve this, follow the following steps:

        Step 1: Open the file move_group.launch in the newly generated hrwros_moveit_config/launch folder.

        Step 2: Go to line 55, where the string <!-- CHOMP --> is found.

        Step 3: Delete or comment out lines 55 to 58, that's where the CHOMP pipeline is included.

        Step 4: Go to line 60, where the string <!-- Pilz Industrial Motion--> is found.

        Step 5: Delete or comment out lines 60 to 63, that's where the Pilz Industrial Motion pipeline is included.

        3 - Change trajectory_execution/allowed_start_tolerances
        In order to ensure the correct work of the controllers. It's also necessary to change the allowed_start_tolerances parameters.

        To achieve this, follow the following steps:

        Step 1: Open the file trajectory_execution.launch.xml in the newly generated hrwros_moveit_config/launch folder.

        Step 2: Go to line 16, find the string  <param name="trajectory_execution/allowed_start_tolerance" value="0.01"/> <!-- default 0.01 -->

        Step 3: Change the parameter value to "0.1"

        Line 14 should look like this:

        <param name="trajectory_execution/allowed_start_tolerance" value="0.1"/> <!-- default 0.01 -->

        4 - Remove  unused arguments from trajectory execution
        The trajectory_execution.launch.xml file generated contains the unused argument "execution_type" that can cause errors during launch.

        In order to ensure the correct this, you just need to delete this argument from the file.

        To achieve this, follow the following steps:

        Step 1: Open the file trajectory_execution.launch.xml in the newly generated hrwros_moveit_config/launch folder.

        Step 2: Go to line 21, find the string  <arg name="execution_type" value="$(arg execution_type)" />

        Step 3: Delete or comment out that line, to remove the argument from the include statement.

        Trajectories are executed on simulated robots or real hardware, and they are controlled by controllers.
Gazebo uses controllers to control the motion and to know the poses and status of the robot.
MoveIt plans movements and send those movements to the controllers in Gazebo.
Communication between all these  components happens over ROS topics and action servers (studied on Week 1)
Components of Gazebo and MoveIt

Gazebo uses:

JointStateController  to publish current joint values (like a sensor)
JointTrajectoryController to control the execution of trajectories sent by MoveIt
MoveIt uses:

Planning scene monitor to update position of things it know (robot arms or other objects)
Simple Controller Manager to send the desired movements to the trajectory controller.
Gazebo Simulation and MoveIt

All the gazebo configuration is contained in the hrwros_gazebo package (part of the Week 4 content files)
All MoveIt configuration is contained in the hrwros_moveit_config package (you just created it)
hrwros_gazebo

In hrwros_gazebo, all controller files live under the config folder.
Joint state controllers contain a name, a type, and a publishing frequency.
They are defined on the rX_joint_state_controller.yaml file
Trajectory controllers contain a name, a type, a list of associated joints, the gains, their constraints, and some other information to do with tolerances.
They are defined on the robotX_controller.yaml file
Important Notes:

On the robotX_controller.yaml files, the video lecture, shows position_controllers/JointTrajectoryController as the type of controllers.
On the files you will get this has changed to effort_controllers/JointTrajectoryController
Also, the gains are not shown on the video, as they are only needed for effort_controllers.
Controllers are provided as ROS action servers: They need to be powered by nodes! We can launch them using launch files.
The launchers are found on the launch folder.
The spawn_robots.launch file contains these settings for the two controllers of each robot.
hrwros_moveit_config

In hrwros_moveit_config the controller files are also under the config folder.
You need to create a new file named controllers.yaml to list all the controller clients that MoveIt is going to use.
Fill in that file with the name of the controllers including their namespace, their action namespaces, their type, and the joints they control (from the gazebo controller), the contents should look like this:

controller_list:
 - name: robot1/robot1_controller
   action_ns: follow_joint_trajectory
   type: FollowJointTrajectory
   joints: ["robot1_elbow_joint",
           "robot1_shoulder_lift_joint",
           "robot1_shoulder_pan_joint",
           "robot1_wrist_1_joint",
           "robot1_wrist_2_joint",
           "robot1_wrist_3_joint"]
 - name: robot2/robot2_controller
   action_ns: follow_joint_trajectory
   type: FollowJointTrajectory
   joints: ["robot2_elbow_joint",
           "robot2_shoulder_lift_joint",
           "robot2_shoulder_pan_joint",
           "robot2_wrist_1_joint",
           "robot2_wrist_2_joint",
           "robot2_wrist_3_joint"]

Finally, we need a launcher file for our MoveIt controller manager file, where we define a name, which controller manager system we want to use from MoveIt, and the file from the previous point where we defined the controller. So go to the launcher folder and open edit the hrwros_moveit_controller_manager.launch.xml file.
Important Note:
On the video, the hrwros_moveit_controller_manager.launch.xml appears empty, whereas on the package you just created it's already pre-filled.

All you need to do is to edit it, so it reads the controllers.yaml file you just created and not the one it has by default (ros_controllers.yaml).

The default motion planner RRTConnect sends the trajectories to be executed on the simulated robot or real hardware




















