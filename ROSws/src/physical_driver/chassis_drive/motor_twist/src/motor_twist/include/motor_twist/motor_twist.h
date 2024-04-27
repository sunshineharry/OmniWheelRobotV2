/*
 * motor_twist.h
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

#ifndef RTW_HEADER_motor_twist_h_
#define RTW_HEADER_motor_twist_h_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "slros2_initialize.h"
#include "motor_twist_types.h"
#include <stddef.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block signals (default storage) */
struct B_motor_twist_T {
  SL_Bus_sensor_msgs_JointState In1;   /* '<S11>/In1' */
  SL_Bus_sensor_msgs_JointState b_varargout_2;
  SL_Bus_geometry_msgs_TwistWithCovarianceStamped BusAssignment1;/* '<Root>/Bus Assignment1' */
  real_T covariance[36];               /* '<Root>/MATLAB Function2' */
  real_T b_value[9];
  real_T v[6];
  real_T v_m[3];
  char_T b_zeroDelimTopic[22];
  char_T prmName[13];
  real_T b_value_c;
  real_T b_value_k;
  real_T SumA31;                       /* '<S8>/SumA31' */
  real_T SumA32;                       /* '<S8>/SumA32' */
  real_T SumA33;                       /* '<S8>/SumA33' */
  real_T SumA34;                       /* '<S8>/SumA34' */
  real_T SumA35;                       /* '<S8>/SumA35' */
  real_T SumB35;                       /* '<S8>/SumB35' */
  real_T SumA31_b;                     /* '<S9>/SumA31' */
  real_T SumA32_g;                     /* '<S9>/SumA32' */
  real_T SumA33_n;                     /* '<S9>/SumA33' */
  real_T SumA34_g;                     /* '<S9>/SumA34' */
  real_T SumA35_g;                     /* '<S9>/SumA35' */
  real_T SumB35_o;                     /* '<S9>/SumB35' */
  real_T SumA31_i;                     /* '<S10>/SumA31' */
  real_T SumA32_e;                     /* '<S10>/SumA32' */
  real_T SumA33_h;                     /* '<S10>/SumA33' */
  real_T SumA34_i;                     /* '<S10>/SumA34' */
  real_T SumA35_k;                     /* '<S10>/SumA35' */
  SL_Bus_builtin_interfaces_Time rtb_CurrentTime1_c;
};

/* Block states (default storage) for system '<Root>' */
struct DW_motor_twist_T {
  ros_slros2_internal_block_Cur_T obj; /* '<Root>/Current Time1' */
  ros_slros2_internal_block_Get_T obj_e;/* '<Root>/Get Parameter3' */
  ros_slros2_internal_block_Get_T obj_g;/* '<Root>/Get Parameter2' */
  ros_slros2_internal_block_Pub_T obj_p;/* '<S6>/SinkBlock' */
  ros_slros2_internal_block_Sub_T obj_py;/* '<S7>/SourceBlock' */
  real_T Delay25_DSTATE;               /* '<S8>/Delay25' */
  real_T Delay24_DSTATE;               /* '<S8>/Delay24' */
  real_T Delay23_DSTATE;               /* '<S8>/Delay23' */
  real_T Delay22_DSTATE;               /* '<S8>/Delay22' */
  real_T Delay21_DSTATE;               /* '<S8>/Delay21' */
  real_T Delay11_DSTATE;               /* '<S8>/Delay11' */
  real_T Delay12_DSTATE;               /* '<S8>/Delay12' */
  real_T Delay13_DSTATE;               /* '<S8>/Delay13' */
  real_T Delay14_DSTATE;               /* '<S8>/Delay14' */
  real_T Delay15_DSTATE;               /* '<S8>/Delay15' */
  real_T Delay25_DSTATE_f;             /* '<S9>/Delay25' */
  real_T Delay24_DSTATE_o;             /* '<S9>/Delay24' */
  real_T Delay23_DSTATE_m;             /* '<S9>/Delay23' */
  real_T Delay22_DSTATE_m;             /* '<S9>/Delay22' */
  real_T Delay21_DSTATE_k;             /* '<S9>/Delay21' */
  real_T Delay11_DSTATE_h;             /* '<S9>/Delay11' */
  real_T Delay12_DSTATE_k;             /* '<S9>/Delay12' */
  real_T Delay13_DSTATE_p;             /* '<S9>/Delay13' */
  real_T Delay14_DSTATE_n;             /* '<S9>/Delay14' */
  real_T Delay15_DSTATE_k;             /* '<S9>/Delay15' */
  real_T Delay25_DSTATE_e;             /* '<S10>/Delay25' */
  real_T Delay24_DSTATE_b;             /* '<S10>/Delay24' */
  real_T Delay23_DSTATE_b;             /* '<S10>/Delay23' */
  real_T Delay22_DSTATE_p;             /* '<S10>/Delay22' */
  real_T Delay21_DSTATE_m;             /* '<S10>/Delay21' */
  real_T Delay11_DSTATE_i;             /* '<S10>/Delay11' */
  real_T Delay12_DSTATE_l;             /* '<S10>/Delay12' */
  real_T Delay13_DSTATE_i;             /* '<S10>/Delay13' */
  real_T Delay14_DSTATE_p;             /* '<S10>/Delay14' */
  real_T Delay15_DSTATE_o;             /* '<S10>/Delay15' */
  boolean_T objisempty;                /* '<S7>/SourceBlock' */
  boolean_T objisempty_h;              /* '<S6>/SinkBlock' */
  boolean_T objisempty_k;              /* '<Root>/Get Parameter3' */
  boolean_T objisempty_d;              /* '<Root>/Get Parameter2' */
  boolean_T objisempty_c;              /* '<Root>/Current Time1' */
};

/* Parameters (default storage) */
struct P_motor_twist_T_ {
  SL_Bus_sensor_msgs_JointState Out1_Y0;/* Computed Parameter: Out1_Y0
                                         * Referenced by: '<S11>/Out1'
                                         */
  SL_Bus_sensor_msgs_JointState Constant_Value;/* Computed Parameter: Constant_Value
                                                * Referenced by: '<S7>/Constant'
                                                */
  SL_Bus_geometry_msgs_TwistWithCovarianceStamped Constant_Value_f;/* Computed Parameter: Constant_Value_f
                                                                    * Referenced by: '<S1>/Constant'
                                                                    */
  real_T Delay25_InitialCondition;     /* Expression: 0
                                        * Referenced by: '<S8>/Delay25'
                                        */
  real_T Delay24_InitialCondition;     /* Expression: 0
                                        * Referenced by: '<S8>/Delay24'
                                        */
  real_T Delay23_InitialCondition;     /* Expression: 0
                                        * Referenced by: '<S8>/Delay23'
                                        */
  real_T Delay22_InitialCondition;     /* Expression: 0
                                        * Referenced by: '<S8>/Delay22'
                                        */
  real_T Delay21_InitialCondition;     /* Expression: 0
                                        * Referenced by: '<S8>/Delay21'
                                        */
  real_T s1_Gain;                      /* Expression: 0.00600878428457218752
                                        * Referenced by: '<S8>/s(1)'
                                        */
  real_T Delay11_InitialCondition;     /* Expression: 0
                                        * Referenced by: '<S8>/Delay11'
                                        */
  real_T a21_Gain;                     /* Expression: -1.92819050100732969
                                        * Referenced by: '<S8>/a(2)(1)'
                                        */
  real_T a31_Gain;                     /* Expression: 0.952225638145618225
                                        * Referenced by: '<S8>/a(3)(1)'
                                        */
  real_T b21_Gain;                     /* Expression: 2
                                        * Referenced by: '<S8>/b(2)(1)'
                                        */
  real_T s2_Gain;                      /* Expression: 0.00574763410239304429
                                        * Referenced by: '<S8>/s(2)'
                                        */
  real_T Delay12_InitialCondition;     /* Expression: 0
                                        * Referenced by: '<S8>/Delay12'
                                        */
  real_T a22_Gain;                     /* Expression: -1.84438864080292242
                                        * Referenced by: '<S8>/a(2)(2)'
                                        */
  real_T a32_Gain;                     /* Expression: 0.867379177212494468
                                        * Referenced by: '<S8>/a(3)(2)'
                                        */
  real_T b22_Gain;                     /* Expression: 2
                                        * Referenced by: '<S8>/b(2)(2)'
                                        */
  real_T s3_Gain;                      /* Expression: 0.00554271721028068171
                                        * Referenced by: '<S8>/s(3)'
                                        */
  real_T Delay13_InitialCondition;     /* Expression: 0
                                        * Referenced by: '<S8>/Delay13'
                                        */
  real_T a23_Gain;                     /* Expression: -1.77863177782458481
                                        * Referenced by: '<S8>/a(2)(3)'
                                        */
  real_T a33_Gain;                     /* Expression: 0.800802646665707551
                                        * Referenced by: '<S8>/a(3)(3)'
                                        */
  real_T b23_Gain;                     /* Expression: 2
                                        * Referenced by: '<S8>/b(2)(3)'
                                        */
  real_T s4_Gain;                      /* Expression: 0.00540276939617958304
                                        * Referenced by: '<S8>/s(4)'
                                        */
  real_T Delay14_InitialCondition;     /* Expression: 0
                                        * Referenced by: '<S8>/Delay14'
                                        */
  real_T a24_Gain;                     /* Expression: -1.73372318516977453
                                        * Referenced by: '<S8>/a(2)(4)'
                                        */
  real_T a34_Gain;                     /* Expression: 0.75533426275449278
                                        * Referenced by: '<S8>/a(3)(4)'
                                        */
  real_T b24_Gain;                     /* Expression: 2
                                        * Referenced by: '<S8>/b(2)(4)'
                                        */
  real_T s5_Gain;                      /* Expression: 0.00533199168081265919
                                        * Referenced by: '<S8>/s(5)'
                                        */
  real_T Delay15_InitialCondition;     /* Expression: 0
                                        * Referenced by: '<S8>/Delay15'
                                        */
  real_T a25_Gain;                     /* Expression: -1.71101095054955299
                                        * Referenced by: '<S8>/a(2)(5)'
                                        */
  real_T a35_Gain;                     /* Expression: 0.732338917272803647
                                        * Referenced by: '<S8>/a(3)(5)'
                                        */
  real_T b25_Gain;                     /* Expression: 2
                                        * Referenced by: '<S8>/b(2)(5)'
                                        */
  real_T Delay25_InitialCondition_e;   /* Expression: 0
                                        * Referenced by: '<S9>/Delay25'
                                        */
  real_T Delay24_InitialCondition_a;   /* Expression: 0
                                        * Referenced by: '<S9>/Delay24'
                                        */
  real_T Delay23_InitialCondition_d;   /* Expression: 0
                                        * Referenced by: '<S9>/Delay23'
                                        */
  real_T Delay22_InitialCondition_e;   /* Expression: 0
                                        * Referenced by: '<S9>/Delay22'
                                        */
  real_T Delay21_InitialCondition_a;   /* Expression: 0
                                        * Referenced by: '<S9>/Delay21'
                                        */
  real_T s1_Gain_f;                    /* Expression: 0.00600878428457218752
                                        * Referenced by: '<S9>/s(1)'
                                        */
  real_T Delay11_InitialCondition_i;   /* Expression: 0
                                        * Referenced by: '<S9>/Delay11'
                                        */
  real_T a21_Gain_m;                   /* Expression: -1.92819050100732969
                                        * Referenced by: '<S9>/a(2)(1)'
                                        */
  real_T a31_Gain_n;                   /* Expression: 0.952225638145618225
                                        * Referenced by: '<S9>/a(3)(1)'
                                        */
  real_T b21_Gain_n;                   /* Expression: 2
                                        * Referenced by: '<S9>/b(2)(1)'
                                        */
  real_T s2_Gain_f;                    /* Expression: 0.00574763410239304429
                                        * Referenced by: '<S9>/s(2)'
                                        */
  real_T Delay12_InitialCondition_a;   /* Expression: 0
                                        * Referenced by: '<S9>/Delay12'
                                        */
  real_T a22_Gain_c;                   /* Expression: -1.84438864080292242
                                        * Referenced by: '<S9>/a(2)(2)'
                                        */
  real_T a32_Gain_c;                   /* Expression: 0.867379177212494468
                                        * Referenced by: '<S9>/a(3)(2)'
                                        */
  real_T b22_Gain_l;                   /* Expression: 2
                                        * Referenced by: '<S9>/b(2)(2)'
                                        */
  real_T s3_Gain_n;                    /* Expression: 0.00554271721028068171
                                        * Referenced by: '<S9>/s(3)'
                                        */
  real_T Delay13_InitialCondition_h;   /* Expression: 0
                                        * Referenced by: '<S9>/Delay13'
                                        */
  real_T a23_Gain_j;                   /* Expression: -1.77863177782458481
                                        * Referenced by: '<S9>/a(2)(3)'
                                        */
  real_T a33_Gain_f;                   /* Expression: 0.800802646665707551
                                        * Referenced by: '<S9>/a(3)(3)'
                                        */
  real_T b23_Gain_d;                   /* Expression: 2
                                        * Referenced by: '<S9>/b(2)(3)'
                                        */
  real_T s4_Gain_f;                    /* Expression: 0.00540276939617958304
                                        * Referenced by: '<S9>/s(4)'
                                        */
  real_T Delay14_InitialCondition_a;   /* Expression: 0
                                        * Referenced by: '<S9>/Delay14'
                                        */
  real_T a24_Gain_c;                   /* Expression: -1.73372318516977453
                                        * Referenced by: '<S9>/a(2)(4)'
                                        */
  real_T a34_Gain_g;                   /* Expression: 0.75533426275449278
                                        * Referenced by: '<S9>/a(3)(4)'
                                        */
  real_T b24_Gain_c;                   /* Expression: 2
                                        * Referenced by: '<S9>/b(2)(4)'
                                        */
  real_T s5_Gain_i;                    /* Expression: 0.00533199168081265919
                                        * Referenced by: '<S9>/s(5)'
                                        */
  real_T Delay15_InitialCondition_g;   /* Expression: 0
                                        * Referenced by: '<S9>/Delay15'
                                        */
  real_T a25_Gain_h;                   /* Expression: -1.71101095054955299
                                        * Referenced by: '<S9>/a(2)(5)'
                                        */
  real_T a35_Gain_n;                   /* Expression: 0.732338917272803647
                                        * Referenced by: '<S9>/a(3)(5)'
                                        */
  real_T b25_Gain_d;                   /* Expression: 2
                                        * Referenced by: '<S9>/b(2)(5)'
                                        */
  real_T Delay25_InitialCondition_eg;  /* Expression: 0
                                        * Referenced by: '<S10>/Delay25'
                                        */
  real_T Delay24_InitialCondition_l;   /* Expression: 0
                                        * Referenced by: '<S10>/Delay24'
                                        */
  real_T Delay23_InitialCondition_m;   /* Expression: 0
                                        * Referenced by: '<S10>/Delay23'
                                        */
  real_T Delay22_InitialCondition_d;   /* Expression: 0
                                        * Referenced by: '<S10>/Delay22'
                                        */
  real_T Delay21_InitialCondition_ao;  /* Expression: 0
                                        * Referenced by: '<S10>/Delay21'
                                        */
  real_T s1_Gain_l;                    /* Expression: 0.00600878428457218752
                                        * Referenced by: '<S10>/s(1)'
                                        */
  real_T Delay11_InitialCondition_o;   /* Expression: 0
                                        * Referenced by: '<S10>/Delay11'
                                        */
  real_T a21_Gain_o;                   /* Expression: -1.92819050100732969
                                        * Referenced by: '<S10>/a(2)(1)'
                                        */
  real_T a31_Gain_o;                   /* Expression: 0.952225638145618225
                                        * Referenced by: '<S10>/a(3)(1)'
                                        */
  real_T b21_Gain_f;                   /* Expression: 2
                                        * Referenced by: '<S10>/b(2)(1)'
                                        */
  real_T s2_Gain_d;                    /* Expression: 0.00574763410239304429
                                        * Referenced by: '<S10>/s(2)'
                                        */
  real_T Delay12_InitialCondition_j;   /* Expression: 0
                                        * Referenced by: '<S10>/Delay12'
                                        */
  real_T a22_Gain_b;                   /* Expression: -1.84438864080292242
                                        * Referenced by: '<S10>/a(2)(2)'
                                        */
  real_T a32_Gain_p;                   /* Expression: 0.867379177212494468
                                        * Referenced by: '<S10>/a(3)(2)'
                                        */
  real_T b22_Gain_f;                   /* Expression: 2
                                        * Referenced by: '<S10>/b(2)(2)'
                                        */
  real_T s3_Gain_nz;                   /* Expression: 0.00554271721028068171
                                        * Referenced by: '<S10>/s(3)'
                                        */
  real_T Delay13_InitialCondition_m;   /* Expression: 0
                                        * Referenced by: '<S10>/Delay13'
                                        */
  real_T a23_Gain_l;                   /* Expression: -1.77863177782458481
                                        * Referenced by: '<S10>/a(2)(3)'
                                        */
  real_T a33_Gain_m;                   /* Expression: 0.800802646665707551
                                        * Referenced by: '<S10>/a(3)(3)'
                                        */
  real_T b23_Gain_l;                   /* Expression: 2
                                        * Referenced by: '<S10>/b(2)(3)'
                                        */
  real_T s4_Gain_g;                    /* Expression: 0.00540276939617958304
                                        * Referenced by: '<S10>/s(4)'
                                        */
  real_T Delay14_InitialCondition_g;   /* Expression: 0
                                        * Referenced by: '<S10>/Delay14'
                                        */
  real_T a24_Gain_f;                   /* Expression: -1.73372318516977453
                                        * Referenced by: '<S10>/a(2)(4)'
                                        */
  real_T a34_Gain_f;                   /* Expression: 0.75533426275449278
                                        * Referenced by: '<S10>/a(3)(4)'
                                        */
  real_T b24_Gain_e;                   /* Expression: 2
                                        * Referenced by: '<S10>/b(2)(4)'
                                        */
  real_T s5_Gain_k;                    /* Expression: 0.00533199168081265919
                                        * Referenced by: '<S10>/s(5)'
                                        */
  real_T Delay15_InitialCondition_l;   /* Expression: 0
                                        * Referenced by: '<S10>/Delay15'
                                        */
  real_T a25_Gain_h3;                  /* Expression: -1.71101095054955299
                                        * Referenced by: '<S10>/a(2)(5)'
                                        */
  real_T a35_Gain_b;                   /* Expression: 0.732338917272803647
                                        * Referenced by: '<S10>/a(3)(5)'
                                        */
  real_T b25_Gain_b;                   /* Expression: 2
                                        * Referenced by: '<S10>/b(2)(5)'
                                        */
  real_T SimulationPace_P1;            /* Expression: SimulationPace
                                        * Referenced by: '<Root>/Simulation Pace'
                                        */
  real_T SimulationPace_P2;            /* Expression: 2
                                        * Referenced by: '<Root>/Simulation Pace'
                                        */
  real_T SimulationPace_P3;            /* Expression: OutputPaceError
                                        * Referenced by: '<Root>/Simulation Pace'
                                        */
  real_T SimulationPace_P4;            /* Expression: SampleTime
                                        * Referenced by: '<Root>/Simulation Pace'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_motor_twist_T {
  const char_T *errorStatus;
};

/* Class declaration for model motor_twist */
class motor_twist
{
  /* public data and function members */
 public:
  /* Real-Time Model get method */
  RT_MODEL_motor_twist_T * getRTM();

  /* model start function */
  void start();

  /* Initial conditions function */
  void initialize();

  /* model step function */
  void step();

  /* model terminate function */
  void terminate();

  /* Constructor */
  motor_twist();

  /* Destructor */
  ~motor_twist();

  /* private data and function members */
 private:
  /* Block signals */
  B_motor_twist_T motor_twist_B;

  /* Block states */
  DW_motor_twist_T motor_twist_DW;

  /* Tunable parameters */
  static P_motor_twist_T motor_twist_P;

  /* private member function(s) for subsystem '<Root>'*/
  void motor_twist_SystemCore_setup_j(ros_slros2_internal_block_Sub_T *obj);
  void motor_twist_SystemCore_setup(ros_slros2_internal_block_Pub_T *obj);

  /* Real-Time Model */
  RT_MODEL_motor_twist_T motor_twist_M;
};

extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'motor_twist'
 * '<S1>'   : 'motor_twist/Blank Message'
 * '<S2>'   : 'motor_twist/MATLAB Function'
 * '<S3>'   : 'motor_twist/MATLAB Function1'
 * '<S4>'   : 'motor_twist/MATLAB Function2'
 * '<S5>'   : 'motor_twist/MATLAB Function3'
 * '<S6>'   : 'motor_twist/Publish1'
 * '<S7>'   : 'motor_twist/Subscribe1'
 * '<S8>'   : 'motor_twist/wheel_vel_filter'
 * '<S9>'   : 'motor_twist/wheel_vel_filter1'
 * '<S10>'  : 'motor_twist/wheel_vel_filter2'
 * '<S11>'  : 'motor_twist/Subscribe1/Enabled Subsystem'
 */
#endif                                 /* RTW_HEADER_motor_twist_h_ */
