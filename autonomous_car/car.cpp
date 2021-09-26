#include "car.hh"

Car::Car(uint8_t min_speed, uint8_t max_speed, 
        uint8_t front, uint8_t back)
    : m_sp_(min_speed)
    , min_speed_(min_speed)
    , max_speed_(max_speed)
    , mid_speed_(min_speed + (max_speed - min_speed) / 2)
    , m_dir_(RELEASE) 
    , led_front_(front)
    , led_back_(back)
{
    pinMode(led_front_, OUTPUT);
    pinMode(led_back_, OUTPUT);
    
    m_motor_back_l_ = new AF_DCMotor(1, MOTOR12_64KHZ);
    m_motor_back_r_ = new AF_DCMotor(2, MOTOR12_64KHZ); 
    m_motor_front_r_ = new AF_DCMotor(3, MOTOR34_64KHZ); 
    m_motor_front_l_ = new AF_DCMotor(4, MOTOR34_64KHZ);
  
    set_direction_(m_dir_);
    set_speed_(m_sp_);
  
    handle_led_(LOW, LOW);
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
        case Action::ACTION_SPEED_PLUS:
            set_speed_off_(5);
            break;
        case Action::ACTION_SPEED_MINUS:
            set_speed_off_(-5);
            break;
        case Action::ACTION_MAX_SPEED:
            set_speed_(max_speed_);
            break;
        case Action::ACTION_MIN_SPEED:
            set_speed_(min_speed_);
            break;
        case Action::ACTION_GO_FORWARD:
            set_direction_(FORWARD);
            break;
        case Action::ACTION_GO_BACKWARD:
            set_direction_(BACKWARD);
            break;
        case Action::ACTION_ROTATE_LEFT:
            rotate_left_();
            break;
        case Action::ACTION_ROTATE_RIGHT:
            rotate_right_();
            break;
        case Action::ACTION_STOP:
            set_direction_(RELEASE);
            break;
        case Action::ACTION_LIGHT_ALL:
            handle_led_(HIGH, HIGH);
            break;
        case Action::ACTION_LIGHT_FRONT:
            handle_led_(HIGH, LOW);
            break;
        case Action::ACTION_LIGHT_BACK:
            handle_led_(LOW, HIGH);
            break;
        case Action::ACTION_LIGHT_OFF:
            handle_led_(LOW, LOW);
            break;
        case Action::ACTION_LIGHT_BLINK:
            led_blink_(100, 8);
            break;
        case Action::ACTION_LIGHT_READY:
            led_blink_(50, 6);
            break;
        default:
            set_direction_(RELEASE);
            break;
    }
}

void Car::handle_led_(uint8_t f, uint8_t b)
{
    digitalWrite(led_front_, f);
    digitalWrite(led_back_, b);
}

void Car::led_blink_(unsigned long slp, uint8_t nb_turn)
{
    uint8_t save_front = digitalRead(led_front_);
    uint8_t save_back = digitalRead(led_back_);

    while (nb_turn > 0)
    {
        handle_led_(HIGH, HIGH);
        delay(slp);
  
        handle_led_(LOW, LOW);
        delay(slp);

        nb_turn--;
    }

    handle_led_(save_front, save_back);
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

void Car::rotate_left_()
{
    m_motor_back_l_->run(BACKWARD);
    m_motor_front_l_->run(BACKWARD);
    m_motor_back_r_->run(FORWARD);
    m_motor_front_r_->run(FORWARD);
}

void Car::rotate_right_()
{  
    m_motor_back_r_->run(BACKWARD);
    m_motor_front_r_->run(BACKWARD);
    m_motor_back_l_->run(FORWARD);
    m_motor_front_l_->run(FORWARD);
}
