#include <Time.h>
#include <TimeAlarms.h>
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

/*
class Prescription {
  boolean days[7]; //Days per week to take prescription
  int hour; //Hour to take prescription
  int minute; //Minute to take prescription
};
*/ 

void setCurrentDateTime(Adafruit_ILI9341 tft, Adafruit_FT6206 ctp);
void digitalClockDisplay();
void printDigits(int digits);
void printAlarm();


void setup() {
  Serial.begin(115200);
  Serial.println(F("Get Current Date"));
  
  tft.begin();
  tft.setRotation(3);

  if(!ctp.begin(40)){  // pass in 'sensitivity' coefficient
    Serial.println("Couldn't start FT6206 touchscreen controller");
    while (1);
  }

  Serial.println("Capacitive touchscreen started");
  
  tft.fillScreen(ILI9341_BLACK);
  setCurrentDateTime(tft, ctp);
  tft.fillScreen(ILI9341_BLACK);
}

void loop() {
  if((second() != 0 )&& (second() % 7 == 0)){
    Serial.println("Alarm Set");
    Alarm.alarmRepeat(hour(), minute(), second()+10, printAlarm);
  }
  digitalClockDisplay();
  Alarm.delay(1000);
}

void setCurrentDateTime(Adafruit_ILI9341 tft, Adafruit_FT6206 ctp){
  String thingsToGet[5] = {
    "year", "month", "day", "hour", "minute"
  };
  String request = "Please enter the current ";
  int dateTimeData[5] = {2018, 4, 1, 12, 0};
  for(int i = 0; i < sizeof(dateTimeData)/sizeof(int); i++){
    dateTimeData[i] = getNumFromKeypad(tft, ctp, request, thingsToGet[i]);
    Serial.print(thingsToGet[i]); Serial.println(dateTimeData[i]);
  }
  // set the current time. This is out of order since setTime takes hours, minutes, seconds, days, months, year
  setTime(dateTimeData[3], dateTimeData[4], 0, dateTimeData[2], dateTimeData[1], dateTimeData[0]);
}

// Print the current time to serial
void digitalClockDisplay(){
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.println(); 
}

void printDigits(int digits){
  Serial.print(":");
  // put a leading zero on numbers under 10
  if(digits < 10){
    Serial.print('0');
  }
  Serial.print(digits);
}

void printAlarm(){
  Serial.println("An Alarm is going off");
}

