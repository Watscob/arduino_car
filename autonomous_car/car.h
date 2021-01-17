#ifndef CAR_H
#define CAR_H

#include <AFMotor.h>

class Car
{
  public:
  Car(uint8_t sp);
  ~Car();

  //Min value is 200 for work correctly (why ? I don't know)
  //Max value is 255
  void set_speed(uint8_t sp);
  void set_speed_off(int8_t sp);

  //RELEASE, FORWARD, BACKWARD
  void set_direction(uint8_t dir);
  void turn_left();
  void turn_right();
  void rotate_left();
  void rotate_right();
  
  private:
  
  AF_DCMotor *m_motor_back_l;
  AF_DCMotor *m_motor_back_r;
  AF_DCMotor *m_motor_front_l;
  AF_DCMotor *m_motor_front_r;
  uint8_t m_sp;
  uint8_t m_dir;
};

#endif /* !CAR_H */
