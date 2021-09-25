#include "car.hh"
#include "esp.hh"

#define UPDATE_SPEED 115200

Car *car;
ESPAdaptator *esp;

String car_SSID, car_IP, arg;
bool is_connected = false;

void setup() {
    Serial.begin(UPDATE_SPEED);
    Serial3.begin(UPDATE_SPEED);

    uint8_t led_front = 51;
    uint8_t led_back = 49;
    
    car = new Car(150, 255, led_front, led_back);
    esp = new ESPAdaptator(UPDATE_SPEED);
}

void loop() {
    Serial.println("LOOP");
    Request current_request = esp->read_wifi(&arg);
    Serial.println(current_request);

    if (!is_connected)
    {
        if (current_request == Request::REQUEST_CONNECTED)
        {
            is_connected = true;
            car->do_action(Action::ACTION_LIGHT_READY);
            Serial.println("CONNECTED");
        }
    }
    else
    {
        switch (current_request)
        {
            case Request::REQUEST_GET_SSID:
                car_SSID = arg;
                Serial.print("SSID: ");
                Serial.println(car_SSID);
                break;
            case Request::REQUEST_GET_IP:
                car_IP = arg;
                Serial.print("IP: ");
                Serial.println(car_IP);
                break;
            case Request::REQUEST_SPEED_PLUS:
                car->do_action(Action::ACTION_SPEED_PLUS);
                break;
            case Request::REQUEST_SPEED_MINUS:
                car->do_action(Action::ACTION_SPEED_MINUS);
                break;
            case Request::REQUEST_MIN_SPEED:
                car->do_action(Action::ACTION_MIN_SPEED);
                break;
            case Request::REQUEST_MAX_SPEED:
                car->do_action(Action::ACTION_MAX_SPEED);
                break;
            case Request::REQUEST_GO_FORWARD:
                car->do_action(Action::ACTION_GO_FORWARD);
                break;
            case Request::REQUEST_GO_BACKWARD:
                car->do_action(Action::ACTION_GO_BACKWARD);
                break;
            case Request::REQUEST_ROTATE_LEFT:
                car->do_action(Action::ACTION_ROTATE_LEFT);
                break;
            case Request::REQUEST_ROTATE_RIGHT:
                car->do_action(Action::ACTION_ROTATE_RIGHT);
                break;
            case Request::REQUEST_STOP:
                car->do_action(Action::ACTION_STOP);
                break;
            case Request::REQUEST_LIGHT_ALL:
                car->do_action(Action::ACTION_LIGHT_ALL);
                break;
            case Request::REQUEST_LIGHT_FRONT:
                car->do_action(Action::ACTION_LIGHT_FRONT);
                break;
            case Request::REQUEST_LIGHT_BACK:
                car->do_action(Action::ACTION_LIGHT_BACK);
                break;
            case Request::REQUEST_LIGHT_OFF:
                car->do_action(Action::ACTION_LIGHT_OFF);
                break;
            case Request::REQUEST_LIGHT_BLINK:
                car->do_action(Action::ACTION_LIGHT_BLINK);
                break;
            default:
                break;
        }
    }
}
