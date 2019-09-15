#include "SevSeg.h"

SevSeg sevseg; //Initiate a seven segment controller object
int setNum = 0;
int counter = 0;

void setup() {

  byte numDigits = 4;
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_CATHODE; // See README.md for options
  bool updateWithDelays = false; // Default 'false' is Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = false; // Use 'true' if your decimal point doesn't exist or isn't connected. Then, you only need to specify 7 segmentPins[]

  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
  updateWithDelays, leadingZeros, disableDecPoint);
  
  sevseg.setBrightness(90);

}

void loop() {

  if (counter < 1000) {
    counter ++;
  } else {
    if (setNum < 9999){
      setNum++;
    }
    else {
      setNum = 0;
    }

    counter = 0;
  }
  
  
  sevseg.setNumber(setNum, 2);
  
  sevseg.refreshDisplay(); // Must run repeatedly

}
