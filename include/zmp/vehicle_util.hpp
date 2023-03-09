#ifndef vehicle_util_hpp
#define vehicle_util_hpp
#include "HevCnt.h"

#include <vehicle_info.hpp>

#include <chrono>
#include <iostream>
#include <queue>
#include <string>
#include <thread>

static double steering_diff_sum = 0;
static double estimate_accel = 0.0;
static int target_accel_level = 0;
static double accel_diff_sum = 0;
static double brake_diff_sum = 0;
std::queue<double> steering_diff_buffer;
std::queue<double> accel_diff_buffer;
std::queue<double> brake_diff_buffer;

class VehicleUtil
{
public:
  VehicleUtil();
  ~VehicleUtil();
  HevCnt * hev;
  BattInf _battInf;
  BrakeInf _brakeInf;
  OtherInf _otherInf;
  DrvInf _drvInf;
  StrInf _strInf;
  vehicle_state_t vstate;

  void ZMP_STOP();
  void readLoop();
  static long long int getTime();
  static double KmhToMs(double kmh);
  static double Kmh100ToMs(double kmh100);
  static double RadToDeg(double rad);
  static double DegToRad(double deg);
  double calculateVariableGearRatio(const double vel, const double steer_wheel);

  // streering
  static void clear_diff_str();
  void SetStrMode(int mode);
  int ZMP_STR_CONTROLED();
  void ZMP_SET_STR_PROGRAM();
  void ZMP_SET_STR_MANUAL();
  void ZMP_SET_STR_ANGLE(double angle);
  void ZMP_SET_STR_TORQUE(double torque);
  void SteeringControl(double current_steering_angle, double cmd_steering_angle);
  double _str_torque_pid_control(double current_steering_angle, double cmd_steering_angle);

  // drive
  static void clear_diff_drv();
  void SetDrvMode(int mode);
  int ZMP_DRV_CONTROLED();
  void ZMP_SET_DRV_PROGRAM();
  void ZMP_SET_DRV_MANUAL();
  void SetGear(int gear);
  void ZMP_SET_SHIFT_POS_D();
  void ZMP_SET_SHIFT_POS_N();
  void ZMP_SET_SHIFT_POS_R();
  void ZMP_SET_SHIFT_POS_B();
  double _accel_stroke_pid_control(double current_velocity, double cmd_velocity);
  double _brake_stroke_pid_control(double current_velocity, double cmd_velocity);

  std::thread read_thread;

  // Setter

  // Getter
  float getVelocity();
  double getSteeringAngle();
  int getGear();
  bool getBlinkerLeft();
  bool getBlinkerRight();
  void SetBlinkerLeftON();
  void SetBlinkerRightON();
  void SetBlinkerLeftOFF();
  void SetBlinkerRightOFF();
  float getCurrentBrake();
  float getCurrentAccel();
  bool getDoorStatus();
};

#endif  // vehicle_util_hpp