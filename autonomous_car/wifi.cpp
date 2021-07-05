#include "wifi.hh"

#define UPDATE_SPEED 115200

CarWiFi::CarWiFi(char ssid[], char pass[])
    : ssid_(ssid)
    , pass_(pass)
    , status_(WL_IDLE_STATUS)
    , buf_(8)
    , server_(80)
{}

bool CarWiFi::connect() {
    Serial3.begin(UPDATE_SPEED);
    WiFi.init(&Serial3);

    if (WiFi.status() == WL_NO_SHIELD)
        return false;

    while (this->status_ != WL_CONNECTED)
        this->status_ = WiFi.begin(this->ssid_, this->pass_);

    this->server_.begin();
    return true;
}

String CarWiFi::get_SSID()
{
    return WiFi.SSID();
}

IPAddress CarWiFi::get_IP()
{
    return WiFi.localIP();
}

bool CarWiFi::is_connected()
{
    return WiFi.status() == WL_CONNECTED;
}

void CarWiFi::send_response(WiFiEspClient client)
{
    client.println("HTTP/1.1 200 OK");
    client.println();
    client.println();
}

Request CarWiFi::recv_request()
{
    Request request = Request::UNDEFINED;
    WiFiEspClient client = this->server_.available();
    if (client)
    {
        this->buf_.init();

        while (client.connected())
        {
            if (client.available())
            {
                char c = client.read();
                this->buf_.push(c);

                if (this->buf_.endsWith("\r\n\r\n"))
                {
                    send_response(client);
                    break;
                }

                if (this->buf_.endsWith("GET /H"))
                    request = Request::UNDEFINED;
            }
        }

        client.stop();
    }

    return request;
}