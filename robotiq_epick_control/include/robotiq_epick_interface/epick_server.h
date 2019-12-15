#pragma once
#include <string>

// Custom Callback Queue
#include <ros/callback_queue.h>
#include <ros/advertise_options.h>
#include <ros/advertise_service_options.h>
#include <std_srvs/Empty.h>

#include <ros/ros.h>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>

#include "robotiq_epick_interface/epick_gripper_interface.h"


namespace epick_interface
{

  class EpickServer
  {
  public: EpickServer(ros::NodeHandle& nh);

  public: virtual ~EpickServer();

  public: void Publish();
  private: void initialize();

  public: void QueueThread();

  private: bool OnServiceCallback(std_srvs::Empty::Request &req,
                                  std_srvs::Empty::Response &res);
  private: bool OffServiceCallback(std_srvs::Empty::Request &req,
                                   std_srvs::Empty::Response &res);

  private: bool status_;

  private: ros::NodeHandle& nh_;
  private: EpickGripper gripper_;

  private: boost::mutex lock_;
  private: ros::Publisher pub_;

  private: ros::ServiceServer srv1_; // gripper on srv
  private: ros::ServiceServer srv2_; // gripper off srv

  private: std::string pub_topic_name_;
  private: std::string srv1_topic_name_;
  private: std::string srv2_topic_name_;


  // Custom Callback Queue
  private: ros::CallbackQueue queue_;
  private: boost::thread callback_queue_thread_;

  private: int connect_count_;
  private: void Connect();
  private: void Disconnect();
  };
}