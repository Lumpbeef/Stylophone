
#include <SPI.h>          // f.k. for Arduino-1.5.2
#include "Adafruit_GFX.h"// Hardware-specific library
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
#include <TouchScreen.h>         //Adafruit Library
#include "pitches_alt.h"

// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define GRAY    0xBDD7
#define DGRAY   0x8430
#define WHITE   0xFFFF

#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

//up untill this point is an amalgamtion of code for the LCD display

#define Buzzer_Pin 53 //this is the buzzer pin, change it if you want \/('^')\/

uint16_t ID;

// starting here is the touchscreen code

const int XP=8,XM=A2,YP=A3,YM=9; //320x480 ID=0x9486
const int TS_LEFT=110,TS_RT=930,TS_TOP=975,TS_BOT=87; 

//this is the calibration for my screen values may change for different people

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
TSPoint tp;

#define MINPRESSURE 200
#define MAXPRESSURE 1000

int16_t BOXSIZE;
int16_t PENRADIUS = 1;
uint16_t xpos, ypos;  //screen coordinates during touching

//***********************************************************************************************************************************
// most of the code up to this point is copied from examples from MCUFRIEND_KBV libraries and Digital Examples

void setup(void) {
  // put your setup code here, to run once:
  Serial.begin(9600);
  tft.reset();
  ID = tft.readID();
  Serial.print("TFT ID = 0x");
  Serial.println(ID, HEX);
  tft.begin(ID);
  tft.setRotation(1);
  BOXSIZE = tft.width() / 8;
  tft.fillScreen(DGRAY);
  //this creates the squares for the stylophone keys  big grey rectangles with black edges 
  for (int i = 0; i< 8;i++){
    for(int j = 0; j < 3;j++){
      tft.fillRect(BOXSIZE*i, BOXSIZE*2*j, BOXSIZE, BOXSIZE*2, GRAY);
      tft.drawRect(BOXSIZE*i, BOXSIZE*2*j, BOXSIZE, BOXSIZE*2, BLACK);
    }
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:
  tp = ts.getPoint();
  if (tp.z > MINPRESSURE && tp.z < MAXPRESSURE) {
    xpos = map(tp.y, TS_TOP, TS_BOT, 0, tft.width());
    ypos = map(tp.x, TS_RT, TS_LEFT, 0, tft.height());
    if (ypos < BOXSIZE*2) { 
      
            if (xpos < BOXSIZE) {
              while (tp.z > MINPRESSURE){
                  tone(Buzzer_Pin,doe);
                  Serial.println(tp.z);
                  tp = ts.getPoint();
              }
            } else if (xpos < BOXSIZE * 2) {
                while (tp.z > MINPRESSURE ){
                  tone(Buzzer_Pin,re);
                  Serial.println(tp.z);
                  tp = ts.getPoint();
              }
            } else if (xpos < BOXSIZE * 3) {
                 while (tp.z > MINPRESSURE){
                    tone(Buzzer_Pin,me);
                    Serial.println(tp.z);
                    tp = ts.getPoint();
                 }
            } else if (xpos < BOXSIZE * 4) {
                while (tp.z > MINPRESSURE){
                    tone(Buzzer_Pin,fa);
                    Serial.println(tp.z);
                    tp = ts.getPoint();
              }
            } else if (xpos < BOXSIZE * 5) {
                   while (tp.z > MINPRESSURE){
                    tone(Buzzer_Pin,so);
                    Serial.println(tp.z);
                    tp = ts.getPoint();
              }
            } else if (xpos < BOXSIZE * 6) {
                    while (tp.z > MINPRESSURE){
                     tone(Buzzer_Pin,la);
                     Serial.println(tp.z);
                     tp = ts.getPoint();
              }
            } else if (xpos < BOXSIZE * 7) {
                    while (tp.z > MINPRESSURE){
                     tone(Buzzer_Pin,si);
                     Serial.println(tp.z);
                     tp = ts.getPoint();
                    }
            } else if (xpos < BOXSIZE * 8) {
                    while (tp.z > MINPRESSURE){
                     tone(Buzzer_Pin,doe2);
                     Serial.println(tp.z);
                     tp = ts.getPoint();
                    }
            }
            
            noTone(Buzzer_Pin);

        }
  }
}
