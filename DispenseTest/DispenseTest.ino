#include <Servo.h>
#include <Arduino.h>

int servoPin = 3;
int numPills = 10;

Servo servo;

void dispense(Servo servo, int numPills);

void setup() {
  servo.attach(servoPin);
  servo.write(0);
}

void loop() {
  dispense(servo, numPills);
  delay(1000);
}


void dispense(Servo servo, int numPills){
  for (int i = 0; i < numPills; i++) {
    // Shake the gear at the bottom to make sure a pill is in
    servo.write(0);
    servo.write(15);
    servo.write(0);
    servo.write(15);
    servo.write(0);
    // Take the pill to the top
    servo.write(180);
  }
    servo.write(0);
}
