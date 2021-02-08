#include "car.h"

Car *car;

void setup() 
{ 
    Serial1.begin(9600);

    car = new Car(0);
    car->set_speed(180);
    car->set_direction(RELEASE);
}
 
 
void loop() 
{
    if (Serial1.available())
    {
      char c = Serial1.read();
      switch(c)
      {
        case '+':
          car->set_speed_off(5);
          break;
        case '-':
          car->set_speed_off(-5);
          break;
        case 'U':
          car->set_direction(FORWARD);
          break;
        case 'D':
          car->set_direction(BACKWARD);
          break;
        case 'L':
          car->turn_left();
          break;
        case 'R':
          car->turn_right();
          break;
        case 'T':
          car->reset_turn();
          break;
        case 'l':
          car->rotate_left();
          break;
        case 'r':
          car->rotate_right();
          break;
        default:
          car->set_direction(RELEASE);
          break;
      }
    }
}
