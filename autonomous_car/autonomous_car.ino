#include "car.hh"

Car *car;

void setup() 
{ 
    Serial1.begin(9600);
    car = new Car(150, 255, 52, 53, 50, 51);
}
 
void loop() 
{
    if (Serial1.available())
      car->do_action(Serial1.readStringUntil('\n'));
}
