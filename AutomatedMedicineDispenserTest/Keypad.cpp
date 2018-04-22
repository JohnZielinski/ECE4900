#include <Adafruit_GFX.h>    // Core graphics library
#include <SPI.h>       // this is needed for display
#include <Adafruit_ILI9341.h>
#include <Wire.h>      // this is needed for FT6206
#include <Adafruit_FT6206.h>

// Size of the color selection boxes and the paintbrush size
#define XMAX 320
#define YMAX 240
#define NUMPADBOXSIZE XMAX/5
#define NUMTEXTSIZE 3
#define TEXTSIZE 2
#define ENTER -1
#define DELETE -2

// x-min, x-max, y-min, y-max, value
int keypad[12][5] = {
  {0, NUMPADBOXSIZE, YMAX - NUMPADBOXSIZE, YMAX, 5},
  {NUMPADBOXSIZE, 2 * NUMPADBOXSIZE, YMAX - NUMPADBOXSIZE, YMAX, 6},
  {2 * NUMPADBOXSIZE, 3 * NUMPADBOXSIZE, YMAX - NUMPADBOXSIZE, YMAX, 7},
  {3 * NUMPADBOXSIZE, 4 * NUMPADBOXSIZE, YMAX - NUMPADBOXSIZE, YMAX, 8},
  {4 * NUMPADBOXSIZE, 5 * NUMPADBOXSIZE, YMAX - NUMPADBOXSIZE, YMAX, 9},
  {0, NUMPADBOXSIZE, YMAX - 2 * NUMPADBOXSIZE, YMAX - NUMPADBOXSIZE, 0},
  {NUMPADBOXSIZE, 2 * NUMPADBOXSIZE, YMAX - 2 * NUMPADBOXSIZE, YMAX - NUMPADBOXSIZE, 1},
  {2 * NUMPADBOXSIZE, 3 * NUMPADBOXSIZE, YMAX - 2 * NUMPADBOXSIZE, YMAX - NUMPADBOXSIZE, 2},
  {3 * NUMPADBOXSIZE, 4 * NUMPADBOXSIZE, YMAX - 2 * NUMPADBOXSIZE, YMAX - NUMPADBOXSIZE, 3},
  {4 * NUMPADBOXSIZE, 5 * NUMPADBOXSIZE, YMAX - 2 * NUMPADBOXSIZE, YMAX - NUMPADBOXSIZE, 4},
  {0, XMAX/2, YMAX - 3 * NUMPADBOXSIZE, YMAX - 2 * NUMPADBOXSIZE, -1},
  {XMAX/2, XMAX, YMAX - 3 * NUMPADBOXSIZE, YMAX - 2 * NUMPADBOXSIZE, -2}
};

void drawKeyboard(Adafruit_ILI9341 tft){
  // make keypad selection boxes
    // Draw 5-9
    for(int i = 0; i < 5; i++){
    // Draw 0-4
    tft.drawRect(NUMPADBOXSIZE * i, YMAX - (NUMPADBOXSIZE * 2), NUMPADBOXSIZE, NUMPADBOXSIZE, ILI9341_WHITE);
    tft.setCursor(NUMPADBOXSIZE * i + (NUMPADBOXSIZE / 2 - NUMTEXTSIZE / 2), YMAX - NUMPADBOXSIZE * 2 + (NUMPADBOXSIZE / 2));
    tft.println(i);
    // Draw 5-9
    tft.drawRect(NUMPADBOXSIZE * i, YMAX - NUMPADBOXSIZE, NUMPADBOXSIZE, NUMPADBOXSIZE, ILI9341_WHITE);
    tft.setCursor(NUMPADBOXSIZE * i + (NUMPADBOXSIZE / 2 - NUMTEXTSIZE / 2), YMAX - NUMPADBOXSIZE +(NUMPADBOXSIZE / 2));
    tft.println(i + 5);
    }
    // Draw Enter and Delete
    tft.drawRect(0, YMAX - 3 * NUMPADBOXSIZE, XMAX/2, NUMPADBOXSIZE, ILI9341_WHITE);
    tft.drawRect(XMAX/2, YMAX - 3 * NUMPADBOXSIZE, XMAX/2, NUMPADBOXSIZE, ILI9341_WHITE);
    tft.setCursor(0, YMAX - (3 * NUMPADBOXSIZE) + NUMPADBOXSIZE/2);
    tft.println("ENTER");
    tft.setCursor(XMAX/2+1, YMAX - (3 * NUMPADBOXSIZE) + NUMPADBOXSIZE/2);
    tft.println("DELETE");
}

TS_Point getMappedPoint(Adafruit_FT6206 ctp){
  // wait for input
  while(!ctp.touched()){}
    // Retrieve a point  
  TS_Point p = ctp.getPoint();
  TS_Point temp;
    // flip it around to match the screen.
  temp.y = map(p.x, 0, YMAX, YMAX, 0);
  temp.x = map(p.y, 0, XMAX, 0, XMAX);
  p.x = temp.x;
  p.y = temp.y;
  Serial.print("("); Serial.print(p.x);
  Serial.print(", "); Serial.print(p.y);
  Serial.println(")");
  // wait until the screen is released
  while(ctp.touched()){}
  return p;
}

int getInputValue(Adafruit_FT6206 ctp){
  TS_Point p = getMappedPoint(ctp);
    for (int i = 0; i<12;i++){
      if ( p.x > keypad[i][0] && p.x < keypad[i][1] && p.y > keypad[i][2] && p.y < keypad[i][3])
      {
        return(keypad[i][4]);
      }
    }
}

int getNumFromKeypad(Adafruit_ILI9341 tft, Adafruit_FT6206 ctp, String str1, String str2){
  boolean entered = false;
  String numString = "";
  while(!entered){
    // clear the screen
    tft.fillScreen(ILI9341_BLACK);
    tft.setTextSize(NUMTEXTSIZE - 1);
    tft.setCursor(0,0);
    
    tft.println(str1);
    tft.print(str2 + ": ");

    drawKeyboard(tft);
    tft.print(numString);
    int input = getInputValue(ctp);
    if(input == DELETE){
      numString.remove(numString.length()-1);
    }
    else if(input == ENTER){
      entered = true;
    } 
    else{
      numString.concat(String(input));
    }
  }
  tft.fillScreen(ILI9341_BLACK);
  return numString.toInt();
}
