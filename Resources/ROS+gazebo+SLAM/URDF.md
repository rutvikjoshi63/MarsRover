we’re going to focus on getting the visual geometry correct
make sure you have the joint_state_publisher package installed
installed urdf_tutorial using apt-get

http://wiki.ros.org/urdf/Tutorials/Building%20a%20Visual%20Robot%20Model%20with%20URDF%20from%20Scratch

http://wiki.ros.org/urdf/Tutorials/Building%20a%20Movable%20Robot%20Model%20with%20URDF

   1 <?xml version="1.0"?>
   2 <robot name="origins">
   3   <link name="base_link">
   4     <visual>
   5       <geometry>
   6         <cylinder length="0.6" radius="0.2"/>
   7       </geometry>
   8     </visual>
   9   </link>
  10 
  11   <link name="right_leg">
  12     <visual>
  13       <geometry>
  14         <box size="0.6 0.1 0.2"/>
  15       </geometry>
  16       <origin rpy="0 1.57075 0" xyz="0 0 -0.3"/>
  17     </visual>
  18   </link>
  19 
  20   <joint name="base_to_right_leg" type="fixed">
  21     <parent link="base_link"/>
  22     <child link="right_leg"/>
  23     <origin xyz="0 -0.22 0.25"/>
  24   </joint>
  25 
  26 </robot>
  ![Alt text](images/image.png)

roslaunch urdf_tutorial display.launch model:=urdf/01-myfirst.urdf

check_urdf robot.urdf
This tool only checks the syntax though, so it checks whether we've only used legal combinations of recognized URDF keywords in our files. It cannot check whether you've correctly specified the mass of your robot links, whether the model that we've created makes sense or whether the colors that you've used correspond to what the manufacturer has used.

XACRO
xacro is a macro language for XML. The xacro program runs all of the macros and outputs the result.

At the top of the URDF file, you must specify a namespace in order for the file to parse properly
   1 <?xml version="1.0"?>
   2 <robot xmlns:xacro="http://www.ros.org/wiki/xacro" name="firefighter">

for defining materials
   4   <material name="blue">
   5     <color rgba="0 0 0.8 1"/>
   6   </material>
   7 
   8   <material name="white">
   9     <color rgba="1 1 1 1"/>
  10   </material>

  http://wiki.ros.org/urdf/Tutorials/Adding%20Physical%20and%20Collision%20Properties%20to%20a%20URDF%20Model

   1 <xacro:property name="width" value="0.2" />
   2 <xacro:property name="bodylen" value="0.6" />
   3 <link name="base_link">
   4     <visual>
   5         <geometry>
   6             <cylinder radius="${width}" length="${bodylen}"/>
   7         </geometry>
   8         <material name="blue"/>
   9     </visual>
  10     <collision>
  11         <geometry>
  12             <cylinder radius="${width}" length="${bodylen}"/>
  13         </geometry>
  14     </collision>
  15 </link>
  The value of the contents of the ${} construct are then used to replace the ${}.
     1 <xacro:property name=”robotname” value=”marvin” />
   2 <link name=”${robotname}s_leg” />

Common Trick 1: Use a name prefix to get two similarly named objects.
Common Trick 2: Use math to calculate joint origins. In the case that you change the size of your robot, changing a property with some math to calculate the joint offset will save a lot of trouble.
Common Trick 3: Using a reflect parameter, and setting it to 1 or -1. See how we use the reflect parameter to put the legs on either side of the body in the base_to_${prefix}_leg origin.


So we first convert the XACRO file to URDF (this will generate the URDF file in the current working directory):

  rosrun xacro xacro /path/to/robot.xacro > robot.urdf

  or
  roscd to the path, then
  rosrun xacro xacro --inorder hrwros.xacro > hrwros.urdf

And then run check_urdf on that file:

  check_urdf robot.urd
  fThis tool only checks the syntax though, so it checks whether we've only used legal combinations of recognized URDF keywords in our files. It cannot check whether you've correctly specified the mass of your robot links, whether the model that we've created makes sense or whether the colors that you've used correspond to what the manufacturer has used.