#include "car.h"

Car *car;

void setup()
{
  car = new Car(0);
  car->set_speed(200);
  car->set_direction(RELEASE);
}

void loop()
{
  car->set_direction(FORWARD);
  car->set_speed(153);
  delay(1000);
  car->set_speed(255);
  delay(1000);
  car->set_direction(RELEASE);
  delay(1000);
  car->set_direction(BACKWARD);
  car->set_speed(153);
  delay(1000);
  car->set_speed(255);
  delay(1000);
  car->set_direction(RELEASE);
  delay(1000);
}
