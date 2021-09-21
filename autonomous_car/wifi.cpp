#include "wifi.hh"

#define UPDATE_SPEED 115200
String index = "<!DOCTYPE html><html lang=\"en\"><head><style>*{font-family:sans-serif}body,html{margin:0;padding:0}table,#page{margin-left:auto;margin-right:auto}legend{font-size:x-small;font-weight:normal;color:grey}td>form>button{width:100\%;height:100%}body{height:20em}#page{width:max-content;margin-top:50vh;transform:translateY(-50%)}</style> <script src=\"https://kit.fontawesome.com/52ac5a2d37.js\" crossorigin=\"anonymous\"></script> <title>Arduino Car</title></head><body><div id=\"page\"><fieldset><legend>CONTROLS</legend><table><tr><td></td><td><form id=\"forward\" action=\"/move/forward\" method=\"post\" onsubmit=\"return false\"> <button type=\"submit\" class=\"btn btn-default\"><i class=\"fas fa-arrow-up\"></i></button></form></td><td></td></tr><tr><td><form id=\"rotate_left\" action=\"/move/rotate/left\" method=\"post\" onsubmit=\"return false\"> <button type=\"submit\" class=\"btn btn-default\"><i class=\"fas fa-arrow-left\"></i></button></form></td><td><form id=\"stop\" action=\"/move/stop\" method=\"post\" onsubmit=\"return false\"> <button type=\"submit\" class=\"btn btn-default\"><i class=\"fas fa-times\"></i></button></form></td><td><form id=\"rotate_right\" action=\"/move/rotate/right\" method=\"post\" onsubmit=\"return false\"> <button type=\"submit\" class=\"btn btn-default\"><i class=\"fas fa-arrow-right\"></i></button></form></td></tr><tr><td></td><td><form id=\"backward\" action=\"/move/backward\" method=\"post\" onsubmit=\"return false\"> <button type=\"submit\" class=\"btn btn-default\"><i class=\"fas fa-arrow-down\"></i></button></form></td><td></td></tr></table></fieldset><fieldset><legend>SPEED</legend><table><tr><td><form id=\"speed_decrease\" action=\"/speed/decrease\" method=\"post\" onsubmit=\"return false\"> <button type=\"submit\" class=\"btn btn-default\"><i class=\"fas fa-minus\"></i></button></form></td><td><form id=\"speed_increase\" action=\"/speed/increase\" method=\"post\" onsubmit=\"return false\"> <button type=\"submit\" class=\"btn btn-default\"><i class=\"fas fa-plus\"></i></button></form></td><td><form id=\"min_speed\" action=\"/speed/min\" method=\"post\" onsubmit=\"return false\"> <button type=\"submit\" class=\"btn btn-default\">MIN</button></form></td><td><form id=\"max_speed\" action=\"/speed/max\" method=\"post\" onsubmit=\"return false\"> <button type=\"submit\" class=\"btn btn-default\">MAX</button></form></td></tr></table></fieldset><fieldset><legend>LIGHT</legend><table><tr><td><form id=\"light_all\" action=\"/light/all\" method=\"post\" onsubmit=\"return false\"> <button type=\"submit\" class=\"btn btn-default\">ON</button></form></td><td><form id=\"light_front\" action=\"/light/front\" method=\"post\" onsubmit=\"return false\"> <button type=\"submit\" class=\"btn btn-default\">FRONT</button></form></td><td><form id=\"light_back\" action=\"/light/back\" method=\"post\" onsubmit=\"return false\"> <button type=\"submit\" class=\"btn btn-default\">BACK</button></form></td><td><form id=\"light_blink\" action=\"/light/blink\" method=\"post\" onsubmit=\"return false\"> <button type=\"submit\" class=\"btn btn-default\">BLINK</button></form></td><td><form id=\"light_off\" action=\"/light/off\" method=\"post\" onsubmit=\"return false\"> <button type=\"submit\" class=\"btn btn-default\">OFF</button></form></td></tr></table></fieldset></div></body></html>";

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
    bool is_index = false;
    if (client)
    {
        this->buf_.init();

        while (client.connected())
        {
            if (client.available())
            {
                char c = client.read();
                this->buf_.push(c);
                Serial.print("BUF: ");
                char buf[20];
                this->buf_.getStr(buf, 0);
                Serial.println(buf);

                if (this->buf_.endsWith("\r\n\r\n"))
                {
                    send_response_(client, is_index);
                    break;
                }

                if (this->buf_.endsWith("GET /") || this->buf_.endsWith("GET /index.hmtl"))
                {
                    request = Request::REQUEST_UNDEFINED;
                    is_index = true;
                }
                else if (this->buf_.endsWith("POST /speed/increase"))
                    request = Request::REQUEST_SPEED_PLUS;
                else if (this->buf_.endsWith("/speed/decrease"))
                    request = Request::REQUEST_SPEED_MINUS;
                else if (this->buf_.endsWith("POST /speed/min"))
                    request = Request::REQUEST_MIN_SPEED;
                else if (this->buf_.endsWith("POST /speed/max"))
                    request = Request::REQUEST_MAX_SPEED;
                else if (this->buf_.endsWith("POST /move/forward"))
                    request = Request::REQUEST_GO_FORWARD;
                else if (this->buf_.endsWith("POST /move/backward"))
                    request = Request::REQUEST_GO_BACKWARD;
                else if (this->buf_.endsWith("POST /move/rotate/left"))
                    request = Request::REQUEST_ROTATE_LEFT;
                else if (this->buf_.endsWith("POST /move/rotate/right"))
                    request = Request::REQUEST_ROTATE_RIGHT;
                else if (this->buf_.endsWith("POST /move/stop"))
                    request = Request::REQUEST_STOP;
                else if (this->buf_.endsWith("POST /light/all"))
                    request = Request::REQUEST_LIGHT_ALL;
                else if (this->buf_.endsWith("POST /light/front"))
                    request = Request::REQUEST_LIGHT_FRONT;
                else if (this->buf_.endsWith("POST /light/back"))
                    request = Request::REQUEST_LIGHT_BACK;
                else if (this->buf_.endsWith("POST /light/off"))
                    request = Request::REQUEST_LIGHT_OFF;
                else if (this->buf_.endsWith("POST /light/blink"))
                    request = Request::REQUEST_LIGHT_BLINK;
            }
        }
        client.stop();
    }

    return request;
}

void CarWiFi::send_response_(WiFiEspClient client, bool is_index)
{
    if (!is_index)
    {
        client.print("HTTP/1.1 200 OK\r\n\r\n");
    }
    else
    {
        client.print("HTTP/1.1 200 OK\r\n");
        client.print("Content-type: text/html\r\n");
        client.print("Connection: close\r\n");
        client.print(index);
        client.print("\r\n");
    }
}
