#include "car.hh"

#include <Arduino.h>

Car::Car(uint8_t sp, uint8_t min_speed, uint8_t max_speed)
  : m_sp_(sp)
  , min_speed_(min_speed)
  , max_speed_(max_speed)
  , mid_speed_(min_speed + (max_speed - min_speed) / 2)
  , save_speed_(min_speed)
  , m_dir_(RELEASE) 
{
  m_motor_back_l_ = new AF_DCMotor(1);
  m_motor_back_r_ = new AF_DCMotor(2); 
  m_motor_front_r_ = new AF_DCMotor(3); 
  m_motor_front_l_ = new AF_DCMotor(4);
  
  set_direction_(m_dir_);
  set_speed_(m_sp_);
}

Car::~Car()
{
  delete m_motor_back_l_;
  delete m_motor_back_r_;
  delete m_motor_front_l_;
  delete m_motor_front_r_;
}

void Car::do_action(char c)
{
  switch(c)
  {
    case '+':
      set_speed_off_(5);
      break;
    case '-':
      set_speed_off_(-5);
      break;
    case 'U':
      set_direction_(FORWARD);
      break;
    case 'D':
      set_direction_(BACKWARD);
      break;
    case 'L':
      rotate_left_();
      break;
    case 'R':
      rotate_right_();
      break;
    case 'T':
      reset_rotate_();
    default:
      set_direction_(RELEASE);
      break;
  }
}

void Car::set_speed_(uint8_t sp)
{
  m_sp_ = clamp(sp, min_speed_, max_speed_);
    
  m_motor_back_l_->setSpeed(m_sp_);
  m_motor_back_r_->setSpeed(m_sp_);
  m_motor_front_l_->setSpeed(m_sp_);
  m_motor_front_r_->setSpeed(m_sp_);
}

void Car::set_speed_off_(int8_t sp)
{
  set_speed_(m_sp_ + sp);
}

void Car::set_direction_(uint8_t dir)
{
  m_dir_ = dir;
  
  m_motor_back_l_->run(m_dir_);
  m_motor_back_r_->run(m_dir_);
  m_motor_front_l_->run(m_dir_);
  m_motor_front_r_->run(m_dir_);
}

void Car::rotate_right_()
{
  save_speed_ = m_sp_;
  set_speed_(min_speed_);
  
  m_motor_back_l_->run(BACKWARD);
  m_motor_front_l_->run(BACKWARD);
  m_motor_back_r_->run(FORWARD);
  m_motor_front_r_->run(FORWARD);
}

void Car::rotate_left_()
{
  save_speed_ = m_sp_;
  set_speed_(min_speed_);
  
  m_motor_back_r_->run(BACKWARD);
  m_motor_front_r_->run(BACKWARD);
  m_motor_back_l_->run(FORWARD);
  m_motor_front_l_->run(FORWARD);
}

void Car::reset_rotate_()
{
  set_speed_(save_speed_);
  set_direction_(RELEASE);
}
