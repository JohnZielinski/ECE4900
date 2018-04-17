#include <Servo.h>
#include <Arduino.h>

int servoPin = 9;
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
    for (int j = 0; j < 5; j++){
      servo.write(0);
      delay(300);
      servo.write(30);
      delay(300);
    }
    servo.write(0);
    delay(500);
    // Take the pill to the top
    servo.write(180);
    unsigned long timeNow = millis();
    unsigned long readForTime = 2000; // Read for 5 seconds
    while(millis() - timeNow < readForTime){
//      if (digitalread(laser_pin == LOW){
        //Serial.println("Pill Detected");
      //}
    }
  }
    servo.write(0);
}
