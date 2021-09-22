#pragma once

#include <Arduino.h>
#include <WiFiEsp.h>

#include "car.hh"

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

class CarWiFi 
{
public:
    CarWiFi(char const *ssid, char const *pass);
    ~CarWiFi();
    bool connect();
    String get_SSID();
    IPAddress get_IP();
    bool is_connected();
    Request recv_request();

private:
    char const *ssid_;
    char const *pass_;
    int status_;
    RingBuffer buf_;
    WiFiEspServer server_;
    
    void send_response_(WiFiEspClient client);
};
