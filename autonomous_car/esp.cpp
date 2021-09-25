#include "esp.hh"

#define UPDATE_SPEED 115200

ESPAdaptator::ESPAdaptator()
    : is_connected_(false)
    , SSID_("")
    , IP_()
    , request_()
{
    Serial3.begin(UPDATE_SPEED);

    Serial.println("Connecting ...");
    while (!this->is_connected_)
        this->process();
    Serial.println("Connected");

    // Get SSID
    this->process();
    Serial.println("Recv SSID");
    // Get IP
    this->process();
    Serial.println("Recv IP");
}

bool ESPAdaptator::is_connected()
{
    return this->is_connected_;
}

String ESPAdaptator::get_SSID()
{
    return this->SSID_;
}

String ESPAdaptator::get_IP()
{
    return this->IP_;
}

Request ESPAdaptator::get_request()
{
    if (this->request_)
    {
        Request res = this->request_;
        this->request_ = Request::REQUEST_UNDEFINED;
        Serial.print("--> ");
        Serial.println(res);
        return res;
    }
    return Request::REQUEST_UNDEFINED;
}

static Request command_to_request(String command)
{
    if (command == "move_forward")
        return Request::REQUEST_GO_FORWARD;
    else if (command == "move_backward")
        return Request::REQUEST_GO_BACKWARD;
    else if (command == "move_rotate_left")
        return Request::REQUEST_ROTATE_LEFT;
    else if (command == "move_rotate_right")
        return Request::REQUEST_ROTATE_RIGHT;
    else if (command == "move_stop")
        return Request::REQUEST_STOP;
    else if (command == "speed_decrease")
        return Request::REQUEST_SPEED_MINUS;
    else if (command == "speed_increase")
        return Request::REQUEST_SPEED_PLUS;
    else if (command == "speed_min")
        return Request::REQUEST_MIN_SPEED;
    else if (command == "speed_max")
        return Request::REQUEST_MAX_SPEED;
    else if (command == "light_all")
        return Request::REQUEST_LIGHT_ALL;
    else if (command == "light_front")
        return Request::REQUEST_LIGHT_FRONT;
    else if (command == "light_back")
        return Request::REQUEST_LIGHT_BACK;
    else if (command == "light_blink")
        return Request::REQUEST_LIGHT_BLINK;
    else if (command == "light_off")
        return Request::REQUEST_LIGHT_OFF;
    else
        return Request::REQUEST_UNDEFINED;
}

void ESPAdaptator::process()
{
    String request;

    String request_type;
    String request_arg;

    while (Serial3.peek() != '#')
        Serial3.read();
    Serial3.read();

    request = Serial3.readStringUntil('\r');
    
    Serial.print("request '");
    Serial.print(request);
    Serial.println("'");

    if (request.indexOf(' ') != -1)
    {
        request_type = request.substring(0, request.indexOf(' '));
        request_arg = request.substring(request.indexOf(' ') + 1);
    }
    else
        request_type = request;

    Serial.print("request_type '");
    Serial.print(request_type);
    Serial.println("'");
    Serial.print("request_arg '");
    Serial.print(request_arg);
    Serial.println("'");

    if (request_type.equals("CONNECTED"))
        this->is_connected_ = true;
    else if (request_type.equals("SSID"))
        this->SSID_  = request_arg;
    else if (request_type.equals("IP"))
        this->IP_ = request_arg;
    else if (request_type.equals("COMMAND"))
        this->request_ = command_to_request(request_arg);
}
