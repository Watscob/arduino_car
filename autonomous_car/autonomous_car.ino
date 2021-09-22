#include "car.hh"
#include "wifi.hh"

Car *car;
CarWiFi *carWiFi;


void setup() 
{ 
    Serial.begin(9600);
    uint8_t led_front = 51;
    uint8_t led_back = 49;
    pinMode(led_front, OUTPUT);
    pinMode(led_back, OUTPUT);
    car = new Car(150, 255, led_front, led_back);
    carWiFi = new CarWiFi("Livebox-FBFC", "BonAnniv54");

    if (!carWiFi->connect())
        while(true)
            car->do_action(Action::ACTION_LIGHT_BLINK);

    car->do_action(Action::ACTION_LIGHT_READY);
    Serial.print("SSID: ");
    Serial.println(carWiFi->get_SSID());
    Serial.print("IP: ");
    Serial.println(carWiFi->get_IP());
}
 
void loop() 
{
    switch (carWiFi->recv_request())
    {
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
