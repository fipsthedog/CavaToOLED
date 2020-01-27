#include <FastLED.h>
#define DATA_PIN 11
#define NUM_LEDS 1
CRGB leds[NUM_LEDS];
long milOld;
int csvVal;

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
#define OLED_Address 0x3C
Adafruit_SSD1306 oled(1);
//128x32 in this case

byte y = 0; // for incoming serial data
byte x = 0;
byte lastX=0;
byte lastY=0;


void setup() {
  //set Specific LED
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
  //random starting color
  randomSeed(analogRead(0));
  csvVal=random(255);
  
  Serial.begin(115200); // opens serial port, sets data rate
  oled.begin(SSD1306_SWITCHCAPVCC, OLED_Address);
  oled.clearDisplay();
  //optional:
  //oled.invertDisplay(true);
  //set Display rotation here
  oled.setRotation(2);
  oled.display();
}

void loop() {
  serialDraw();
}

void serialDraw(){
  // send data only when you receive data:
  while (Serial.available() > 0) {
    
    byte y=Serial.parseInt();
    Serial.println(y);
    if (y<33 && x<10){
      draw(x,y);
      x+=1;
    }
    else if(y==99){
      oled.display();
      oled.clearDisplay();
      x=0; //end of line
      //Serial.print("END"); //optinal for debugging
      } 
    else if (y==98){
      x=0;
      randomwalkColor(500,1);
    }//beginning of line
    
  }
  x=0; 
  randomwalkColor(500,1);
}

void draw(byte inX, byte height){
  byte pos=(10-inX)*12-2;  
  oled.drawFastVLine(pos-2,0,height,WHITE);
  oled.drawFastVLine(pos-3,0,height,WHITE);
  oled.drawFastVLine(pos-4,0,height,WHITE);
  oled.drawFastVLine(pos-1,0,height,WHITE);
  oled.drawFastVLine(pos,0,height,WHITE);
  oled.drawFastVLine(pos+2,0,height,WHITE);
  oled.drawFastVLine(pos+1,0,height,WHITE);
  oled.drawFastVLine(pos+3,0,height,WHITE);
  oled.drawFastVLine(pos+4,0,height,WHITE);
  //lineBar(pos,height,4);
}

void randomwalkColor(int tStep,int factor){
  if (millis()>milOld+tStep){
    milOld=millis();
    csvVal=(csvVal+((1-(random(2)*2))*factor))%255;
    leds[0] = CHSV(csvVal,255,255);
    FastLED.show();  
  }
  
}
