#include "car.hh"

Car::Car(uint8_t min_speed, uint8_t max_speed, 
         uint8_t front_left, uint8_t front_right, 
         uint8_t back_left, uint8_t back_right)
  : m_sp_(min_speed)
  , min_speed_(min_speed)
  , max_speed_(max_speed)
  , mid_speed_(min_speed + (max_speed - min_speed) / 2)
  , m_dir_(RELEASE) 
  , led_front_left_(front_left)
  , led_front_right_(front_right)
  , led_back_left_(back_left)
  , led_back_right_(back_right)
{
  m_motor_back_l_ = new AF_DCMotor(1, MOTOR12_64KHZ);
  m_motor_back_r_ = new AF_DCMotor(2, MOTOR12_64KHZ); 
  m_motor_front_r_ = new AF_DCMotor(3, MOTOR34_64KHZ); 
  m_motor_front_l_ = new AF_DCMotor(4, MOTOR34_64KHZ);
  
  set_direction_(m_dir_);
  set_speed_(m_sp_);
  
  pinMode(led_front_left_, OUTPUT);
  pinMode(led_front_right_, OUTPUT);
  pinMode(led_back_left_, OUTPUT);
  pinMode(led_back_right_, OUTPUT);
  
  handle_led_(LOW, LOW, LOW, LOW);
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
  else if (s == "LIGHT_ALL")
    handle_led_(HIGH, HIGH, HIGH, HIGH);
  else if (s == "LIGHT_FRONT")
    handle_led_(HIGH, HIGH, LOW, LOW);
  else if (s == "LIGHT_BACK")
    handle_led_(LOW, LOW, HIGH, HIGH);
  else if (s == "LIGHT_OFF")
    handle_led_(LOW, LOW, LOW, LOW);
  else if (s.substring(0, 11) == "LIGHT_BLINK")
  {
    uint8_t slp = s.substring(11, s.length()).toInt();
    if (slp != 0)
      led_blink_(slp, 3);
  }
}

void Car::handle_led_(uint8_t fl, uint8_t fr, uint8_t bl, uint8_t br)
{
  digitalWrite(led_front_left_, fl);
  digitalWrite(led_front_right_, fr);
  digitalWrite(led_back_left_, bl);
  digitalWrite(led_back_right_, br);
}

void Car::led_blink_(uint8_t slp, uint8_t nb_turn)
{
  while (nb_turn > 0)
  {
    handle_led_(HIGH, LOW, LOW, LOW);
    delay(slp);
  
    handle_led_(LOW, HIGH, LOW, LOW);
    delay(slp);
  
    handle_led_(LOW, LOW, LOW, HIGH);
    delay(slp);
  
    handle_led_(LOW, LOW, HIGH, LOW);
    delay(slp);
  
    handle_led_(LOW, LOW, LOW, LOW);
    nb_turn--;
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
