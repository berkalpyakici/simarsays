#include "TM1637.h"

TM1637 tm1637(39,38);

const int maxNumPlayers = 4;
const int leftButtonPin = PUSH1;     // the number of the pushbutton pin
const int rightButtonPin = PUSH2;     // the number of the pushbutton pin
const int redLedPin =  RED_LED;      // the number of the LED pin
const int greenLedPin =  GREEN_LED;      // the number of the LED pin
const int blueLedPin =  BLUE_LED;      // the number of the LED pin
const int buzzer = 40;
const int audioSensor = 23;

int leftButtonState = 0;         // variable for reading the pushbutton status
int rightButtonState = 0;         // variable for reading the pushbutton status
int audioLevel = 0;

int buzzDuration = 200;
int buzzDelayMultiplier = 500;

int curPlayer = 1;
int curRound = 1;

const float patterns[20][4] = {
    {0.57,  0.42,  0.66,  0.43},
    {0.51,  0.43,  0.86,  0.59},
    {0.84,  0.48,  0.31,  0.44},
    {0.45,  0.97,  0.42,  0.33},
    {0.79,  0.27,  0.31,  0.00},
    {0.39,  0.61,  0.93,  0.15},
    {0.52,  0.55,  0.63,  0.81},
    {0.32,  0.12,  0.99,  0.34},
    {0.63,  0.79,  0.32,  0.72},
    {0.07,  0.20,  0.08,  0.28},
    {0.76,  0.13,  0.34,  0.78},
    {0.14,  0.91,  0.08,  0.07},
    {0.40,  0.77,  0.78,  0.82},
    {0.75,  0.71,  0.47,  0.34},
    {0.81,  0.62,  0.62,  0.53},
    {0.11,  0.64,  0.35,  0.83},
    {0.97,  0.61,  0.18,  0.71},
    {0.50,  0.54,  0.67,  0.57},
    {0.99,  0.41,  0.63,  0.24},
    {0.45,  0.46,  0.90,  0.56}};

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

  

  buzzPattern(2);
}


void segmentDisplay(int sig1, int sig2, int sig3, int sig4) {
  /***
   * Displays the number on the 4 Digit Display:
   */
  int8_t LedDisp[] = {sig1,sig2,sig3,sig4};
  tm1637.display(LedDisp);
}

void toggleBuzz(){
  /***
   * 
   */
  digitalWrite(buzzer, HIGH);
  delay(buzzDuration);
  digitalWrite(buzzer, LOW);
}

void buzzPattern(int pattern) {
  /***
   * Plays the pattern with the index patern.
   */
  for(int i = 0; i < 4; i++ ) {
    toggleBuzz();
    delay(patterns[pattern][i] * buzzDelayMultiplier);
  }
}

void writeLed(int LED, int STATE) {
  /***
   * Does LED stuff.
   */
  digitalWrite(LED, STATE);
}

int soundLevel() {
  /***
   * Listens the enviornment.
   * > 1800 means a clap.
   */
  long sum = 0;
  for(int i=0; i<32; i++)
  {
      sum += analogRead(audioSensor);
  }

  sum >>= 5;

  return sum
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
