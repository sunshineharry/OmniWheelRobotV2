#include "slros_busmsg_conversion.h"


// Conversions between SL_Bus_builtin_interfaces_Time and builtin_interfaces::msg::Time

void convertFromBus(builtin_interfaces::msg::Time& msgPtr, SL_Bus_builtin_interfaces_Time const* busPtr)
{
  const std::string rosMessageType("builtin_interfaces/Time");

  msgPtr.nanosec =  busPtr->nanosec;
  msgPtr.sec =  busPtr->sec;
}

void convertToBus(SL_Bus_builtin_interfaces_Time* busPtr, const builtin_interfaces::msg::Time& msgPtr)
{
  const std::string rosMessageType("builtin_interfaces/Time");

  busPtr->nanosec =  msgPtr.nanosec;
  busPtr->sec =  msgPtr.sec;
}


// Conversions between SL_Bus_geometry_msgs_Twist and geometry_msgs::msg::Twist

void convertFromBus(geometry_msgs::msg::Twist& msgPtr, SL_Bus_geometry_msgs_Twist const* busPtr)
{
  const std::string rosMessageType("geometry_msgs/Twist");

  convertFromBus(msgPtr.angular, &busPtr->angular);
  convertFromBus(msgPtr.linear, &busPtr->linear);
}

void convertToBus(SL_Bus_geometry_msgs_Twist* busPtr, const geometry_msgs::msg::Twist& msgPtr)
{
  const std::string rosMessageType("geometry_msgs/Twist");

  convertToBus(&busPtr->angular, msgPtr.angular);
  convertToBus(&busPtr->linear, msgPtr.linear);
}


// Conversions between SL_Bus_geometry_msgs_TwistWithCovariance and geometry_msgs::msg::TwistWithCovariance

void convertFromBus(geometry_msgs::msg::TwistWithCovariance& msgPtr, SL_Bus_geometry_msgs_TwistWithCovariance const* busPtr)
{
  const std::string rosMessageType("geometry_msgs/TwistWithCovariance");

  convertFromBusFixedPrimitiveArray(msgPtr.covariance, busPtr->covariance);
  convertFromBus(msgPtr.twist, &busPtr->twist);
}

void convertToBus(SL_Bus_geometry_msgs_TwistWithCovariance* busPtr, const geometry_msgs::msg::TwistWithCovariance& msgPtr)
{
  const std::string rosMessageType("geometry_msgs/TwistWithCovariance");

  convertToBusFixedPrimitiveArray(busPtr->covariance, msgPtr.covariance, slros::NoopWarning());
  convertToBus(&busPtr->twist, msgPtr.twist);
}


// Conversions between SL_Bus_geometry_msgs_TwistWithCovarianceStamped and geometry_msgs::msg::TwistWithCovarianceStamped

void convertFromBus(geometry_msgs::msg::TwistWithCovarianceStamped& msgPtr, SL_Bus_geometry_msgs_TwistWithCovarianceStamped const* busPtr)
{
  const std::string rosMessageType("geometry_msgs/TwistWithCovarianceStamped");

  convertFromBus(msgPtr.header, &busPtr->header);
  convertFromBus(msgPtr.twist, &busPtr->twist);
}

void convertToBus(SL_Bus_geometry_msgs_TwistWithCovarianceStamped* busPtr, const geometry_msgs::msg::TwistWithCovarianceStamped& msgPtr)
{
  const std::string rosMessageType("geometry_msgs/TwistWithCovarianceStamped");

  convertToBus(&busPtr->header, msgPtr.header);
  convertToBus(&busPtr->twist, msgPtr.twist);
}


// Conversions between SL_Bus_geometry_msgs_Vector3 and geometry_msgs::msg::Vector3

void convertFromBus(geometry_msgs::msg::Vector3& msgPtr, SL_Bus_geometry_msgs_Vector3 const* busPtr)
{
  const std::string rosMessageType("geometry_msgs/Vector3");

  msgPtr.x =  busPtr->x;
  msgPtr.y =  busPtr->y;
  msgPtr.z =  busPtr->z;
}

void convertToBus(SL_Bus_geometry_msgs_Vector3* busPtr, const geometry_msgs::msg::Vector3& msgPtr)
{
  const std::string rosMessageType("geometry_msgs/Vector3");

  busPtr->x =  msgPtr.x;
  busPtr->y =  msgPtr.y;
  busPtr->z =  msgPtr.z;
}


// Conversions between SL_Bus_sensor_msgs_JointState and sensor_msgs::msg::JointState

void convertFromBus(sensor_msgs::msg::JointState& msgPtr, SL_Bus_sensor_msgs_JointState const* busPtr)
{
  const std::string rosMessageType("sensor_msgs/JointState");

  convertFromBusVariablePrimitiveArray(msgPtr.effort, busPtr->effort, busPtr->effort_SL_Info);
  convertFromBus(msgPtr.header, &busPtr->header);
  convertFromBusVariableStringArray(msgPtr.name, busPtr->name, busPtr->name_SL_Info);
  convertFromBusVariablePrimitiveArray(msgPtr.position, busPtr->position, busPtr->position_SL_Info);
  convertFromBusVariablePrimitiveArray(msgPtr.velocity, busPtr->velocity, busPtr->velocity_SL_Info);
}

void convertToBus(SL_Bus_sensor_msgs_JointState* busPtr, const sensor_msgs::msg::JointState& msgPtr)
{
  const std::string rosMessageType("sensor_msgs/JointState");

  convertToBusVariablePrimitiveArray(busPtr->effort, busPtr->effort_SL_Info, msgPtr.effort, slros::EnabledWarning(rosMessageType, "effort"));
  convertToBus(&busPtr->header, msgPtr.header);
  convertToBusVariableStringArray(busPtr->name, busPtr->name_SL_Info, msgPtr.name, slros::EnabledWarning(rosMessageType, "name"));
  convertToBusVariablePrimitiveArray(busPtr->position, busPtr->position_SL_Info, msgPtr.position, slros::EnabledWarning(rosMessageType, "position"));
  convertToBusVariablePrimitiveArray(busPtr->velocity, busPtr->velocity_SL_Info, msgPtr.velocity, slros::EnabledWarning(rosMessageType, "velocity"));
}


// Conversions between SL_Bus_std_msgs_Header and std_msgs::msg::Header

void convertFromBus(std_msgs::msg::Header& msgPtr, SL_Bus_std_msgs_Header const* busPtr)
{
  const std::string rosMessageType("std_msgs/Header");

  convertFromBusVariablePrimitiveArray(msgPtr.frame_id, busPtr->frame_id, busPtr->frame_id_SL_Info);
  convertFromBus(msgPtr.stamp, &busPtr->stamp);
}

void convertToBus(SL_Bus_std_msgs_Header* busPtr, const std_msgs::msg::Header& msgPtr)
{
  const std::string rosMessageType("std_msgs/Header");

  convertToBusVariablePrimitiveArray(busPtr->frame_id, busPtr->frame_id_SL_Info, msgPtr.frame_id, slros::EnabledWarning(rosMessageType, "frame_id"));
  convertToBus(&busPtr->stamp, msgPtr.stamp);
}

