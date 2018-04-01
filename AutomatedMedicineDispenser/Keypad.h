#include <Adafruit_GFX.h>    // Core graphics library
#include <SPI.h>       // this is needed for display
#include <Adafruit_ILI9341.h>
#include <Wire.h>      // this is needed for FT6206
#include <Adafruit_FT6206.h>

// Function Prototypes
TS_Point getMappedPoint(Adafruit_FT6206 ctp);
char getInputValue(Adafruit_FT6206 ctp);
void drawKeyboard(Adafruit_ILI9341 tft);
int getNumFromKeypad(Adafruit_ILI9341 tft, Adafruit_FT6206 ctp, String str);
