#include <Keyboard.h>

#define SPACE 2
#define LEFT 3
#define RIGHT 4

unsigned long debounceDelay = 50; 
unsigned long lastDebounceTimeSpace = 0;
unsigned long lastDebounceTimeLeft = 0;
unsigned long lastDebounceTimeRight = 0;

bool lastSpace = HIGH;
bool lastLeft = HIGH;
bool lastRight = HIGH;

bool spaceState = HIGH;
bool leftState = HIGH;
bool rightState = HIGH;

bool leftPressed = false;
bool rightPressed = false;

void setup() {
  // make pin 2 an input and turn on the
  // pullup resistor so it goes high unless
  // connected  to ground:
  pinMode(SPACE, INPUT_PULLUP);
  pinMode(LEFT, INPUT_PULLUP);
  pinMode(RIGHT, INPUT_PULLUP);
  Keyboard.begin();
  Serial.begin(9600);
}

void loop() {
  int spaceReading = digitalRead(SPACE);
  int leftReading = digitalRead(LEFT);
  int rightReading = digitalRead(RIGHT);

  if(leftPressed && leftReading == HIGH){
      Keyboard.write(KEY_LEFT_ARROW);
      leftPressed = false;
  }
  
  if(rightPressed && rightReading == HIGH){
      Keyboard.write(KEY_RIGHT_ARROW);
      rightPressed = false;
  }

  if(spaceReading != lastSpace){
    lastDebounceTimeSpace = millis();
  }

  if(leftReading != lastLeft){
    lastDebounceTimeLeft = millis();
  }

  if(rightReading != lastRight){
    lastDebounceTimeRight = millis();
  }

  if ((millis() - lastDebounceTimeSpace) > debounceDelay) {
    spaceState = spaceReading;
    if (spaceState == LOW) {
      Keyboard.write(32);
    }
  }  

  if ((millis() - lastDebounceTimeLeft) > debounceDelay) {
    if (leftReading != leftState) {
      leftState = leftReading;
      
      if (leftState == LOW) {
        leftPressed = true;
      }
    }
  }

  if ((millis() - lastDebounceTimeRight) > debounceDelay) {
    if (rightReading != rightState) {
      rightState = rightReading;

      if (rightState == LOW) {
        rightPressed = true;
      }
    }
  }

  lastSpace = spaceReading;
  lastLeft = leftReading;
  lastRight = rightReading;

}
