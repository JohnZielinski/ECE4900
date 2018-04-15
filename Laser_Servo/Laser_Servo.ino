#include <Servo.h>

int laser_din1 = 1; /* Set Input Pin */
int laser_din2 = 2;
Servo servo;
int pills = 0;

void setup()
{
  servo.attach(3);
  pinMode(laser_din1, INPUT); /*Set Pin to input mode*/
  pinMode(laser_din2, INPUT);
  Serial.begin(9600);
}
void loop()
{
  while(pills < 5){
    Serial.print(pills);
    Serial.println(" pills dispensed");
    servo.write(0);
    for (int pos = 0; pos <= 180; pos++){
      servo.write(pos);
      if((digitalRead(laser_din1) == HIGH) || (digitalRead(laser_din2) == HIGH)) {
        Serial.println("No Pill yet");
      } else {
        Serial.println("A pill was detected");
        delay(1000);
        pills++;
        break;
      }
    }
    servo.write(180);
  }
  Serial.println("All pills dispensed");
  delay(1000);
}
