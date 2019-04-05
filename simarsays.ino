#include "TM1637.h"

TM1637 tm1637(39,38);

const int maxNumPlayers = 4;
const int leftButtonPin = PUSH1;     // the number of the pushbutton pin
const int rightButtonPin = PUSH2;     // the number of the pushbutton pin
const int redLedPin =  RED_LED;      // the number of the LED pin
const int greenLedPin =  GREEN_LED;      // the number of the LED pin
const int blueLedPin =  BLUE_LED;      // the number of the LED pin
int leftButtonState = 0;         // variable for reading the pushbutton status
int rightButtonState = 0;         // variable for reading the pushbutton status

void setup() {
  // 4 Digit 7 Segment Display Initialization
  tm1637.init();
  tm1637.set(BRIGHTEST);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;

  // Setting Buttons
  pinMode(leftButtonPin, INPUT_PULLUP);     
  pinMode(rightButtonPin, INPUT_PULLUP);
  pinMode(redLedPin, OUTPUT);        
  pinMode(greenLedPin, OUTPUT);        
  pinMode(blueLedPin, OUTPUT);        

  // Writing __ 01 to Display
  segmentDisplay(0x12,0x12,0x00,0x01);

  // Prompting selection for number of players
  int numPlayers = promptNumPlayer();

  
}


void segmentDisplay(int sig1, int sig2, int sig3, int sig4) {
  /***
   * Displays the number on the 4 Digit Display:
   */
  int8_t LedDisp[] = {sig1,sig2,sig3,sig4};
  tm1637.display(LedDisp);
}

void writeLed(int LED, int STATE) {
  /***
   * Does LED stuff:
   */
  digitalWrite(LED, STATE);
}

int promptNumPlayer() {
  /***
   * Prompts number of player selection and
   * returns the inputted number of players.
   */
  writeLed(greenLedPin, HIGH);
  int numPlayers = 1;

  while(true) {
      leftButtonState = digitalRead(leftButtonPin);
      rightButtonState = digitalRead(rightButtonPin);
      
      if(leftButtonState == LOW) { 
        break; 
      }

      if(rightButtonState == LOW) { 
        numPlayers += 1;
        if(numPlayers > maxNumPlayers) {
          numPlayers = 1;
        }
        segmentDisplay(0x12,0x12,0x00,numPlayers);
        delay(250);
      }
  }

  writeLed(greenLedPin, LOW);
  return numPlayers;
}

void loop() {
  // put your main code here, to run repeatedly: 
  
}
