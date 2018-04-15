#include <Servo.h>
#include <Arduino.h>

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
