#include "ros/ros.h"
/*
includes all the headers necessary to use
*/
#include "std_msgs/String.h"
/*
header generated automatically from the String.msg file
*/

#include <sstream>

/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
int main(int argc, char **argv)
{
  /**
   * The ros::init() function needs to see argc and argv so that it can perform
   * any ROS arguments and name remapping that were provided at the command line.
   * For programmatic remappings you can use a different version of init() which takes
   * remappings directly, but for most command-line programs, passing argc and argv is
   * the easiest way to do it.  The third argument to init() is the name of the node.
   *
   * You must call one of the versions of ros::init() before using any other
   * part of the ROS system.

   we specify the name of our node. Node names must be unique in a running system
   */
  ros::init(argc, argv, "talker");

  /**
   * NodeHandle is the main access point to communications with the ROS system.
   * The first NodeHandle constructed will fully initialize this node, and the last
   * NodeHandle destructed will close down the node.

   */
  ros::NodeHandle n;

  /**
   * The advertise() function is how you tell ROS that you want to
   * publish on a given topic name. This invokes a call to the ROS
   * master node, which keeps a registry of who is publishing and who
   * is subscribing. After this advertise() call is made, the master
   * node will notify anyone who is trying to subscribe to this topic name,
   * and they will in turn negotiate a peer-to-peer connection with this
   * node.  advertise() returns a Publisher object which allows you to
   * publish messages on that topic through a call to publish().  Once
   * all copies of the returned Publisher object are destroyed, the topic
   * will be automatically unadvertised.
   NodeHandle::advertise() returns a ros::Publisher object, which serves two purposes:
  1) it contains a publish() method that lets you publish messages onto the topic it was created with, and 
  2) when it goes out of scope, it will automatically unadvertise
   *
   * The second parameter to advertise() is the size of the message queue
   * used for publishing messages.  If messages are published more quickly
   * than we can send them, the number here specifies how many messages to
   * buffer up before throwing some away.
   */
  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);

/*
A ros::Rate object allows you to specify a frequency that you would like to loop at. It will keep track of how long it has been since the last call to Rate::sleep(), and sleep for the correct amount of time

Here we are Looping while publishing messages to chatter 10 times a second 
*/
  ros::Rate loop_rate(10);

  /**
   * A count of how many messages we have sent. This is used to create
   * a unique string for each message.
   */
  int count = 0;

  /*
 By default roscpp will install a SIGINT handler which provides Ctrl-C handling which will cause ros::ok() to return false if that happens.

ros::ok() will return false if:

    a SIGINT is received (Ctrl-C)
    we have been kicked off the network by another node with the same name

    ros::shutdown() has been called by another part of the application.

    all ros::NodeHandles have been destroyed 

Once ros::ok() returns false, all ROS calls will fail. 
*/
  while (ros::ok())
  {
    /**
     * This is a message object. You stuff it with data, and then publish it.

     We broadcast a message on ROS using a message-adapted class, generally generated from a msg file. More complicated datatypes are possible, but for now we're going to use the standard String message, which has one member: "data". 
     */
    std_msgs::String msg;

    std::stringstream ss;
    ss << "hello world " << count;
    msg.data = ss.str();

    /*
ROS_INFO our replacement for printf/cout
*/
    ROS_INFO("%s", msg.data.c_str());

    /**
     * The publish() function is how you send messages. The parameter
     * is the message object. The type of this object must agree with the type
     * given as a template parameter to the advertise<>() call, as was done
     * in the constructor above.

     Here we actually broadcast the message to anyone who is connected
      */
     chatter_pub.publish(msg);
 

    /*
    Required when receiving any callbacks. 
    When we add a subscription into this application, and did not have ros::spinOnce() here, your callbacks would never get called. So, always add it for good measure. 
*/
     ros::spinOnce();
 
     loop_rate.sleep();
     /*
ros::Rate object to sleep for the time remaining to let us hit our 10Hz publish rate. 
*/
     ++count;
   }
 
 
   return 0;
 }