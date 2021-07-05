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

                if (this->buf_.endsWith("POST /speed/increase"))
                    request = Request::SPEED_PLUS;
                else if (this->buf_.endsWith("/speed/decrease"))
                    request = Request::SPEED_MINUS;
                else if (this->buf_.endsWith("POST /speed/min"))
                    request = Request::MIN_SPEED;
                else if (this->buf_.endsWith("POST /speed/max"))
                    request = Request::MAX_SPEED;
                else if (this->buf_.endsWith("POST /move/forward"))
                    request = Request::GO_FORWARD;
                else if (this->buf_.endsWith("POST /move/backward"))
                    request = Request::GO_BACKWARD;
                else if (this->buf_.endsWith("POST /move/rotate/left"))
                    request = Request::ROTATE_LEFT;
                else if (this->buf_.endsWith("POST /move/rotate/right"))
                    request = Request::ROTATE_RIGHT;
                else if (this->buf_.endsWith("POST /move/stop"))
                    request = Request::STOP;
                else if (this->buf_.endsWith("POST /light/all"))
                    request = Request::LIGHT_ALL;
                else if (this->buf_.endsWith("POST /light/front"))
                    request = Request::LIGHT_FRONT;
                else if (this->buf_.endsWith("POST /light/back"))
                    request = Request::LIGHT_BACK;
                else if (this->buf_.endsWith("POST /light/off"))
                    request = Request::LIGHT_OFF;
                else if (this->buf_.endsWith("POST /light/blink"))
                    request = Request::LIGHT_BLINK;
            }
        }

        client.stop();
    }

    return request;
}

void CarWiFi::send_response_(WiFiEspClient client)
{
    client.println("HTTP/1.1 200 OK");
    client.println();
    client.println();
}