#pragma once

#include <AFMotor.h>
#include <Arduino.h>

inline int clamp(int x, int x_min, int x_max)
{
  if (x < x_min)
    x = x_min;
  else if (x > x_max)
    x = x_max;
  return x;
}

class Car
{
public:
  Car(uint8_t sp, uint8_t min_speed, uint8_t max_speed);
  ~Car();

  void do_action(String s);
  
private:
  AF_DCMotor *m_motor_back_l_;
  AF_DCMotor *m_motor_back_r_;
  AF_DCMotor *m_motor_front_l_;
  AF_DCMotor *m_motor_front_r_;
  uint8_t m_sp_;
  uint8_t m_dir_;
  uint8_t min_speed_;
  uint8_t mid_speed_;
  uint8_t max_speed_;
  uint8_t save_speed_;
  
  void set_speed_(uint8_t sp);
  void set_speed_off_(int8_t sp);

  //RELEASE, FORWARD, BACKWARD
  void set_direction_(uint8_t dir);
  void rotate_left_();
  void rotate_right_();
  void reset_rotate_();
};
