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

// Function Prototypes
TS_Point getMappedPoint();
char getInputButtonValue();

// Size of the color selection boxes and the paintbrush size
#define NUMPADBOXSIZE 320/5
#define DAYBOXSIZE 320/8
#define NUMTEXTSIZE 3
#define TEXTSIZE 2

// x-min, x-max, y-min, y-max, value
int keypad[18][5] = {
  {0, NUMPADBOXSIZE, 240 - NUMPADBOXSIZE, 240, '5'},
  {NUMPADBOXSIZE, 2 * NUMPADBOXSIZE, 240 - NUMPADBOXSIZE, 240, '6'},
  {2 * NUMPADBOXSIZE, 3 * NUMPADBOXSIZE, 240 - NUMPADBOXSIZE, 240, '7'},
  {3 * NUMPADBOXSIZE, 4 * NUMPADBOXSIZE, 240 - NUMPADBOXSIZE, 240, '8'},
  {4 * NUMPADBOXSIZE, 5 * NUMPADBOXSIZE, 240 - NUMPADBOXSIZE, 240, '9'},
  {0, NUMPADBOXSIZE, 240 - 2 * NUMPADBOXSIZE, 240 - NUMPADBOXSIZE, '0'},
  {NUMPADBOXSIZE, 2 * NUMPADBOXSIZE, 240 - 2 * NUMPADBOXSIZE, 240 - NUMPADBOXSIZE, '1'},
  {2 * NUMPADBOXSIZE, 3 * NUMPADBOXSIZE, 240 - 2 * NUMPADBOXSIZE, 240 - NUMPADBOXSIZE, '2'},
  {3 * NUMPADBOXSIZE, 4 * NUMPADBOXSIZE, 240 - 2 * NUMPADBOXSIZE, 240 - NUMPADBOXSIZE, '3'},
  {4 * NUMPADBOXSIZE, 5 * NUMPADBOXSIZE, 240 - 2 * NUMPADBOXSIZE, 240 - NUMPADBOXSIZE, '4'}
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
  tft.setTextSize(TEXTSIZE);
  tft.setTextColor(ILI9341_WHITE);

  tft.setCursor(0,0);
  tft.println("Please enter the date:");

  tft.setTextSize(NUMTEXTSIZE);
  // make keypad selection boxes
  for(int i = 0; i < 5; i++){
    // Draw 0-4
    tft.drawRect(NUMPADBOXSIZE * i, 240 - (NUMPADBOXSIZE * 2), NUMPADBOXSIZE, NUMPADBOXSIZE, ILI9341_WHITE);
    tft.setCursor(NUMPADBOXSIZE * i + (NUMPADBOXSIZE / 2 - NUMTEXTSIZE / 2), 240 - NUMPADBOXSIZE * 2 + (NUMPADBOXSIZE / 2));
    tft.println(i);
    // Draw 5-9
    tft.drawRect(NUMPADBOXSIZE * i, 240 - NUMPADBOXSIZE, NUMPADBOXSIZE, NUMPADBOXSIZE, ILI9341_WHITE);
    tft.setCursor(NUMPADBOXSIZE * i + (NUMPADBOXSIZE / 2 - NUMTEXTSIZE / 2), 240 - NUMPADBOXSIZE +(NUMPADBOXSIZE / 2));
    tft.println(i + 5);
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

  char input = getInputButtonValue();
  Serial.print("Key Touched: "); Serial.println(input);
  delay(1000);
}


TS_Point getMappedPoint(){
    // Retrieve a point  
  TS_Point p = ctp.getPoint();
  TS_Point temp;
    // flip it around to match the screen.
  temp.y = map(p.x, 0, 240, 240, 0);
  temp.x = map(p.y, 0, 320, 0, 320);
  p.x = temp.x;
  p.y = temp.y;
  Serial.print("("); Serial.print(p.x);
  Serial.print(", "); Serial.print(p.y);
  Serial.println(")");
  return p;
}

char getInputButtonValue(){
  TS_Point p = getMappedPoint();
    for (int i = 0; i<18;i++){
      if ( p.x > keypad[i][0] && p.x < keypad[i][1] && p.y > keypad[i][2] && p.y < keypad[i][3])
      {
        return(keypad[i][4]);
      }
    }
}




