#include "car.hh"

Car::Car(uint8_t min_speed, uint8_t max_speed)
  : m_sp_(min_speed)
  , min_speed_(min_speed)
  , max_speed_(max_speed)
  , mid_speed_(min_speed + (max_speed - min_speed) / 2)
  , m_dir_(RELEASE) 
{
  m_motor_back_l_ = new AF_DCMotor(1, MOTOR12_64KHZ);
  m_motor_back_r_ = new AF_DCMotor(2, MOTOR12_64KHZ); 
  m_motor_front_r_ = new AF_DCMotor(3, MOTOR34_64KHZ); 
  m_motor_front_l_ = new AF_DCMotor(4, MOTOR34_64KHZ);
  
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

void Car::do_action(String s)
{
  if (s[0] == '+' || s[0] == '-')
  {
    uint8_t sp = s.toInt();
    if (sp != 0)
      set_speed_off_(sp);
  }
  else if (s.substring(0, 5) == "SPEED")
  {
    uint8_t sp = s.substring(5, s.length()).toInt();
    if (sp != 0)
      set_speed_(sp);
  }
  else if (s == "MAX_SPEED")
    set_speed_(max_speed_);
  else if (s == "MIN_SPEED")
    set_speed_(min_speed_);
  else if (s == "GO_FORWARD")
    set_direction_(FORWARD);
  else if (s == "GO_BACKWARD")
    set_direction_(BACKWARD);
  else if (s == "ROTATE_LEFT")
    rotate_left_();
  else if (s == "ROTATE_RIGHT")
    rotate_right_();
  else if (s == "STOP")
    set_direction_(RELEASE);
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
  m_motor_back_l_->run(BACKWARD);
  m_motor_front_l_->run(BACKWARD);
  m_motor_back_r_->run(FORWARD);
  m_motor_front_r_->run(FORWARD);
}

void Car::rotate_left_()
{  
  m_motor_back_r_->run(BACKWARD);
  m_motor_front_r_->run(BACKWARD);
  m_motor_back_l_->run(FORWARD);
  m_motor_front_l_->run(FORWARD);
}
