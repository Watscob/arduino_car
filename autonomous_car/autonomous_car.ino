#include "car.hh"
#include "wifi.hh"

Car *car;
CarWiFi *carWiFi;


void setup() 
{ 
    car = new Car(150, 255, 52, 53, 50, 51);
    carWiFi = new CarWiFi("Livebox-FBFC", "BonAnniv54");

    if (!carWiFi->connect())
        while(true) {}
}
 
void loop() 
{
    switch (carWiFi->recv_request())
    {
        case Request::SPEED_PLUS:
            car->do_action(Action::SPEED_PLUS);
            break;
        case Request::SPEED_MINUS:
            car->do_action(Action::SPEED_MINUS);
            break;
        case Request::MIN_SPEED:
            car->do_action(Action::MIN_SPEED);
            break;
        case Request::MAX_SPEED:
            car->do_action(Action::MAX_SPEED);
            break;
        case Request::GO_FORWARD:
            car->do_action(Action::GO_FORWARD);
            break;
        case Request::GO_BACKWARD:
            car->do_action(Action::GO_BACKWARD);
            break;
        case Request::ROTATE_LEFT:
            car->do_action(Action::ROTATE_LEFT);
            break;
        case Request::ROTATE_RIGHT:
            car->do_action(Action::ROTATE_RIGHT);
            break;
        case Request::STOP:
            car->do_action(Action::STOP);
            break;
        case Request::LIGHT_ALL:
            car->do_action(Action::LIGHT_ALL);
            break;
        case Request::LIGHT_FRONT:
            car->do_action(Action::LIGHT_FRONT);
            break;
        case Request::LIGHT_BACK:
            car->do_action(Action::LIGHT_BACK);
            break;
        case Request::LIGHT_OFF:
            car->do_action(Action::LIGHT_OFF);
            break;
        case Request::LIGHT_BLINK:
            car->do_action(Action::LIGHT_BLINK);
            break;
        default:
            break;
    }
}
