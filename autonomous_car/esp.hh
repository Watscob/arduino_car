#pragma once

#include <Arduino.h>

enum Request
{
    REQUEST_UNDEFINED,      // 0
    REQUEST_SPEED_PLUS,     // 1
    REQUEST_SPEED_MINUS,    // 2
    REQUEST_MIN_SPEED,      // 3
    REQUEST_MAX_SPEED,      // 4
    REQUEST_GO_FORWARD,     // 5
    REQUEST_GO_BACKWARD,    // 6
    REQUEST_ROTATE_LEFT,    // 7
    REQUEST_ROTATE_RIGHT,   // 8
    REQUEST_STOP,           // 9
    REQUEST_LIGHT_ALL,      //10
    REQUEST_LIGHT_FRONT,    //11
    REQUEST_LIGHT_BACK,     //12
    REQUEST_LIGHT_OFF,      //13
    REQUEST_LIGHT_BLINK,    //14        

    REQUEST_CONNECTED,      //15
    REQUEST_GET_SSID,       //16
    REQUEST_GET_IP          //17
};

class ESPAdaptator
{
public:
    ESPAdaptator(long update_speed);
    ~ESPAdaptator();
    Request read_wifi(String *arg);
};
