/*#include "car.h"

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
}*/

#include "car.h"

Car *car;

 
void setup() 
{
    // communication with the host computer
    Serial.begin(9600);   
 
    // communication with the BT module on serial1
    Serial1.begin(9600);

    car = new Car(0);
    car->set_speed(200);
    car->set_direction(RELEASE);
}
 
 
void loop() 
{
    // listen for communication from the BT module and then write it to the serial monitor
    //if ( Serial1.available() )   {  Serial.write( Serial1.read() );  }
 
    // listen for user input and send it to the HC-05
    //if ( Serial.available() )   {  Serial1.write( Serial.read() );  }
    //Serial1.write("Ici HC-05 !\n");
    //delay(1000);

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
          car->rotate_left();
          break;
        case 'R':
          car->rotate_right();
          break;
        default:
          car->set_direction(RELEASE);
          break;
      }
    }
}
