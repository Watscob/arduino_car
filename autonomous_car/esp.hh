#pragma once

#include <Arduino.h>

enum Request
{
    REQUEST_UNDEFINED,
    REQUEST_SPEED_PLUS,
    REQUEST_SPEED_MINUS,
    REQUEST_MIN_SPEED,
    REQUEST_MAX_SPEED,
    REQUEST_GO_FORWARD,
    REQUEST_GO_BACKWARD,
    REQUEST_ROTATE_LEFT,
    REQUEST_ROTATE_RIGHT,
    REQUEST_STOP,
    REQUEST_LIGHT_ALL,
    REQUEST_LIGHT_FRONT,
    REQUEST_LIGHT_BACK,
    REQUEST_LIGHT_OFF,
    REQUEST_LIGHT_BLINK
};

class ESPAdaptator
{
public:
    ESPAdaptator();
    ~ESPAdaptator();
    bool is_connected();
    String get_SSID();
    String get_IP();
    Request get_request();
    void process();
private:
    bool is_connected_;
    String SSID_;
    String IP_;
    Request request_;
};
