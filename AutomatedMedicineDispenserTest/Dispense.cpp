#include <Servo.h>
#include <Arduino.h>
#include <Time.h>
#include <TimeAlarms.h>

void dispense(Servo servo, int numPills, int buzzerPin){
  tone(buzzerPin, 1500, 5000);
  for (int i = 0; i < numPills; i++) {
    // Shake the gear at the bottom to make sure a pill is in
    for (int j = 0; j < 5; j++){
      servo.write(0);
      Alarm.delay(300);
      servo.write(30);
      Alarm.delay(300);
    }
    servo.write(0);
    Alarm.delay(500);
    // Take the pill to the top
    servo.write(180);
    Alarm.delay(1000);
  }
    servo.write(0);
}
