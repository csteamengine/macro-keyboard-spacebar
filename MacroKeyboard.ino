#include <Keyboard.h>

#define SPACE 2
#define DOWN 4
#define UP 3

unsigned long debounceDelay = 50; 
unsigned long lastDebounceTimeSpace = 0;
unsigned long lastDebounceTimeDown = 0;
unsigned long lastDebounceTimeUp = 0;

bool lastSpace = HIGH;
bool lastDown = HIGH;
bool lastUp = HIGH;

bool spaceState = HIGH;
bool downState = HIGH;
bool upState = HIGH;

bool downPressed = false;
bool upPressed = false;

void setup() {
  // make pin 2 an input and turn on the
  // pullup resistor so it goes high unless
  // connected  to ground:
  pinMode(SPACE, INPUT_PULLUP);
  pinMode(DOWN, INPUT_PULLUP);
  pinMode(UP, INPUT_PULLUP);
  Keyboard.begin();
  Serial.begin(9600);
}

void loop() {
  int spaceReading = digitalRead(SPACE);
  int downReading = digitalRead(DOWN);
  int upReading = digitalRead(UP);

  if(downPressed && downReading == HIGH){
      Keyboard.write(KEY_DOWN_ARROW);
      downPressed = false;
  }
  
  if(upPressed && upReading == HIGH){
      Keyboard.write(KEY_UP_ARROW);
      upPressed = false;
  }

  if(spaceReading != lastSpace){
    lastDebounceTimeSpace = millis();
  }

  if(downReading != lastDown){
    lastDebounceTimeDown = millis();
  }

  if(upReading != lastUp){
    lastDebounceTimeUp = millis();
  }

  if ((millis() - lastDebounceTimeSpace) > debounceDelay) {
    spaceState = spaceReading;
    if (spaceState == LOW) {
      Keyboard.press(' ');
    }else{
      Keyboard.release(' ');
    }
  }  

  if ((millis() - lastDebounceTimeDown) > debounceDelay) {
    if (downReading != downState) {
      downState = downReading;
      
      if (downState == LOW) {
        downPressed = true;
      }
    }
  }

  if ((millis() - lastDebounceTimeUp) > debounceDelay) {
    if (upReading != upState) {
      upState = upReading;

      if (upState == LOW) {
        upPressed = true;
      }
    }
  }

  lastSpace = spaceReading;
  lastDown = downReading;
  lastUp = upReading;

}
