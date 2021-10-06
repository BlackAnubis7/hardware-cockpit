// CLK MAY BE COMMON FOR DIFFEREN MAX CHIPS
// LOAD AND DataIn SHOULD BE GIVEN TO EACH CHIP
// ----------------------------------------------
// CLK AND LOAD AND DataIn ARE COMMON IF CHIPS IN SERIAL

// https://www.ardumotive.com/8-digit-7seg-display-en.html
#include "LedControl.h"

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 13 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
LedControl lc= LedControl(16,17,14,1);
LedControl lc2=LedControl(53,17,51,1);

unsigned long delaytime=250;

void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);
  lc2.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc2.setIntensity(0,8);
  /* and clear the display */
  lc2.clearDisplay(0);
}


/*
 This method will display the characters for the
 word "Arduino" one after the other on digit 0. 
 */
void writeArduinoOn7Segment() {
  for(char a='0'; a<='9'; a++) {
    lc.setChar(0,0,a,false);
    for(char b='0'; b<='9'; b++) {
      lc.setChar(0,1,b,false);
      lc2.setChar(0,0,b,false);
      for(char c='0'; c<='9'; c++) {
        lc.setChar(0,2,c,false);
        delay(delaytime);
      }
    }
  }
} 


void loop() { 
  writeArduinoOn7Segment();
}