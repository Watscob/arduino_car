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
    SPEED_PLUS,
    SPEED_MINUS,
    MIN_SPEED,
    MAX_SPEED,
    GO_FORWARD,
    GO_BACKWARD,
    ROTATE_LEFT,
    ROTATE_RIGHT,
    STOP,
    LIGHT_ALL,
    LIGHT_FRONT,
    LIGHT_BACK,
    LIGHT_OFF,
    LIGHT_BLINK
};

class Car
{
public:
    Car(uint8_t min_speed, uint8_t max_speed, 
        uint8_t front_left, uint8_t front_right, 
        uint8_t back_left, uint8_t back_right);
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

    uint8_t led_front_left_;
    uint8_t led_front_right_;
    uint8_t led_back_left_;
    uint8_t led_back_right_;

    void handle_led_(uint8_t fl, uint8_t fr, uint8_t bl, uint8_t br);
    void led_blink_(uint8_t slp, uint8_t nb_turn);
  
    void set_speed_(uint8_t sp);
    void set_speed_off_(int8_t sp);

    //RELEASE, FORWARD, BACKWARD
    void set_direction_(uint8_t dir);
    void rotate_left_();
    void rotate_right_();
    void reset_rotate_();
};