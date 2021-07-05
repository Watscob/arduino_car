#include "car.hh"

Car *car;

void setup() 
{ 
    car = new Car(150, 255, 52, 53, 50, 51);
}
 
void loop() 
{
    car->do_action(Action::STOP);
}
