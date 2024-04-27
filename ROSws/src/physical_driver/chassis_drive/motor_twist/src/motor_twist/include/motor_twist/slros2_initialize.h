// Copyright 2022-2023 The MathWorks, Inc.
// Generated 13-Apr-2024 12:33:46
#ifndef _SLROS2_INITIALIZE_H_
#define _SLROS2_INITIALIZE_H_
#include "motor_twist_types.h"
// Generic pub-sub header
#include "slros2_generic_pubsub.h"
// Generic service header
#include "slros2_generic_service.h"
#include "slros2_time.h"
#include "slros2_generic_param.h"
extern rclcpp::Node::SharedPtr SLROSNodePtr;
#ifndef SET_QOS_VALUES
#define SET_QOS_VALUES(qosStruct, hist, dep, dur, rel)  \
    {                                                   \
        qosStruct.history = hist;                       \
        qosStruct.depth = dep;                          \
        qosStruct.durability = dur;                     \
        qosStruct.reliability = rel;                    \
    }
#endif
inline rclcpp::QoS getQOSSettingsFromRMW(const rmw_qos_profile_t& qosProfile) {
    rclcpp::QoS qos(rclcpp::QoSInitialization::from_rmw(qosProfile));
    if (RMW_QOS_POLICY_DURABILITY_TRANSIENT_LOCAL == qosProfile.durability) {
        qos.transient_local();
    } else {
        qos.durability_volatile();
    }
    if (RMW_QOS_POLICY_RELIABILITY_RELIABLE == qosProfile.reliability) {
        qos.reliable();
    } else {
        qos.best_effort();
    }
    return qos;
}
// motor_twist/Publish1
extern SimulinkPublisher<geometry_msgs::msg::TwistWithCovarianceStamped,SL_Bus_geometry_msgs_TwistWithCovarianceStamped> Pub_motor_twist_411;
// motor_twist/Subscribe1
extern SimulinkSubscriber<sensor_msgs::msg::JointState,SL_Bus_sensor_msgs_JointState> Sub_motor_twist_406;
// For Block motor_twist/Get Parameter2
extern SimulinkParameterGetter<real64_T,double> ParamGet_motor_twist_407;
// For Block motor_twist/Get Parameter3
extern SimulinkParameterGetter<real64_T,double> ParamGet_motor_twist_408;
#endif
