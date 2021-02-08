#pragma once

#include <AFMotor.h>

class Car
{
public:
  Car(uint8_t sp, uint8_t min_speed, uint8_t max_speed);
  ~Car();

  inline int clamp(int x, int x_min, int x_max)
  {
    if (x < x_min)
      x = x_min;
    else if (x > x_max)
      x = x_max;
    return x;
  }

  //Min value is 200 for work correctly (why ? I don't know)
  //Max value is 255
  void do_action(char c);
  void set_speed(uint8_t sp);
  void set_speed_off(int8_t sp);

  //RELEASE, FORWARD, BACKWARD
  void set_direction(uint8_t dir);
  void turn_left();
  void turn_right();
  void reset_turn();
  void rotate_left();
  void rotate_right();
  
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
};
