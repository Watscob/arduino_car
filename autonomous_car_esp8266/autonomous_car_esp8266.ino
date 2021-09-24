#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266mDNS.h>
#include <ESP8266WiFiMulti.h> 

#include "index.hh"

ESP8266WiFiMulti wifiMulti;
ESP8266WebServer server(80);

void setup() {
    Serial.begin(115200);

    WiFi.hostname("ArduinoCar");

    wifiMulti.addAP("Livebox-FBFC", "BonAnniv54");

    Serial.println("#CONNECTING");
    while (wifiMulti.run() != WL_CONNECTED)
        delay(500);
    Serial.println("#CONNECTED");
    Serial.print("#SSID ");
    Serial.println(WiFi.SSID());
    Serial.print("#IP ");
    Serial.println(WiFi.localIP());

    
    server.on("/", HTTP_GET, []() {
        server.send(200, "text/html", defaultPage);
    });
    server.on("/index.html", HTTP_GET, []() {
        server.send(200, "text/html", defaultPage);
    });
    server.onNotFound([]() {
        server.send(404, "text/plain", "404: Not found");
    });
    
    server.on("/move/forward", HTTP_POST, []() {
        send_command("move_forward"); 
    });
    server.on("/move/backward", HTTP_POST, []() {
        send_command("move_backward"); 
    });
    server.on("/move/rotate/left", HTTP_POST, []() {
        send_command("move_rotate_left"); 
    });
    server.on("/move/rotate/right", HTTP_POST, []() {
        send_command("move_rotate_right"); 
    });
    server.on("/move/stop", HTTP_POST, []() {
        send_command("move_stop"); 
    });
    server.on("/speed/decrease", HTTP_POST, []() {
        send_command("speed_decrease"); 
    });
    server.on("/speed/increase", HTTP_POST, []() {
        send_command("speed_increase"); 
    });
    server.on("/speed/min", HTTP_POST, []() {
        send_command("speed_min"); 
    });
    server.on("/speed/max", HTTP_POST, []() {
        send_command("speed_max"); 
    });
    server.on("/light/all", HTTP_POST, []() {
        send_command("light_all"); 
    });
    server.on("/light/front", HTTP_POST, []() {
        send_command("light_front"); 
    });
    server.on("/light/back", HTTP_POST, []() {
        send_command("light_back"); 
    });
    server.on("/light/blink", HTTP_POST, []() {
        send_command("light_blink"); 
    });
    server.on("/light/off", HTTP_POST, []() {
        send_command("light_off"); 
    });

    server.begin();
    Serial.println("#SERVER_BEGIN");
}

void send_command(String command)
{
    Serial.print("#COMMAND ");
    Serial.println(command);
    server.send(200);
}

void loop() {
    server.handleClient();
}
