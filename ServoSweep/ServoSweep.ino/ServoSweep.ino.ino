#include <Servo.h>

Servo servo;
int pos = 0;
int speed = 5;
void setup() {
servo.attach(9);
}

void loop() {
for(pos = 0; pos <= 180; pos++){
  servo.write(pos);
  delay(speed);
}
for(pos = 180; pos >= 0; pos--){
  servo.write(pos);
  delay(speed);
}
}
