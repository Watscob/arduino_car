#pragma once

#include <Arduino.h>
#include <WiFiEsp.h>

enum Request
{
    UNDEFINED,
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

class CarWiFi 
{
public:
    CarWiFi(char ssid[], char pass[]);
    ~CarWiFi();
    bool connect();
    String get_SSID();
    IPAddress get_IP();
    bool is_connected();
    Request recv_request();

private:
    char *ssid_;
    char *pass_;
    int status_;
    RingBuffer buf_;
    WiFiEspServer server_;
    
    void send_response_(WiFiEspClient client);
};