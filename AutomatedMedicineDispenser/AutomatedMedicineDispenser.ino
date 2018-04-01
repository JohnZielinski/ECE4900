//#include <Time.h>
//#include <TimeAlarms.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <SPI.h>       // this is needed for display
#include <Adafruit_ILI9341.h>
#include <Wire.h>      // this is needed for FT6206
#include <Adafruit_FT6206.h>
#include "Keypad.h"

// The FT6206 uses hardware I2C (SCL/SDA)
Adafruit_FT6206 ctp = Adafruit_FT6206();

// The display also uses hardware SPI, plus #9 & #10
#define TFT_CS 10
#define TFT_DC 9
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

class Prescription {
  boolean days[7]; //Days per week to take prescription
  int hour; //Hour to take prescription
  int minute; //Minute to take prescription
};


void setup() {
  Serial.begin(115200);
  Serial.println(F("Get Current Date"));
  
  tft.begin();
  tft.setRotation(3);

  if (! ctp.begin(40)) {  // pass in 'sensitivity' coefficient
    Serial.println("Couldn't start FT6206 touchscreen controller");
    while (1);
  }

  Serial.println("Capacitive touchscreen started");
  
  tft.fillScreen(ILI9341_BLACK);
  // Get the current day
  int year = getNumFromKeypad(tft, ctp, "year");
  int month = getNumFromKeypad(tft, ctp, "month");
  int day = getNumFromKeypad(tft, ctp, "day");
  int hour = getNumFromKeypad(tft, ctp, "hour");
  int minute = getNumFromKeypad(tft, ctp, "minute");
  Serial.print("Year: "); Serial.println(year);
  Serial.print("Month: "); Serial.println( month);
  Serial.print("Day: "); Serial.println(day);
  Serial.print("Hour: "); Serial.println(hour);
  Serial.print("Minute: "); Serial.println(minute);

}

void loop() {
  delay(1000);
}
