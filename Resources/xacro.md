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
   1   <link name="base_link">
   2     <visual>
   3       <geometry>
   4         <cylinder length="0.6" radius="0.2"/>
   5       </geometry>
   6       <material name="blue"/>
   7     </visual>
   8     <collision>
   9       <geometry>
  10         <cylinder length="0.6" radius="0.2"/>
  11       </geometry>
  12     </collision>
  13   </link>