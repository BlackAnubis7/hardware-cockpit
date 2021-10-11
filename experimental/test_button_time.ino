#include "LedControl.h"

LedControl lc= LedControl(16,17,14,1);

unsigned long ta;
int buttonPin = 46;
int state = LOW;
int prevState = LOW;
int time = 0;

void setup() {
  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
  pinMode(buttonPin, INPUT);
}

char chr(int n) {
  return (char) n + '0';
}

void writeNum(int n) {
  for (int i=2; i>=0; i--) {
    lc.setChar(0, i, chr(n % 10), false);
    n /= 10;
  }
}

void loop() { 
  state = digitalRead(buttonPin);
  if (state == HIGH) {
      if (prevState == LOW) {
        time = 0;
        ta = millis();
      }
      else time = millis()-ta;
  }
  prevState = state;
  writeNum(time);
  delay(1);
}