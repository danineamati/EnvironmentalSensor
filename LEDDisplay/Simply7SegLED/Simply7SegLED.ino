#include "SevSeg.h"

SevSeg sevseg; //Initiate a seven segment controller object
int setNum = 0;


void setup() {

  byte numDigits = 4;
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins);
  sevseg.setBrightness(90);

}

void loop() {
  
  sevseg.setNumber(8888, 3);
  
  sevseg.refreshDisplay(); // Must run repeatedly

}
