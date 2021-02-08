#include "car.hh"

#include <Arduino.h>

int min_speed = 180;
int mid_speed = 217;
int max_speed = 255;

static int clamp(int x, int x_min, int x_max)
{
  if (x < x_min)
    x = x_min;
  else if (x > x_max)
    x = x_max;
  return x;
}

Car::Car(uint8_t sp): m_sp(sp), m_dir(RELEASE) 
{
  m_motor_back_l = new AF_DCMotor(1);
  m_motor_back_r = new AF_DCMotor(2); 
  m_motor_front_r = new AF_DCMotor(3); 
  m_motor_front_l = new AF_DCMotor(4); 
}

Car::~Car()
{
  delete m_motor_back_l;
  delete m_motor_back_r;
  delete m_motor_front_l;
  delete m_motor_front_r;
}

void Car::set_speed(uint8_t sp)
{
  m_sp = clamp(sp, min_speed, max_speed);
    
  m_motor_back_l->setSpeed(m_sp);
  m_motor_back_r->setSpeed(m_sp);
  m_motor_front_l->setSpeed(m_sp);
  m_motor_front_r->setSpeed(m_sp);
}

void Car::set_speed_off(int8_t sp)
{
  set_speed(m_sp + sp);
}

void Car::set_direction(uint8_t dir)
{
  m_dir = dir;
  m_motor_back_l->run(m_dir);
  m_motor_back_r->run(m_dir);
  m_motor_front_l->run(m_dir);
  m_motor_front_r->run(m_dir);
}

void Car::turn_left()
{
  m_motor_back_r->setSpeed(mid_speed);
  m_motor_front_r->setSpeed(mid_speed);
  m_motor_back_l->setSpeed(min_speed);
  m_motor_front_l->setSpeed(min_speed);
}

void Car::turn_right()
{
  m_motor_back_r->setSpeed(min_speed);
  m_motor_front_r->setSpeed(min_speed);
  m_motor_back_l->setSpeed(mid_speed);
  m_motor_front_l->setSpeed(mid_speed);
}

void Car::reset_turn()
{
  set_speed(m_sp);
}

void Car::rotate_left()
{
  set_speed(min_speed);
  m_motor_back_l->run(BACKWARD);
  m_motor_front_l->run(BACKWARD);
  m_motor_back_r->run(FORWARD);
  m_motor_front_r->run(FORWARD);
  set_speed(m_sp);
}

void Car::rotate_right()
{
  set_speed(min_speed);
  m_motor_back_r->run(BACKWARD);
  m_motor_front_r->run(BACKWARD);
  m_motor_back_l->run(FORWARD);
  m_motor_front_l->run(FORWARD);
  set_speed(m_sp);
}
