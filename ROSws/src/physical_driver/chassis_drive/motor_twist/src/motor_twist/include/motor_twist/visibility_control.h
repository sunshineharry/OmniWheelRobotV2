#ifndef MOTOR_TWIST__VISIBILITY_CONTROL_H_
#define MOTOR_TWIST__VISIBILITY_CONTROL_H_
#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define MOTOR_TWIST_EXPORT __attribute__ ((dllexport))
    #define MOTOR_TWIST_IMPORT __attribute__ ((dllimport))
  #else
    #define MOTOR_TWIST_EXPORT __declspec(dllexport)
    #define MOTOR_TWIST_IMPORT __declspec(dllimport)
  #endif
  #ifdef MOTOR_TWIST_BUILDING_LIBRARY
    #define MOTOR_TWIST_PUBLIC MOTOR_TWIST_EXPORT
  #else
    #define MOTOR_TWIST_PUBLIC MOTOR_TWIST_IMPORT
  #endif
  #define MOTOR_TWIST_PUBLIC_TYPE MOTOR_TWIST_PUBLIC
  #define MOTOR_TWIST_LOCAL
#else
  #define MOTOR_TWIST_EXPORT __attribute__ ((visibility("default")))
  #define MOTOR_TWIST_IMPORT
  #if __GNUC__ >= 4
    #define MOTOR_TWIST_PUBLIC __attribute__ ((visibility("default")))
    #define MOTOR_TWIST_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define MOTOR_TWIST_PUBLIC
    #define MOTOR_TWIST_LOCAL
  #endif
  #define MOTOR_TWIST_PUBLIC_TYPE
#endif
#endif  // MOTOR_TWIST__VISIBILITY_CONTROL_H_
// Generated 13-Apr-2024 12:33:48
 