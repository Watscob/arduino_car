#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266mDNS.h>
#include <ESP8266WiFiMulti.h> 

#include "index.hh"

#define UPDATE_SPEED 115200

ESP8266WiFiMulti wifiMulti;
ESP8266WebServer server(80);

void setup() {
    Serial.begin(UPDATE_SPEED);

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
    server.onNotFound([]() {
        server.send(404, "text/plain", "404: Not found");
    });
    server.on("/command", HTTP_POST, []() {
        if (!server.hasArg("action") || server.arg("action") == NULL)
        {
            server.send(400, "text/plain", "400: Requête invalide");
            return;
        }

        send_command(server.arg("action"));
        server.send(200);
    });

    server.begin();
    Serial.println("#SERVER_BEGIN");
}

void send_command(String command)
{
    Serial.print("#COMMAND ");
    Serial.println(command);
}

void loop() {
    server.handleClient();
}
