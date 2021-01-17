#include "car.h"

#include <Arduino.h>

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
  m_sp = sp;
  m_motor_back_l->setSpeed(m_sp);
  m_motor_back_r->setSpeed(m_sp);
  m_motor_front_l->setSpeed(m_sp);
  m_motor_front_r->setSpeed(m_sp);
}

void Car::set_speed_off(int8_t sp)
{
  if (m_sp + sp >= 0 && m_sp + sp <= 255)
  {
    m_sp += sp;
    m_motor_back_l->setSpeed(m_sp);
    m_motor_back_r->setSpeed(m_sp);
    m_motor_front_l->setSpeed(m_sp);
    m_motor_front_r->setSpeed(m_sp);
  }
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
  m_motor_back_l->setSpeed(m_sp/3);
  m_motor_front_l->setSpeed(m_sp/3);
  delay(500);
  m_motor_back_l->setSpeed(m_sp);
  m_motor_front_l->setSpeed(m_sp);
}

void Car::turn_right()
{
  m_motor_back_r->setSpeed(m_sp/3);
  m_motor_front_r->setSpeed(m_sp/3);
  delay(500);
  m_motor_back_r->setSpeed(m_sp);
  m_motor_front_r->setSpeed(m_sp);
}

void Car::rotate_left()
{
  m_motor_back_l->run(BACKWARD);
  m_motor_front_l->run(BACKWARD);
  m_motor_back_r->run(FORWARD);
  m_motor_front_r->run(FORWARD);
  delay(500);
  m_motor_back_r->run(m_dir);
  m_motor_front_r->run(m_dir);
  m_motor_back_l->run(m_dir);
  m_motor_front_l->run(m_dir);
}

void Car::rotate_right()
{
  m_motor_back_r->run(BACKWARD);
  m_motor_front_r->run(BACKWARD);
  m_motor_back_l->run(FORWARD);
  m_motor_front_l->run(FORWARD);
  delay(500);
  m_motor_back_r->run(m_dir);
  m_motor_front_r->run(m_dir);
  m_motor_back_l->run(m_dir);
  m_motor_front_l->run(m_dir);
}
