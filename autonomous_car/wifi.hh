#pragma once

#include <Arduino.h>
#include <WiFiEsp.h>

enum Request
{
    UNDEFINED
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
    void send_response(WiFiEspClient client);
    Request recv_request();

private:
    char *ssid_;
    char *pass_;
    int status_;
    RingBuffer buf_;
    WiFiEspServer server_;
};