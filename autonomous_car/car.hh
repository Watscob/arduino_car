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

enum Action
{
    ACTION_SPEED_PLUS,
    ACTION_SPEED_MINUS,
    ACTION_MIN_SPEED,
    ACTION_MAX_SPEED,
    ACTION_GO_FORWARD,
    ACTION_GO_BACKWARD,
    ACTION_ROTATE_LEFT,
    ACTION_ROTATE_RIGHT,
    ACTION_STOP,
    ACTION_LIGHT_ALL,
    ACTION_LIGHT_FRONT,
    ACTION_LIGHT_BACK,
    ACTION_LIGHT_OFF,
    ACTION_LIGHT_BLINK,
    ACTION_LIGHT_READY
};

class Car
{
public:
    Car(uint8_t min_speed, uint8_t max_speed, 
        uint8_t front, uint8_t back);
    ~Car();

    void do_action(Action action);
  
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

    uint8_t led_front_;
    uint8_t led_back_;

    void handle_led_(uint8_t front, uint8_t back);
    void led_blink_(unsigned long slp, uint8_t nb_turn);
  
    void set_speed_(uint8_t sp);
    void set_speed_off_(int8_t sp);

    //RELEASE, FORWARD, BACKWARD
    void set_direction_(uint8_t dir);
    void rotate_left_();
    void rotate_right_();
    void reset_rotate_();
};
