#include <Adafruit_GFX.h>    // Core graphics library
#include <SPI.h>       // this is needed for display
#include <Adafruit_ILI9341.h>
#include <Wire.h>      // this is needed for FT6206
#include <Adafruit_FT6206.h>

// The FT6206 uses hardware I2C (SCL/SDA)
Adafruit_FT6206 ctp = Adafruit_FT6206();

// The display also uses hardware SPI, plus #9 & #10
#define TFT_CS 10
#define TFT_DC 9
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

// Size of the color selection boxes and the paintbrush size
#define NUMPADBOXSIZE 320/5
#define DAYBOXSIZE 320/8
#define PENRADIUS 3
#define NUMTEXTSIZE 3
#define TEXTSIZE 2
int oldcolor, currentcolor;

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
  tft.setTextSize(TEXTSIZE);
  tft.setTextColor(ILI9341_WHITE);

  tft.setCursor(0,0);
  tft.println("Please enter the date:");

  tft.setTextSize(NUMTEXTSIZE);
  // make keypad selection boxes
  for(int i = 0; i < 5; i++){
    // Draw 0-4
    tft.drawRect(NUMPADBOXSIZE*(i), 240-NUMPADBOXSIZE*2, NUMPADBOXSIZE, NUMPADBOXSIZE, ILI9341_WHITE);
    tft.setCursor(NUMPADBOXSIZE*(i)+(NUMPADBOXSIZE/2-NUMTEXTSIZE/2), 240-NUMPADBOXSIZE*2+(NUMPADBOXSIZE/2));
    tft.println(i);
    // Draw 5-9
    tft.drawRect(NUMPADBOXSIZE*(i), 240-NUMPADBOXSIZE, NUMPADBOXSIZE, NUMPADBOXSIZE, ILI9341_WHITE);
    tft.setCursor(NUMPADBOXSIZE*(i)+(NUMPADBOXSIZE/2-NUMTEXTSIZE/2), 240-NUMPADBOXSIZE+(NUMPADBOXSIZE/2));
    tft.println(i+4);
  }
  
  // make day selection boxes, plus DEL box
  tft.setTextSize(TEXTSIZE);
  for(int i = 0; i<8; i++){
    tft.drawRect(DAYBOXSIZE*(i), 240-(NUMPADBOXSIZE*2+DAYBOXSIZE), DAYBOXSIZE, DAYBOXSIZE, ILI9341_WHITE);
  }
  // fill in days and DEL
  char days[8][4] = {"M", "TU", "W", "TH", "F", "Sa", "Su", "DEL"};
  for(int i = 0; i < 8; i++){
    tft.setCursor(DAYBOXSIZE*i + 3, 240-(NUMPADBOXSIZE*2+DAYBOXSIZE)+(DAYBOXSIZE/2));
    tft.println(days[i]);
  }
}

void loop() {
    // Wait for a touch
  if (! ctp.touched()) {
    return;
  }

    // Retrieve a point  
  TS_Point p = ctp.getPoint();

    // flip it around to match the screen.
  p.x = map(p.x, 0, 240, 240, 0);
  p.y = map(p.y, 0, 320, 320, 0);

  // Print out the remapped (rotated) coordinates
  Serial.print("("); Serial.print(p.x);
  Serial.print(", "); Serial.print(p.y);
  Serial.println(")");
    if (p.y < NUMPADBOXSIZE) {
     oldcolor = currentcolor;

     if (p.x < NUMPADBOXSIZE) { 
       currentcolor = ILI9341_RED; 
       tft.drawRect(0, 0, NUMPADBOXSIZE, NUMPADBOXSIZE, ILI9341_WHITE);
     } else if (p.x < NUMPADBOXSIZE*2) {
       currentcolor = ILI9341_YELLOW;
       tft.drawRect(NUMPADBOXSIZE, 0, NUMPADBOXSIZE, NUMPADBOXSIZE, ILI9341_WHITE);
     } else if (p.x < NUMPADBOXSIZE*3) {
       currentcolor = ILI9341_GREEN;
       tft.drawRect(NUMPADBOXSIZE*2, 0, NUMPADBOXSIZE, NUMPADBOXSIZE, ILI9341_WHITE);
     } else if (p.x < NUMPADBOXSIZE*4) {
       currentcolor = ILI9341_CYAN;
       tft.drawRect(NUMPADBOXSIZE*3, 0, NUMPADBOXSIZE, NUMPADBOXSIZE, ILI9341_WHITE);
     } else if (p.x < NUMPADBOXSIZE*5) {
       currentcolor = ILI9341_BLUE;
       tft.drawRect(NUMPADBOXSIZE*4, 0, NUMPADBOXSIZE, NUMPADBOXSIZE, ILI9341_WHITE);
     } else if (p.x <= NUMPADBOXSIZE*6) {
       currentcolor = ILI9341_MAGENTA;
       tft.drawRect(NUMPADBOXSIZE*5, 0, NUMPADBOXSIZE, NUMPADBOXSIZE, ILI9341_WHITE);
     }

     if (oldcolor != currentcolor) {
        if (oldcolor == ILI9341_RED) 
          tft.fillRect(0, 0, NUMPADBOXSIZE, NUMPADBOXSIZE, ILI9341_RED);
        if (oldcolor == ILI9341_YELLOW) 
          tft.fillRect(NUMPADBOXSIZE, 0, NUMPADBOXSIZE, NUMPADBOXSIZE, ILI9341_YELLOW);
        if (oldcolor == ILI9341_GREEN) 
          tft.fillRect(NUMPADBOXSIZE*2, 0, NUMPADBOXSIZE, NUMPADBOXSIZE, ILI9341_GREEN);
        if (oldcolor == ILI9341_CYAN) 
          tft.fillRect(NUMPADBOXSIZE*3, 0, NUMPADBOXSIZE, NUMPADBOXSIZE, ILI9341_CYAN);
        if (oldcolor == ILI9341_BLUE) 
          tft.fillRect(NUMPADBOXSIZE*4, 0, NUMPADBOXSIZE, NUMPADBOXSIZE, ILI9341_BLUE);
        if (oldcolor == ILI9341_MAGENTA) 
          tft.fillRect(NUMPADBOXSIZE*5, 0, NUMPADBOXSIZE, NUMPADBOXSIZE, ILI9341_MAGENTA);
     }
  }
  if (((p.y-PENRADIUS) > NUMPADBOXSIZE) && ((p.y+PENRADIUS) < tft.height())) {
    tft.fillCircle(p.x, p.y, PENRADIUS, currentcolor);
  }
}
