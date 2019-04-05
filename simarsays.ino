#include "TM1637.h"

TM1637 tm1637(39,38);

int8_t LedDisp[] = {0x00,0x12,0x00,0x00};


void setup() {
  // Initializing Serial Connection
  Serial.begin(9600);

  // 4 Digit 7 Segment Display Initialization
  tm1637.init();
  tm1637.set(BRIGHTEST);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
  tm1637.display(LedDisp);

  int numPlayers = promptNumPlayer();
}

int promptNumPlayer() {
  int numPlayers = 1;

  while(true) {
    delay(1000);
    int8_t LedDisps[] = {0x00,0x12,0x01,0x00};
    tm1637.display(LedDisps);
    delay(1000);
    int8_t LedDispx[] = {0x00,0x12,0x00,0x00};
    tm1637.display(LedDispx);
  }

  return numPlayers;
}

void loop() {
  // put your main code here, to run repeatedly: 
  
}
