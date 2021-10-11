#include "LedControl.h"

LedControl lc= LedControl(16,17,14,1);

unsigned long delaytime=250;
int analogPin = A0;
int analogInput = 0;

void setup() {
  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
}

char chr(int n) {
  return (char) n + '0';
}

void loop() { 
  analogInput = analogRead(analogPin);
  lc.setChar(0, 0, '-', false);
  lc.setChar(0, 1, '-', false);
  lc.setChar(0, 2, '-', false);
  lc.setIntensity(0,analogInput/70);
  delay(20);
}