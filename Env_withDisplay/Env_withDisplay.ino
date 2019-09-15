/*
  Get basic environmental readings from the BME280
  By: Nathan Seidle
  SparkFun Electronics
  Date: March 9th, 2018
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  Feel like supporting our work? Buy a board from SparkFun!
  https://www.sparkfun.com/products/14348 - Qwiic Combo Board
  https://www.sparkfun.com/products/13676 - BME280 Breakout Board
  
  This example shows how to read humidity, pressure, and current temperature from the BME280 over I2C.

  Hardware connections:
  BME280 -> Arduino
  GND -> GND
  3.3 -> 3.3
  SDA -> A4
  SCL -> A5
*/

#include <Wire.h>

#include "SevSeg.h"

#include "SparkFunBME280.h"
BME280 mySensor;
SevSeg sevseg; //Initiate a seven segment controller object
int counter = 0;
int multiplier = 0;

void setup()
{

  // Set Up Serial
  Serial.begin(9600);
  Serial.println("Reading basic values from BME280");



  // Set Up Environmental Sensor
  Wire.begin();

  if (mySensor.beginI2C() == false) //Begin communication over I2C
  {
    Serial.println("The sensor did not respond. Please check wiring.");
    while(1); //Freeze
  }


  // Set Up 7 segment 4 digit display
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

  Serial.println("Set Up Complete");

}

void loop()
{

  // Calling the delay function will mess up the 7 Segment display, as such we just loop enough to run it.

  if (counter < 30000) {
    counter ++;
  } else if (multiplier <= 5) {
    counter = 0;
    multiplier ++; 
  } else {

    // Print full data to serial. 
    Serial.print("Humidity: ");
    Serial.print(mySensor.readFloatHumidity(), 0);
    Serial.print("% ");
  
    Serial.print(" Pressure: ");
    Serial.print(mySensor.readFloatPressure(), 0);
    Serial.print(" Pa ");
    Serial.print(" Pressure: ");
    Serial.print(mySensor.readFloatPressure() / 3386, 0);
    Serial.print(" inHg ");
  
    Serial.print(" Alt: ");
    //Serial.print(mySensor.readFloatAltitudeMeters(), 1);
    Serial.print(mySensor.readFloatAltitudeFeet(), 1);
    Serial.print(" Feet ");
  
    Serial.print(" Temp: ");
    //Serial.print(mySensor.readTempC(), 2);
    Serial.print(mySensor.readTempF(), 2);
    Serial.print(" oF ");

    Serial.println();

    // Display the temperature in Farhenheit on the display
    sevseg.setNumber(mySensor.readTempF(), 2); 
    
    counter = 0;
    multiplier = 0;
  }
  
  
  
  
  sevseg.refreshDisplay(); // Must run repeatedly

  

}
