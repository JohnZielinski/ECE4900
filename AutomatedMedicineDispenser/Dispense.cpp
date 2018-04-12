#include <Servo.h>
#include <Arduino.h>

#define PILLDETECTED LOW

void dispense(Servo servo, int numPills, int laser_in) {
  int numDispensed = 0;
  while (numDispensed < numPills) {
    bool pillDispensed = false;
    int pos = 0;
    while (!pillDispensed) {
      // Turn servo, checking for a pill every degree
      servo.write(pos);
      if (digitalRead(laser_in == PILLDETECTED)) {
        numDispensed++;
        pillDispensed = true;
      }
      if (pos < 180) {
        pos++;
      } else {
        pos = 0;
      }
    }
    servo.write(0);
  }
}
