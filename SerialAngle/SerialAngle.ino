#include <Servo.h>

Servo servo;
int pos = 0;
int speed = 5;

void setup() {
  servo.attach(3);
  Serial.begin(9600);

}

void loop() {
  byte angle;

  if(Serial.available()){
    angle = Serial.parseInt();
      servo.write(angle);
      Serial.println(angle);
      delay(1000);
  }
}
