/*
 * motor_twist_types.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "motor_twist".
 *
 * Model version              : 1.33
 * Simulink Coder version : 23.2 (R2023b) 01-Aug-2023
 * C++ source code generated on : Sat Apr 13 12:33:41 2024
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_motor_twist_types_h_
#define RTW_HEADER_motor_twist_types_h_
#include "rtwtypes.h"
#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_builtin_interfaces_Time_
#define DEFINED_TYPEDEF_FOR_SL_Bus_builtin_interfaces_Time_

struct SL_Bus_builtin_interfaces_Time
{
  int32_T sec;
  uint32_T nanosec;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_ROSVariableLengthArrayInfo_
#define DEFINED_TYPEDEF_FOR_SL_Bus_ROSVariableLengthArrayInfo_

struct SL_Bus_ROSVariableLengthArrayInfo
{
  uint32_T CurrentLength;
  uint32_T ReceivedLength;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_std_msgs_Header_
#define DEFINED_TYPEDEF_FOR_SL_Bus_std_msgs_Header_

struct SL_Bus_std_msgs_Header
{
  SL_Bus_builtin_interfaces_Time stamp;
  uint8_T frame_id[128];
  SL_Bus_ROSVariableLengthArrayInfo frame_id_SL_Info;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_geometry_msgs_Vector3_
#define DEFINED_TYPEDEF_FOR_SL_Bus_geometry_msgs_Vector3_

struct SL_Bus_geometry_msgs_Vector3
{
  real_T x;
  real_T y;
  real_T z;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_geometry_msgs_Twist_
#define DEFINED_TYPEDEF_FOR_SL_Bus_geometry_msgs_Twist_

struct SL_Bus_geometry_msgs_Twist
{
  SL_Bus_geometry_msgs_Vector3 linear;
  SL_Bus_geometry_msgs_Vector3 angular;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_geometry_msgs_TwistWithCovariance_
#define DEFINED_TYPEDEF_FOR_SL_Bus_geometry_msgs_TwistWithCovariance_

struct SL_Bus_geometry_msgs_TwistWithCovariance
{
  SL_Bus_geometry_msgs_Twist twist;
  real_T covariance[36];
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_geometry_msgs_TwistWithCovarianceStamped_
#define DEFINED_TYPEDEF_FOR_SL_Bus_geometry_msgs_TwistWithCovarianceStamped_

struct SL_Bus_geometry_msgs_TwistWithCovarianceStamped
{
  SL_Bus_std_msgs_Header header;
  SL_Bus_geometry_msgs_TwistWithCovariance twist;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_std_msgs_String_
#define DEFINED_TYPEDEF_FOR_SL_Bus_std_msgs_String_

struct SL_Bus_std_msgs_String
{
  uint8_T data[128];
  SL_Bus_ROSVariableLengthArrayInfo data_SL_Info;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_sensor_msgs_JointState_
#define DEFINED_TYPEDEF_FOR_SL_Bus_sensor_msgs_JointState_

struct SL_Bus_sensor_msgs_JointState
{
  SL_Bus_std_msgs_Header header;
  SL_Bus_std_msgs_String name[16];
  SL_Bus_ROSVariableLengthArrayInfo name_SL_Info;
  real_T position[128];
  SL_Bus_ROSVariableLengthArrayInfo position_SL_Info;
  real_T velocity[128];
  SL_Bus_ROSVariableLengthArrayInfo velocity_SL_Info;
  real_T effort[128];
  SL_Bus_ROSVariableLengthArrayInfo effort_SL_Info;
};

#endif

#ifndef struct_f_robotics_slcore_internal_bl_T
#define struct_f_robotics_slcore_internal_bl_T

struct f_robotics_slcore_internal_bl_T
{
  int32_T __dummy;
};

#endif                              /* struct_f_robotics_slcore_internal_bl_T */

#ifndef struct_ros_slros2_internal_block_Cur_T
#define struct_ros_slros2_internal_block_Cur_T

struct ros_slros2_internal_block_Cur_T
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  f_robotics_slcore_internal_bl_T SampleTimeHandler;
};

#endif                              /* struct_ros_slros2_internal_block_Cur_T */

#ifndef struct_ros_slros2_internal_block_Get_T
#define struct_ros_slros2_internal_block_Get_T

struct ros_slros2_internal_block_Get_T
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  f_robotics_slcore_internal_bl_T SampleTimeHandler;
};

#endif                              /* struct_ros_slros2_internal_block_Get_T */

/* Custom Type definition for MATLABSystem: '<S7>/SourceBlock' */
#include "rmw/qos_profiles.h"
#include "rmw/types.h"
#include "rmw/types.h"
#include "rmw/types.h"
#ifndef struct_ros_slros2_internal_block_Pub_T
#define struct_ros_slros2_internal_block_Pub_T

struct ros_slros2_internal_block_Pub_T
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
};

#endif                              /* struct_ros_slros2_internal_block_Pub_T */

#ifndef struct_ros_slros2_internal_block_Sub_T
#define struct_ros_slros2_internal_block_Sub_T

struct ros_slros2_internal_block_Sub_T
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
};

#endif                              /* struct_ros_slros2_internal_block_Sub_T */

/* Parameters (default storage) */
typedef struct P_motor_twist_T_ P_motor_twist_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_motor_twist_T RT_MODEL_motor_twist_T;

#endif                                 /* RTW_HEADER_motor_twist_types_h_ */
