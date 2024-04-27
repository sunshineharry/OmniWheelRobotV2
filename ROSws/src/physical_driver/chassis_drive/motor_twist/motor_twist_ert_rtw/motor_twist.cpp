/*
 * motor_twist.cpp
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

#include "motor_twist.h"
#include "motor_twist_types.h"
#include "rtwtypes.h"
#include <math.h>
#include <string.h>
#include <emmintrin.h>
#include "rmw/qos_profiles.h"
#include "rmw/types.h"
#include <stddef.h>

void motor_twist::motor_twist_SystemCore_setup_j(ros_slros2_internal_block_Sub_T
  *obj)
{
  rmw_qos_durability_policy_t durability;
  rmw_qos_history_policy_t history;
  rmw_qos_profile_t qos_profile;
  rmw_qos_reliability_policy_t reliability;
  char_T b_zeroDelimTopic[14];
  static const char_T tmp[13] = { '/', 'm', 'o', 't', 'o', 'r', '/', 's', 't',
    'a', 't', 'e', 's' };

  obj->isInitialized = 1;
  qos_profile = rmw_qos_profile_default;
  history = RMW_QOS_POLICY_HISTORY_KEEP_LAST;
  reliability = RMW_QOS_POLICY_RELIABILITY_RELIABLE;
  durability = RMW_QOS_POLICY_DURABILITY_VOLATILE;
  SET_QOS_VALUES(qos_profile, history, (size_t)1.0, durability, reliability);
  for (int32_T i = 0; i < 13; i++) {
    b_zeroDelimTopic[i] = tmp[i];
  }

  b_zeroDelimTopic[13] = '\x00';
  Sub_motor_twist_406.createSubscriber(&b_zeroDelimTopic[0], qos_profile);
  obj->isSetupComplete = true;
}

void motor_twist::motor_twist_SystemCore_setup(ros_slros2_internal_block_Pub_T
  *obj)
{
  rmw_qos_durability_policy_t durability;
  rmw_qos_history_policy_t history;
  rmw_qos_profile_t qos_profile;
  rmw_qos_reliability_policy_t reliability;
  static const char_T tmp[21] = { '/', 'm', 'o', 't', 'o', 'r', '/', 'b', 'a',
    's', 'e', 'l', 'i', 'n', 'k', '/', 't', 'w', 'i', 's', 't' };

  obj->isInitialized = 1;
  qos_profile = rmw_qos_profile_default;
  history = RMW_QOS_POLICY_HISTORY_KEEP_LAST;
  reliability = RMW_QOS_POLICY_RELIABILITY_RELIABLE;
  durability = RMW_QOS_POLICY_DURABILITY_VOLATILE;
  SET_QOS_VALUES(qos_profile, history, (size_t)1.0, durability, reliability);
  for (int32_T i = 0; i < 21; i++) {
    motor_twist_B.b_zeroDelimTopic[i] = tmp[i];
  }

  motor_twist_B.b_zeroDelimTopic[21] = '\x00';
  Pub_motor_twist_411.createPublisher(&motor_twist_B.b_zeroDelimTopic[0],
    qos_profile);
  obj->isSetupComplete = true;
}

/* Model step function */
void motor_twist::step()
{
  __m128d tmp;
  __m128d tmp_0;
  __m128d tmp_1;
  real_T rtb_SumB35_p;
  int32_T i;
  boolean_T b_varargout_1;

  /* MATLABSystem: '<S7>/SourceBlock' */
  b_varargout_1 = Sub_motor_twist_406.getLatestMessage
    (&motor_twist_B.b_varargout_2);

  /* Outputs for Enabled SubSystem: '<S7>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S11>/Enable'
   */
  if (b_varargout_1) {
    /* SignalConversion generated from: '<S11>/In1' */
    motor_twist_B.In1 = motor_twist_B.b_varargout_2;
  }

  /* End of MATLABSystem: '<S7>/SourceBlock' */
  /* End of Outputs for SubSystem: '<S7>/Enabled Subsystem' */

  /* Sum: '<S8>/SumA31' incorporates:
   *  Delay: '<S8>/Delay11'
   *  Delay: '<S8>/Delay21'
   *  Gain: '<S8>/a(2)(1)'
   *  Gain: '<S8>/a(3)(1)'
   *  Gain: '<S8>/s(1)'
   *  MATLAB Function: '<Root>/MATLAB Function'
   *  Sum: '<S8>/SumA21'
   */
  motor_twist_B.SumA31 = (motor_twist_P.s1_Gain * motor_twist_B.In1.velocity[0]
    - motor_twist_P.a21_Gain * motor_twist_DW.Delay11_DSTATE) -
    motor_twist_P.a31_Gain * motor_twist_DW.Delay21_DSTATE;

  /* Sum: '<S8>/SumA32' incorporates:
   *  Delay: '<S8>/Delay11'
   *  Delay: '<S8>/Delay12'
   *  Delay: '<S8>/Delay21'
   *  Delay: '<S8>/Delay22'
   *  Gain: '<S8>/a(2)(2)'
   *  Gain: '<S8>/a(3)(2)'
   *  Gain: '<S8>/b(2)(1)'
   *  Gain: '<S8>/s(2)'
   *  Sum: '<S8>/SumA22'
   *  Sum: '<S8>/SumB21'
   *  Sum: '<S8>/SumB31'
   */
  motor_twist_B.SumA32 = (((motor_twist_P.b21_Gain *
    motor_twist_DW.Delay11_DSTATE + motor_twist_B.SumA31) +
    motor_twist_DW.Delay21_DSTATE) * motor_twist_P.s2_Gain -
    motor_twist_P.a22_Gain * motor_twist_DW.Delay12_DSTATE) -
    motor_twist_P.a32_Gain * motor_twist_DW.Delay22_DSTATE;

  /* Sum: '<S8>/SumA33' incorporates:
   *  Delay: '<S8>/Delay12'
   *  Delay: '<S8>/Delay13'
   *  Delay: '<S8>/Delay22'
   *  Delay: '<S8>/Delay23'
   *  Gain: '<S8>/a(2)(3)'
   *  Gain: '<S8>/a(3)(3)'
   *  Gain: '<S8>/b(2)(2)'
   *  Gain: '<S8>/s(3)'
   *  Sum: '<S8>/SumA23'
   *  Sum: '<S8>/SumB22'
   *  Sum: '<S8>/SumB32'
   */
  motor_twist_B.SumA33 = (((motor_twist_P.b22_Gain *
    motor_twist_DW.Delay12_DSTATE + motor_twist_B.SumA32) +
    motor_twist_DW.Delay22_DSTATE) * motor_twist_P.s3_Gain -
    motor_twist_P.a23_Gain * motor_twist_DW.Delay13_DSTATE) -
    motor_twist_P.a33_Gain * motor_twist_DW.Delay23_DSTATE;

  /* Sum: '<S8>/SumA34' incorporates:
   *  Delay: '<S8>/Delay13'
   *  Delay: '<S8>/Delay14'
   *  Delay: '<S8>/Delay23'
   *  Delay: '<S8>/Delay24'
   *  Gain: '<S8>/a(2)(4)'
   *  Gain: '<S8>/a(3)(4)'
   *  Gain: '<S8>/b(2)(3)'
   *  Gain: '<S8>/s(4)'
   *  Sum: '<S8>/SumA24'
   *  Sum: '<S8>/SumB23'
   *  Sum: '<S8>/SumB33'
   */
  motor_twist_B.SumA34 = (((motor_twist_P.b23_Gain *
    motor_twist_DW.Delay13_DSTATE + motor_twist_B.SumA33) +
    motor_twist_DW.Delay23_DSTATE) * motor_twist_P.s4_Gain -
    motor_twist_P.a24_Gain * motor_twist_DW.Delay14_DSTATE) -
    motor_twist_P.a34_Gain * motor_twist_DW.Delay24_DSTATE;

  /* Sum: '<S8>/SumA35' incorporates:
   *  Delay: '<S8>/Delay14'
   *  Delay: '<S8>/Delay15'
   *  Delay: '<S8>/Delay24'
   *  Delay: '<S8>/Delay25'
   *  Gain: '<S8>/a(2)(5)'
   *  Gain: '<S8>/a(3)(5)'
   *  Gain: '<S8>/b(2)(4)'
   *  Gain: '<S8>/s(5)'
   *  Sum: '<S8>/SumA25'
   *  Sum: '<S8>/SumB24'
   *  Sum: '<S8>/SumB34'
   */
  motor_twist_B.SumA35 = (((motor_twist_P.b24_Gain *
    motor_twist_DW.Delay14_DSTATE + motor_twist_B.SumA34) +
    motor_twist_DW.Delay24_DSTATE) * motor_twist_P.s5_Gain -
    motor_twist_P.a25_Gain * motor_twist_DW.Delay15_DSTATE) -
    motor_twist_P.a35_Gain * motor_twist_DW.Delay25_DSTATE;

  /* Sum: '<S8>/SumB35' incorporates:
   *  Delay: '<S8>/Delay15'
   *  Delay: '<S8>/Delay25'
   *  Gain: '<S8>/b(2)(5)'
   *  Sum: '<S8>/SumB25'
   */
  motor_twist_B.SumB35 = (motor_twist_P.b25_Gain * motor_twist_DW.Delay15_DSTATE
    + motor_twist_B.SumA35) + motor_twist_DW.Delay25_DSTATE;

  /* Sum: '<S9>/SumA31' incorporates:
   *  Delay: '<S9>/Delay11'
   *  Delay: '<S9>/Delay21'
   *  Gain: '<S9>/a(2)(1)'
   *  Gain: '<S9>/a(3)(1)'
   *  Gain: '<S9>/s(1)'
   *  MATLAB Function: '<Root>/MATLAB Function'
   *  Sum: '<S9>/SumA21'
   */
  motor_twist_B.SumA31_b = (motor_twist_P.s1_Gain_f *
    motor_twist_B.In1.velocity[1] - motor_twist_P.a21_Gain_m *
    motor_twist_DW.Delay11_DSTATE_h) - motor_twist_P.a31_Gain_n *
    motor_twist_DW.Delay21_DSTATE_k;

  /* Sum: '<S9>/SumA32' incorporates:
   *  Delay: '<S9>/Delay11'
   *  Delay: '<S9>/Delay12'
   *  Delay: '<S9>/Delay21'
   *  Delay: '<S9>/Delay22'
   *  Gain: '<S9>/a(2)(2)'
   *  Gain: '<S9>/a(3)(2)'
   *  Gain: '<S9>/b(2)(1)'
   *  Gain: '<S9>/s(2)'
   *  Sum: '<S9>/SumA22'
   *  Sum: '<S9>/SumB21'
   *  Sum: '<S9>/SumB31'
   */
  motor_twist_B.SumA32_g = (((motor_twist_P.b21_Gain_n *
    motor_twist_DW.Delay11_DSTATE_h + motor_twist_B.SumA31_b) +
    motor_twist_DW.Delay21_DSTATE_k) * motor_twist_P.s2_Gain_f -
    motor_twist_P.a22_Gain_c * motor_twist_DW.Delay12_DSTATE_k) -
    motor_twist_P.a32_Gain_c * motor_twist_DW.Delay22_DSTATE_m;

  /* Sum: '<S9>/SumA33' incorporates:
   *  Delay: '<S9>/Delay12'
   *  Delay: '<S9>/Delay13'
   *  Delay: '<S9>/Delay22'
   *  Delay: '<S9>/Delay23'
   *  Gain: '<S9>/a(2)(3)'
   *  Gain: '<S9>/a(3)(3)'
   *  Gain: '<S9>/b(2)(2)'
   *  Gain: '<S9>/s(3)'
   *  Sum: '<S9>/SumA23'
   *  Sum: '<S9>/SumB22'
   *  Sum: '<S9>/SumB32'
   */
  motor_twist_B.SumA33_n = (((motor_twist_P.b22_Gain_l *
    motor_twist_DW.Delay12_DSTATE_k + motor_twist_B.SumA32_g) +
    motor_twist_DW.Delay22_DSTATE_m) * motor_twist_P.s3_Gain_n -
    motor_twist_P.a23_Gain_j * motor_twist_DW.Delay13_DSTATE_p) -
    motor_twist_P.a33_Gain_f * motor_twist_DW.Delay23_DSTATE_m;

  /* Sum: '<S9>/SumA34' incorporates:
   *  Delay: '<S9>/Delay13'
   *  Delay: '<S9>/Delay14'
   *  Delay: '<S9>/Delay23'
   *  Delay: '<S9>/Delay24'
   *  Gain: '<S9>/a(2)(4)'
   *  Gain: '<S9>/a(3)(4)'
   *  Gain: '<S9>/b(2)(3)'
   *  Gain: '<S9>/s(4)'
   *  Sum: '<S9>/SumA24'
   *  Sum: '<S9>/SumB23'
   *  Sum: '<S9>/SumB33'
   */
  motor_twist_B.SumA34_g = (((motor_twist_P.b23_Gain_d *
    motor_twist_DW.Delay13_DSTATE_p + motor_twist_B.SumA33_n) +
    motor_twist_DW.Delay23_DSTATE_m) * motor_twist_P.s4_Gain_f -
    motor_twist_P.a24_Gain_c * motor_twist_DW.Delay14_DSTATE_n) -
    motor_twist_P.a34_Gain_g * motor_twist_DW.Delay24_DSTATE_o;

  /* Sum: '<S9>/SumA35' incorporates:
   *  Delay: '<S9>/Delay14'
   *  Delay: '<S9>/Delay15'
   *  Delay: '<S9>/Delay24'
   *  Delay: '<S9>/Delay25'
   *  Gain: '<S9>/a(2)(5)'
   *  Gain: '<S9>/a(3)(5)'
   *  Gain: '<S9>/b(2)(4)'
   *  Gain: '<S9>/s(5)'
   *  Sum: '<S9>/SumA25'
   *  Sum: '<S9>/SumB24'
   *  Sum: '<S9>/SumB34'
   */
  motor_twist_B.SumA35_g = (((motor_twist_P.b24_Gain_c *
    motor_twist_DW.Delay14_DSTATE_n + motor_twist_B.SumA34_g) +
    motor_twist_DW.Delay24_DSTATE_o) * motor_twist_P.s5_Gain_i -
    motor_twist_P.a25_Gain_h * motor_twist_DW.Delay15_DSTATE_k) -
    motor_twist_P.a35_Gain_n * motor_twist_DW.Delay25_DSTATE_f;

  /* Sum: '<S9>/SumB35' incorporates:
   *  Delay: '<S9>/Delay15'
   *  Delay: '<S9>/Delay25'
   *  Gain: '<S9>/b(2)(5)'
   *  Sum: '<S9>/SumB25'
   */
  motor_twist_B.SumB35_o = (motor_twist_P.b25_Gain_d *
    motor_twist_DW.Delay15_DSTATE_k + motor_twist_B.SumA35_g) +
    motor_twist_DW.Delay25_DSTATE_f;

  /* Sum: '<S10>/SumA31' incorporates:
   *  Delay: '<S10>/Delay11'
   *  Delay: '<S10>/Delay21'
   *  Gain: '<S10>/a(2)(1)'
   *  Gain: '<S10>/a(3)(1)'
   *  Gain: '<S10>/s(1)'
   *  MATLAB Function: '<Root>/MATLAB Function'
   *  Sum: '<S10>/SumA21'
   */
  motor_twist_B.SumA31_i = (motor_twist_P.s1_Gain_l *
    motor_twist_B.In1.velocity[2] - motor_twist_P.a21_Gain_o *
    motor_twist_DW.Delay11_DSTATE_i) - motor_twist_P.a31_Gain_o *
    motor_twist_DW.Delay21_DSTATE_m;

  /* Sum: '<S10>/SumA32' incorporates:
   *  Delay: '<S10>/Delay11'
   *  Delay: '<S10>/Delay12'
   *  Delay: '<S10>/Delay21'
   *  Delay: '<S10>/Delay22'
   *  Gain: '<S10>/a(2)(2)'
   *  Gain: '<S10>/a(3)(2)'
   *  Gain: '<S10>/b(2)(1)'
   *  Gain: '<S10>/s(2)'
   *  Sum: '<S10>/SumA22'
   *  Sum: '<S10>/SumB21'
   *  Sum: '<S10>/SumB31'
   */
  motor_twist_B.SumA32_e = (((motor_twist_P.b21_Gain_f *
    motor_twist_DW.Delay11_DSTATE_i + motor_twist_B.SumA31_i) +
    motor_twist_DW.Delay21_DSTATE_m) * motor_twist_P.s2_Gain_d -
    motor_twist_P.a22_Gain_b * motor_twist_DW.Delay12_DSTATE_l) -
    motor_twist_P.a32_Gain_p * motor_twist_DW.Delay22_DSTATE_p;

  /* Sum: '<S10>/SumA33' incorporates:
   *  Delay: '<S10>/Delay12'
   *  Delay: '<S10>/Delay13'
   *  Delay: '<S10>/Delay22'
   *  Delay: '<S10>/Delay23'
   *  Gain: '<S10>/a(2)(3)'
   *  Gain: '<S10>/a(3)(3)'
   *  Gain: '<S10>/b(2)(2)'
   *  Gain: '<S10>/s(3)'
   *  Sum: '<S10>/SumA23'
   *  Sum: '<S10>/SumB22'
   *  Sum: '<S10>/SumB32'
   */
  motor_twist_B.SumA33_h = (((motor_twist_P.b22_Gain_f *
    motor_twist_DW.Delay12_DSTATE_l + motor_twist_B.SumA32_e) +
    motor_twist_DW.Delay22_DSTATE_p) * motor_twist_P.s3_Gain_nz -
    motor_twist_P.a23_Gain_l * motor_twist_DW.Delay13_DSTATE_i) -
    motor_twist_P.a33_Gain_m * motor_twist_DW.Delay23_DSTATE_b;

  /* Sum: '<S10>/SumA34' incorporates:
   *  Delay: '<S10>/Delay13'
   *  Delay: '<S10>/Delay14'
   *  Delay: '<S10>/Delay23'
   *  Delay: '<S10>/Delay24'
   *  Gain: '<S10>/a(2)(4)'
   *  Gain: '<S10>/a(3)(4)'
   *  Gain: '<S10>/b(2)(3)'
   *  Gain: '<S10>/s(4)'
   *  Sum: '<S10>/SumA24'
   *  Sum: '<S10>/SumB23'
   *  Sum: '<S10>/SumB33'
   */
  motor_twist_B.SumA34_i = (((motor_twist_P.b23_Gain_l *
    motor_twist_DW.Delay13_DSTATE_i + motor_twist_B.SumA33_h) +
    motor_twist_DW.Delay23_DSTATE_b) * motor_twist_P.s4_Gain_g -
    motor_twist_P.a24_Gain_f * motor_twist_DW.Delay14_DSTATE_p) -
    motor_twist_P.a34_Gain_f * motor_twist_DW.Delay24_DSTATE_b;

  /* Sum: '<S10>/SumA35' incorporates:
   *  Delay: '<S10>/Delay14'
   *  Delay: '<S10>/Delay15'
   *  Delay: '<S10>/Delay24'
   *  Delay: '<S10>/Delay25'
   *  Gain: '<S10>/a(2)(5)'
   *  Gain: '<S10>/a(3)(5)'
   *  Gain: '<S10>/b(2)(4)'
   *  Gain: '<S10>/s(5)'
   *  Sum: '<S10>/SumA25'
   *  Sum: '<S10>/SumB24'
   *  Sum: '<S10>/SumB34'
   */
  motor_twist_B.SumA35_k = (((motor_twist_P.b24_Gain_e *
    motor_twist_DW.Delay14_DSTATE_p + motor_twist_B.SumA34_i) +
    motor_twist_DW.Delay24_DSTATE_b) * motor_twist_P.s5_Gain_k -
    motor_twist_P.a25_Gain_h3 * motor_twist_DW.Delay15_DSTATE_o) -
    motor_twist_P.a35_Gain_b * motor_twist_DW.Delay25_DSTATE_e;

  /* Sum: '<S10>/SumB35' incorporates:
   *  Delay: '<S10>/Delay15'
   *  Delay: '<S10>/Delay25'
   *  Gain: '<S10>/b(2)(5)'
   *  Sum: '<S10>/SumB25'
   */
  rtb_SumB35_p = (motor_twist_P.b25_Gain_b * motor_twist_DW.Delay15_DSTATE_o +
                  motor_twist_B.SumA35_k) + motor_twist_DW.Delay25_DSTATE_e;

  /* MATLAB Function: '<Root>/MATLAB Function2' */
  if ((fabs(motor_twist_B.SumB35) < 0.1) && (fabs(motor_twist_B.SumB35_o) < 0.1)
      && (fabs(rtb_SumB35_p) < 0.1)) {
    motor_twist_B.v[3] = 0.01;
    motor_twist_B.v[4] = 0.01;
    motor_twist_B.v[5] = 0.01;
  } else {
    motor_twist_B.v[3] = 0.1;
    motor_twist_B.v[4] = 0.1;
    motor_twist_B.v[5] = 0.1;
  }

  motor_twist_B.v[0] = 0.0;
  motor_twist_B.v[1] = 0.0;
  motor_twist_B.v[2] = 0.0;
  memset(&motor_twist_B.covariance[0], 0, 36U * sizeof(real_T));
  for (i = 0; i < 6; i++) {
    motor_twist_B.covariance[i + 6 * i] = motor_twist_B.v[i];
  }

  /* MATLABSystem: '<Root>/Get Parameter2' */
  ParamGet_motor_twist_407.getParameter(&motor_twist_B.b_value_c);

  /* MATLABSystem: '<Root>/Get Parameter3' */
  ParamGet_motor_twist_408.getParameter(&motor_twist_B.b_value_k);

  /* MATLAB Function: '<Root>/MATLAB Function1' incorporates:
   *  MATLABSystem: '<Root>/Get Parameter2'
   *  MATLABSystem: '<Root>/Get Parameter3'
   */
  motor_twist_B.b_value[0] = motor_twist_B.b_value_k * 0.0;
  motor_twist_B.b_value[1] = motor_twist_B.b_value_k * 0.66666666666666663;
  motor_twist_B.b_value[3] = motor_twist_B.b_value_k * -0.57735026918962573;
  motor_twist_B.b_value[4] = motor_twist_B.b_value_k * -0.33333333333333331;
  motor_twist_B.b_value[6] = motor_twist_B.b_value_k * 0.57735026918962573;
  motor_twist_B.b_value[7] = motor_twist_B.b_value_k * -0.33333333333333331;
  motor_twist_B.b_value_c = 1.0 / (3.0 * motor_twist_B.b_value_c) *
    motor_twist_B.b_value_k;
  motor_twist_B.b_value[2] = motor_twist_B.b_value_c;
  motor_twist_B.b_value[5] = motor_twist_B.b_value_c;
  motor_twist_B.b_value[8] = motor_twist_B.b_value_c;
  for (i = 0; i <= 0; i += 2) {
    /* MATLAB Function: '<Root>/MATLAB Function1' */
    tmp = _mm_loadu_pd(&motor_twist_B.b_value[i + 3]);
    tmp_0 = _mm_loadu_pd(&motor_twist_B.b_value[i]);
    tmp_1 = _mm_loadu_pd(&motor_twist_B.b_value[i + 6]);
    _mm_storeu_pd(&motor_twist_B.v_m[i], _mm_add_pd(_mm_add_pd(_mm_mul_pd(tmp,
      _mm_set1_pd(motor_twist_B.SumB35_o)), _mm_mul_pd(tmp_0, _mm_set1_pd
      (motor_twist_B.SumB35))), _mm_mul_pd(tmp_1, _mm_set1_pd(rtb_SumB35_p))));
  }

  /* MATLAB Function: '<Root>/MATLAB Function1' */
  for (i = 2; i < 3; i++) {
    motor_twist_B.v_m[i] = (motor_twist_B.b_value[i + 3] *
      motor_twist_B.SumB35_o + motor_twist_B.b_value[i] * motor_twist_B.SumB35)
      + motor_twist_B.b_value[i + 6] * rtb_SumB35_p;
  }

  /* MATLABSystem: '<Root>/Current Time1' */
  currentROS2TimeBus(&motor_twist_B.rtb_CurrentTime1_c);

  /* BusAssignment: '<Root>/Bus Assignment1' incorporates:
   *  Constant: '<S1>/Constant'
   *  MATLAB Function: '<Root>/MATLAB Function1'
   *  MATLAB Function: '<Root>/MATLAB Function2'
   *  MATLAB Function: '<Root>/MATLAB Function3'
   *  MATLABSystem: '<Root>/Current Time1'
   */
  motor_twist_B.BusAssignment1 = motor_twist_P.Constant_Value_f;
  motor_twist_B.BusAssignment1.twist.twist.linear.x = 0.50000000000000011 *
    motor_twist_B.v_m[0] - 0.8660254037844386 * motor_twist_B.v_m[1];
  motor_twist_B.BusAssignment1.twist.twist.linear.y = 0.8660254037844386 *
    motor_twist_B.v_m[0] + 0.50000000000000011 * motor_twist_B.v_m[1];
  motor_twist_B.BusAssignment1.twist.twist.angular.z = motor_twist_B.v_m[2];
  memcpy(&motor_twist_B.BusAssignment1.twist.covariance[0],
         &motor_twist_B.covariance[0], 36U * sizeof(real_T));
  motor_twist_B.BusAssignment1.header.stamp = motor_twist_B.rtb_CurrentTime1_c;
  memset(&motor_twist_B.BusAssignment1.header.frame_id[0], 0, sizeof(uint8_T) <<
         7U);

  /* MATLABSystem: '<S6>/SinkBlock' */
  Pub_motor_twist_411.publish(&motor_twist_B.BusAssignment1);

  /* S-Function (saeroclockpacer): '<Root>/Simulation Pace' */
  /*
   * The Clock Pacer generates no code, it is only active in
   * interpreted simulation.
   */

  /* Update for Delay: '<S8>/Delay25' incorporates:
   *  Delay: '<S8>/Delay15'
   */
  motor_twist_DW.Delay25_DSTATE = motor_twist_DW.Delay15_DSTATE;

  /* Update for Delay: '<S8>/Delay24' incorporates:
   *  Delay: '<S8>/Delay14'
   */
  motor_twist_DW.Delay24_DSTATE = motor_twist_DW.Delay14_DSTATE;

  /* Update for Delay: '<S8>/Delay23' incorporates:
   *  Delay: '<S8>/Delay13'
   */
  motor_twist_DW.Delay23_DSTATE = motor_twist_DW.Delay13_DSTATE;

  /* Update for Delay: '<S8>/Delay22' incorporates:
   *  Delay: '<S8>/Delay12'
   */
  motor_twist_DW.Delay22_DSTATE = motor_twist_DW.Delay12_DSTATE;

  /* Update for Delay: '<S8>/Delay21' incorporates:
   *  Delay: '<S8>/Delay11'
   */
  motor_twist_DW.Delay21_DSTATE = motor_twist_DW.Delay11_DSTATE;

  /* Update for Delay: '<S8>/Delay11' */
  motor_twist_DW.Delay11_DSTATE = motor_twist_B.SumA31;

  /* Update for Delay: '<S8>/Delay12' */
  motor_twist_DW.Delay12_DSTATE = motor_twist_B.SumA32;

  /* Update for Delay: '<S8>/Delay13' */
  motor_twist_DW.Delay13_DSTATE = motor_twist_B.SumA33;

  /* Update for Delay: '<S8>/Delay14' */
  motor_twist_DW.Delay14_DSTATE = motor_twist_B.SumA34;

  /* Update for Delay: '<S8>/Delay15' */
  motor_twist_DW.Delay15_DSTATE = motor_twist_B.SumA35;

  /* Update for Delay: '<S9>/Delay25' incorporates:
   *  Delay: '<S9>/Delay15'
   */
  motor_twist_DW.Delay25_DSTATE_f = motor_twist_DW.Delay15_DSTATE_k;

  /* Update for Delay: '<S9>/Delay24' incorporates:
   *  Delay: '<S9>/Delay14'
   */
  motor_twist_DW.Delay24_DSTATE_o = motor_twist_DW.Delay14_DSTATE_n;

  /* Update for Delay: '<S9>/Delay23' incorporates:
   *  Delay: '<S9>/Delay13'
   */
  motor_twist_DW.Delay23_DSTATE_m = motor_twist_DW.Delay13_DSTATE_p;

  /* Update for Delay: '<S9>/Delay22' incorporates:
   *  Delay: '<S9>/Delay12'
   */
  motor_twist_DW.Delay22_DSTATE_m = motor_twist_DW.Delay12_DSTATE_k;

  /* Update for Delay: '<S9>/Delay21' incorporates:
   *  Delay: '<S9>/Delay11'
   */
  motor_twist_DW.Delay21_DSTATE_k = motor_twist_DW.Delay11_DSTATE_h;

  /* Update for Delay: '<S9>/Delay11' */
  motor_twist_DW.Delay11_DSTATE_h = motor_twist_B.SumA31_b;

  /* Update for Delay: '<S9>/Delay12' */
  motor_twist_DW.Delay12_DSTATE_k = motor_twist_B.SumA32_g;

  /* Update for Delay: '<S9>/Delay13' */
  motor_twist_DW.Delay13_DSTATE_p = motor_twist_B.SumA33_n;

  /* Update for Delay: '<S9>/Delay14' */
  motor_twist_DW.Delay14_DSTATE_n = motor_twist_B.SumA34_g;

  /* Update for Delay: '<S9>/Delay15' */
  motor_twist_DW.Delay15_DSTATE_k = motor_twist_B.SumA35_g;

  /* Update for Delay: '<S10>/Delay25' incorporates:
   *  Delay: '<S10>/Delay15'
   */
  motor_twist_DW.Delay25_DSTATE_e = motor_twist_DW.Delay15_DSTATE_o;

  /* Update for Delay: '<S10>/Delay24' incorporates:
   *  Delay: '<S10>/Delay14'
   */
  motor_twist_DW.Delay24_DSTATE_b = motor_twist_DW.Delay14_DSTATE_p;

  /* Update for Delay: '<S10>/Delay23' incorporates:
   *  Delay: '<S10>/Delay13'
   */
  motor_twist_DW.Delay23_DSTATE_b = motor_twist_DW.Delay13_DSTATE_i;

  /* Update for Delay: '<S10>/Delay22' incorporates:
   *  Delay: '<S10>/Delay12'
   */
  motor_twist_DW.Delay22_DSTATE_p = motor_twist_DW.Delay12_DSTATE_l;

  /* Update for Delay: '<S10>/Delay21' incorporates:
   *  Delay: '<S10>/Delay11'
   */
  motor_twist_DW.Delay21_DSTATE_m = motor_twist_DW.Delay11_DSTATE_i;

  /* Update for Delay: '<S10>/Delay11' */
  motor_twist_DW.Delay11_DSTATE_i = motor_twist_B.SumA31_i;

  /* Update for Delay: '<S10>/Delay12' */
  motor_twist_DW.Delay12_DSTATE_l = motor_twist_B.SumA32_e;

  /* Update for Delay: '<S10>/Delay13' */
  motor_twist_DW.Delay13_DSTATE_i = motor_twist_B.SumA33_h;

  /* Update for Delay: '<S10>/Delay14' */
  motor_twist_DW.Delay14_DSTATE_p = motor_twist_B.SumA34_i;

  /* Update for Delay: '<S10>/Delay15' */
  motor_twist_DW.Delay15_DSTATE_o = motor_twist_B.SumA35_k;
}

/* Model initialize function */
void motor_twist::initialize()
{
  {
    int32_T i;
    static const char_T tmp[12] = { 'r', 'o', 'b', 'o', 't', '_', 'r', 'a', 'd',
      'i', 'u', 's' };

    static const char_T tmp_0[12] = { 'w', 'h', 'e', 'e', 'l', '_', 'r', 'a',
      'd', 'i', 'u', 's' };

    /* Start for MATLABSystem: '<S7>/SourceBlock' */
    motor_twist_DW.objisempty = true;
    motor_twist_SystemCore_setup_j(&motor_twist_DW.obj_py);

    /* Start for MATLABSystem: '<Root>/Get Parameter2' */
    motor_twist_DW.obj_g.matlabCodegenIsDeleted = false;
    motor_twist_DW.objisempty_d = true;
    motor_twist_DW.obj_g.isInitialized = 1;
    for (i = 0; i < 12; i++) {
      motor_twist_B.prmName[i] = tmp[i];
    }

    motor_twist_B.prmName[12] = '\x00';
    ParamGet_motor_twist_407.initParam(&motor_twist_B.prmName[0]);
    ParamGet_motor_twist_407.setInitialValue(0.175);
    motor_twist_DW.obj_g.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<Root>/Get Parameter2' */

    /* Start for MATLABSystem: '<Root>/Get Parameter3' */
    motor_twist_DW.obj_e.matlabCodegenIsDeleted = false;
    motor_twist_DW.objisempty_k = true;
    motor_twist_DW.obj_e.isInitialized = 1;
    for (i = 0; i < 12; i++) {
      motor_twist_B.prmName[i] = tmp_0[i];
    }

    motor_twist_B.prmName[12] = '\x00';
    ParamGet_motor_twist_408.initParam(&motor_twist_B.prmName[0]);
    ParamGet_motor_twist_408.setInitialValue(0.0375);
    motor_twist_DW.obj_e.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<Root>/Get Parameter3' */

    /* Start for MATLABSystem: '<Root>/Current Time1' */
    motor_twist_DW.obj.matlabCodegenIsDeleted = false;
    motor_twist_DW.objisempty_c = true;
    motor_twist_DW.obj.isInitialized = 1;
    motor_twist_DW.obj.isSetupComplete = true;

    /* Start for MATLABSystem: '<S6>/SinkBlock' */
    motor_twist_DW.objisempty_h = true;
    motor_twist_SystemCore_setup(&motor_twist_DW.obj_p);
  }

  /* InitializeConditions for Delay: '<S8>/Delay25' */
  motor_twist_DW.Delay25_DSTATE = motor_twist_P.Delay25_InitialCondition;

  /* InitializeConditions for Delay: '<S8>/Delay24' */
  motor_twist_DW.Delay24_DSTATE = motor_twist_P.Delay24_InitialCondition;

  /* InitializeConditions for Delay: '<S8>/Delay23' */
  motor_twist_DW.Delay23_DSTATE = motor_twist_P.Delay23_InitialCondition;

  /* InitializeConditions for Delay: '<S8>/Delay22' */
  motor_twist_DW.Delay22_DSTATE = motor_twist_P.Delay22_InitialCondition;

  /* InitializeConditions for Delay: '<S8>/Delay21' */
  motor_twist_DW.Delay21_DSTATE = motor_twist_P.Delay21_InitialCondition;

  /* InitializeConditions for Delay: '<S8>/Delay11' */
  motor_twist_DW.Delay11_DSTATE = motor_twist_P.Delay11_InitialCondition;

  /* InitializeConditions for Delay: '<S8>/Delay12' */
  motor_twist_DW.Delay12_DSTATE = motor_twist_P.Delay12_InitialCondition;

  /* InitializeConditions for Delay: '<S8>/Delay13' */
  motor_twist_DW.Delay13_DSTATE = motor_twist_P.Delay13_InitialCondition;

  /* InitializeConditions for Delay: '<S8>/Delay14' */
  motor_twist_DW.Delay14_DSTATE = motor_twist_P.Delay14_InitialCondition;

  /* InitializeConditions for Delay: '<S8>/Delay15' */
  motor_twist_DW.Delay15_DSTATE = motor_twist_P.Delay15_InitialCondition;

  /* InitializeConditions for Delay: '<S9>/Delay25' */
  motor_twist_DW.Delay25_DSTATE_f = motor_twist_P.Delay25_InitialCondition_e;

  /* InitializeConditions for Delay: '<S9>/Delay24' */
  motor_twist_DW.Delay24_DSTATE_o = motor_twist_P.Delay24_InitialCondition_a;

  /* InitializeConditions for Delay: '<S9>/Delay23' */
  motor_twist_DW.Delay23_DSTATE_m = motor_twist_P.Delay23_InitialCondition_d;

  /* InitializeConditions for Delay: '<S9>/Delay22' */
  motor_twist_DW.Delay22_DSTATE_m = motor_twist_P.Delay22_InitialCondition_e;

  /* InitializeConditions for Delay: '<S9>/Delay21' */
  motor_twist_DW.Delay21_DSTATE_k = motor_twist_P.Delay21_InitialCondition_a;

  /* InitializeConditions for Delay: '<S9>/Delay11' */
  motor_twist_DW.Delay11_DSTATE_h = motor_twist_P.Delay11_InitialCondition_i;

  /* InitializeConditions for Delay: '<S9>/Delay12' */
  motor_twist_DW.Delay12_DSTATE_k = motor_twist_P.Delay12_InitialCondition_a;

  /* InitializeConditions for Delay: '<S9>/Delay13' */
  motor_twist_DW.Delay13_DSTATE_p = motor_twist_P.Delay13_InitialCondition_h;

  /* InitializeConditions for Delay: '<S9>/Delay14' */
  motor_twist_DW.Delay14_DSTATE_n = motor_twist_P.Delay14_InitialCondition_a;

  /* InitializeConditions for Delay: '<S9>/Delay15' */
  motor_twist_DW.Delay15_DSTATE_k = motor_twist_P.Delay15_InitialCondition_g;

  /* InitializeConditions for Delay: '<S10>/Delay25' */
  motor_twist_DW.Delay25_DSTATE_e = motor_twist_P.Delay25_InitialCondition_eg;

  /* InitializeConditions for Delay: '<S10>/Delay24' */
  motor_twist_DW.Delay24_DSTATE_b = motor_twist_P.Delay24_InitialCondition_l;

  /* InitializeConditions for Delay: '<S10>/Delay23' */
  motor_twist_DW.Delay23_DSTATE_b = motor_twist_P.Delay23_InitialCondition_m;

  /* InitializeConditions for Delay: '<S10>/Delay22' */
  motor_twist_DW.Delay22_DSTATE_p = motor_twist_P.Delay22_InitialCondition_d;

  /* InitializeConditions for Delay: '<S10>/Delay21' */
  motor_twist_DW.Delay21_DSTATE_m = motor_twist_P.Delay21_InitialCondition_ao;

  /* InitializeConditions for Delay: '<S10>/Delay11' */
  motor_twist_DW.Delay11_DSTATE_i = motor_twist_P.Delay11_InitialCondition_o;

  /* InitializeConditions for Delay: '<S10>/Delay12' */
  motor_twist_DW.Delay12_DSTATE_l = motor_twist_P.Delay12_InitialCondition_j;

  /* InitializeConditions for Delay: '<S10>/Delay13' */
  motor_twist_DW.Delay13_DSTATE_i = motor_twist_P.Delay13_InitialCondition_m;

  /* InitializeConditions for Delay: '<S10>/Delay14' */
  motor_twist_DW.Delay14_DSTATE_p = motor_twist_P.Delay14_InitialCondition_g;

  /* InitializeConditions for Delay: '<S10>/Delay15' */
  motor_twist_DW.Delay15_DSTATE_o = motor_twist_P.Delay15_InitialCondition_l;

  /* SystemInitialize for Enabled SubSystem: '<S7>/Enabled Subsystem' */
  /* SystemInitialize for SignalConversion generated from: '<S11>/In1' incorporates:
   *  Outport: '<S11>/Out1'
   */
  motor_twist_B.In1 = motor_twist_P.Out1_Y0;

  /* End of SystemInitialize for SubSystem: '<S7>/Enabled Subsystem' */
}

/* Model terminate function */
void motor_twist::terminate()
{
  /* Terminate for MATLABSystem: '<S7>/SourceBlock' */
  if (!motor_twist_DW.obj_py.matlabCodegenIsDeleted) {
    motor_twist_DW.obj_py.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S7>/SourceBlock' */

  /* Terminate for MATLABSystem: '<Root>/Get Parameter2' */
  if (!motor_twist_DW.obj_g.matlabCodegenIsDeleted) {
    motor_twist_DW.obj_g.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<Root>/Get Parameter2' */

  /* Terminate for MATLABSystem: '<Root>/Get Parameter3' */
  if (!motor_twist_DW.obj_e.matlabCodegenIsDeleted) {
    motor_twist_DW.obj_e.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<Root>/Get Parameter3' */

  /* Terminate for MATLABSystem: '<Root>/Current Time1' */
  if (!motor_twist_DW.obj.matlabCodegenIsDeleted) {
    motor_twist_DW.obj.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<Root>/Current Time1' */

  /* Terminate for MATLABSystem: '<S6>/SinkBlock' */
  if (!motor_twist_DW.obj_p.matlabCodegenIsDeleted) {
    motor_twist_DW.obj_p.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S6>/SinkBlock' */
}

/* Constructor */
motor_twist::motor_twist() :
  motor_twist_B(),
  motor_twist_DW(),
  motor_twist_M()
{
  /* Currently there is no constructor body generated.*/
}

/* Destructor */
motor_twist::~motor_twist()
{
  /* Currently there is no destructor body generated.*/
}

/* Real-Time Model get method */
RT_MODEL_motor_twist_T * motor_twist::getRTM()
{
  return (&motor_twist_M);
}
