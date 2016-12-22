/*
  BrakeLights.ino
  
  Merry Christmas!!!

  WS2812 Addressable LEDs simulating a short drive around the block.
  
  Copyright (c) 2016, 87fairlady300zx@gmail.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification, 
  are permitted with the following conditions:

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 

  A special thanks to Matt H. for taking intangible sloppy code, throwing it all away
  and recreating this well commented simple demo.
  
  */

#include <Adafruit_NeoPixel.h>

#define PIN            0
#define NUMPIXELS      4

#define LEFT_OUTER      0
#define LEFT_INNER      1
#define RIGHT_INNER     2
#define RIGHT_OUTER     3

#define CR2LED         1

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Color definitions
int off[]          = {  0,   0,   0};
int redDim[]       = { 10,   0,   0};
int red[]          = { 25,   0,   0};
int redBright[]    = {160,   0,   0};
int redXBright[]   = {240,   0,   0};
int white[]        = {200, 150, 130};
int orangeBright[] = {250,  40,   0};


void setup() {
  strip.begin(); // This initializes the NeoPixel library.

  pinMode(CR2LED, OUTPUT);
  digitalWrite(CR2LED, HIGH);
}

void loop() {
  int i;
  
  clear();
  strip.show();

  // Car turned on
  setTailLights(redDim);

  delay(2000);

  // Brakes applied
  setTailLights(redBright, redDim);
  
  delay(2500);

  // Starter cranking lights dim with each engine rotation
  int crankTimer = 100;
  int crankTlower = crankTimer;
  for(i = 0; i < 10; i++) {
    crankTlower = crankTlower -= i*2;
    setTailLights(redBright, red); // Bright
    delay(crankTlower);
    setTailLights(red, redDim); // Dim
    delay(crankTlower);
  }
  setTailLights(redXBright, red); // End on brighter

  delay(3000);

  // Goes into reverse
  setTailLights(redXBright, white);

  delay(1000);
  
  // Brakes released
  setTailLights(red, white);

  delay(3000);
  
  // Brakes applied
  setTailLights(redXBright, white);
  
  delay(500);
  
  // Reverse released
  setTailLights(redXBright, red);

  delay(1500);

  // Brakes released
  setTailLights(red);

  delay(3000);

  // Brakes applied
  setTailLights(redXBright, red);

  delay(1500);

  // Right turn signal applied
  int turnTimer = 600;
  // 5 times
  for(i=0; i<6; i++) {
    setTailLights(redXBright, red, orangeBright, orangeBright); // Turn signal
    delay(turnTimer);
    setTailLights(redXBright, red, off, off); // Normal
    delay(turnTimer);
  }
  // Brakes released
  // 5 more with breakes released
  for(i=0; i<4; i++) {
  setTailLights(red, red, orangeBright, orangeBright); // Turn signal, no brake
  delay(turnTimer);
  setTailLights(red, red, off, off);
  delay(turnTimer);
  }
  // Turn signal released

  delay(500);

  //Drive forward for some time
   setTailLights(red);
   delay(5000);

  // Brakes applied
  setTailLights(redXBright, red);

  delay(2000);

  // Lights dim
  setTailLights(redBright, redDim);

  delay(3000);

  // Lights turn off
  setTailLights(off);
  
}

// Car helpers

void setTailLights(int *all) {
  setTailLights(all, all, all, all);
}

void setTailLights(int *bothOuter, int *bothInner) {
  setTailLights(bothOuter, bothInner, bothInner, bothOuter);
}

void setTailLights(int *leftOuter, int *leftInner, int *rightInner, int *rightOuter ) {
  setPixelColor(LEFT_OUTER, leftOuter);
  setPixelColor(LEFT_INNER, leftInner);
  setPixelColor(RIGHT_INNER, rightInner);
  setPixelColor(RIGHT_OUTER, rightOuter);
  strip.show();
}

// Strip helpers
void clear() {
  for(int i=0; i< strip.numPixels(); i++) {
    //strip.setPixelColor(i, strip.Color(0, 0, 0));
    setPixelColor(i, off);
  }
}

// Override for my colors, uses global `strip`
void setPixelColor(int index, int *colorValues) {
  uint32_t color;
  color = strip.Color(colorValues[0], colorValues[1], colorValues[2]);
  strip.setPixelColor(index, color);
}
