#include "wifi.hh"

#define UPDATE_SPEED 115200

CarWiFi::CarWiFi(char const *ssid, char const *pass)
    : ssid_(ssid)
    , pass_(pass)
    , status_(WL_IDLE_STATUS)
    , buf_(32)
    , server_(80)
{}

bool CarWiFi::connect()
{
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
    Request request = Request::REQUEST_UNDEFINED;
    WiFiEspClient client = this->server_.available();
    if (client)
    {
        this->buf_.init();
        char c;
        char buf[20];

        Serial.println("-- Client connected --");

        while (client.connected())
        {
            if (client.available())
            {
                c = client.read();
                this->buf_.push(c);
                this->buf_.getStr(buf, 0);

                if (this->buf_.endsWith("\r\n\r\n"))
                    break;
                else if (this->buf_.endsWith("POST /speed/increase"))
                {
                    request = Request::REQUEST_SPEED_PLUS;
                    break;
                }
                else if (this->buf_.endsWith("/speed/decrease"))
                {
                    request = Request::REQUEST_SPEED_MINUS;
                    break;
                }
                else if (this->buf_.endsWith("POST /speed/min"))
                {
                    request = Request::REQUEST_MIN_SPEED;
                    break;
                }
                else if (this->buf_.endsWith("POST /speed/max"))
                {
                    request = Request::REQUEST_MAX_SPEED;
                    break;
                }
                else if (this->buf_.endsWith("POST /move/forward"))
                {
                    request = Request::REQUEST_GO_FORWARD;
                    break;
                }
                else if (this->buf_.endsWith("POST /move/backward"))
                {
                    request = Request::REQUEST_GO_BACKWARD;
                    break;
                }
                else if (this->buf_.endsWith("POST /move/rotate/left"))
                {
                    request = Request::REQUEST_ROTATE_LEFT;
                    break;
                }
                else if (this->buf_.endsWith("POST /move/rotate/right"))
                {
                    request = Request::REQUEST_ROTATE_RIGHT;
                    break;
                }
                else if (this->buf_.endsWith("POST /move/stop"))
                {
                    request = Request::REQUEST_STOP;
                    break;
                }
                else if (this->buf_.endsWith("POST /light/all"))
                {
                    request = Request::REQUEST_LIGHT_ALL;
                    break;
                }
                else if (this->buf_.endsWith("POST /light/front"))
                {
                    request = Request::REQUEST_LIGHT_FRONT;
                    break;
                }
                else if (this->buf_.endsWith("POST /light/back"))
                {
                    request = Request::REQUEST_LIGHT_BACK;
                    break;
                }
                else if (this->buf_.endsWith("POST /light/off"))
                {
                    request = Request::REQUEST_LIGHT_OFF;
                    break;
                }
                else if (this->buf_.endsWith("POST /light/blink"))
                {
                    request = Request::REQUEST_LIGHT_BLINK;
                    break;
                }
            }
        }
        
        send_response_(client);
        client.stop();
        Serial.println("-- Client disconnected --");
    }

    return request;
}

void CarWiFi::send_response_(WiFiEspClient client)
{
    client.print("HTTP/1.1 200 OK\r\n\r\n");
}
