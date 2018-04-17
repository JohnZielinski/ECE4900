#include <Servo.h>
#include <Arduino.h>

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
    delay(1000);
    // Below is for reading a lasor sensor, not used though
    /*
    unsigned long timeNow = millis();
    unsigned long readForTime = 2000; // Read for 5 seconds
    while(millis() - timeNow < readForTime){
      if (digitalread(laser_pin == LOW){
        Serial.println("Pill Detected");
      }
    }
    */
  }
    servo.write(0);
}
