#include "esp.hh"

ESPAdaptator::ESPAdaptator(long update_speed)
{
    Serial3.begin(update_speed);
}

static Request command_to_request(String command)
{
    if (command.equals("move_forward"))
        return Request::REQUEST_GO_FORWARD;
    else if (command.equals("move_backward"))
        return Request::REQUEST_GO_BACKWARD;
    else if (command.equals("move_rotate_left"))
        return Request::REQUEST_ROTATE_LEFT;
    else if (command.equals("move_rotate_right"))
        return Request::REQUEST_ROTATE_RIGHT;
    else if (command.equals("move_stop"))
        return Request::REQUEST_STOP;
    else if (command.equals("speed_decrease"))
        return Request::REQUEST_SPEED_MINUS;
    else if (command.equals("speed_increase"))
        return Request::REQUEST_SPEED_PLUS;
    else if (command.equals("speed_min"))
        return Request::REQUEST_MIN_SPEED;
    else if (command.equals("speed_max"))
        return Request::REQUEST_MAX_SPEED;
    else if (command.equals("light_all"))
        return Request::REQUEST_LIGHT_ALL;
    else if (command.equals("light_front"))
        return Request::REQUEST_LIGHT_FRONT;
    else if (command.equals("light_back"))
        return Request::REQUEST_LIGHT_BACK;
    else if (command.equals("light_blink"))
        return Request::REQUEST_LIGHT_BLINK;
    else if (command.equals("light_off"))
        return Request::REQUEST_LIGHT_OFF;
    else
        return Request::REQUEST_UNDEFINED;
}

Request ESPAdaptator::read_wifi(String *arg)
{
    String request, request_arg;

    while (Serial3.peek() != '#')
        Serial3.read();
    Serial3.read();

    request = Serial3.readStringUntil('\r');

    int index_space = request.indexOf(' ');
    if (index_space != -1)
    {
        request_arg = request.substring(index_space + 1);
        request = request.substring(0, index_space);
    }

    Serial.print("REQUEST '");
    Serial.print(request);
    Serial.println("'");
    Serial.print("ARG '");
    Serial.print(request_arg);
    Serial.println("'");

    if (request.equals("CONNECTED"))
        return Request::REQUEST_CONNECTED;
    else if (request.equals("SSID"))
    {
        *arg = request_arg;
        return Request::REQUEST_GET_SSID;
    }
    else if (request.equals("IP"))
    {
        *arg = request_arg;
        return Request::REQUEST_GET_IP;
    }
    else if (request.equals("COMMAND"))
        return command_to_request(request_arg);
    else
        return Request::REQUEST_UNDEFINED;
}
