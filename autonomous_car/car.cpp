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

void Car::do_action(Action action)
{
    switch(action)
    {
        case Action::SPEED_PLUS:
            set_speed_off_(5);
            break;
        case Action::SPEED_MINUS:
            set_speed_off_(-5);
            break;
        case Action::MAX_SPEED:
            set_speed_(max_speed_);
            break;
        case Action::MIN_SPEED:
            set_speed_(min_speed_);
            break;
        case Action::GO_FORWARD:
            set_direction_(FORWARD);
            break;
        case Action::GO_BACKWARD:
            set_direction_(BACKWARD);
            break;
        case Action::ROTATE_LEFT:
            rotate_left_();
            break;
        case Action::ROTATE_RIGHT:
            rotate_right_();
            break;
        case Action::STOP:
            set_direction_(RELEASE);
            break;
        case Action::LIGHT_ALL:
            handle_led_(HIGH, HIGH, HIGH, HIGH);
            break;
        case Action::LIGHT_FRONT:
            handle_led_(HIGH, HIGH, LOW, LOW);
            break;
        case Action::LIGHT_BACK:
            handle_led_(LOW, LOW, HIGH, HIGH);
            break;
        case Action::LIGHT_OFF:
            handle_led_(LOW, LOW, LOW, LOW);
            break;
        case Action::LIGHT_BLINK:
            led_blink_(100, 3);
            break;
        default:
            set_direction_(RELEASE);
            break;
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
    uint8_t save_fl = digitalRead(led_front_left_);
    uint8_t save_fr = digitalRead(led_front_right_);
    uint8_t save_bl = digitalRead(led_back_left_);
    uint8_t save_br = digitalRead(led_back_right_);

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

        nb_turn--;
    }

    handle_led_(save_fl, save_fr, save_bl, save_br);
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