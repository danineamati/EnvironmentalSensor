/*
  Output all readings in CSV format
  BME280 Arduino and Teensy example
  Marshall Taylor @ SparkFun Electronics
  May 20, 2015
  https://github.com/sparkfun/SparkFun_BME280_Arduino_Library
  
  This sketch outputs BME280 data in comma separated values for generating spreadsheet graphs.

  Feel like supporting our work? Buy a board from SparkFun!
  https://www.sparkfun.com/products/14348 - Qwiic Combo Board
  https://www.sparkfun.com/products/13676 - BME280 Breakout Board
*/

#include <Wire.h>
#include "SparkFunBME280.h"

#include <SPI.h>
#include <SD.h>

File myFile;

BME280 mySensor;
unsigned long sampleNumber = 0;

void setup()
{
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  if (!SD.begin(4)) {
    Serial.println("Initialization failed!");
    return;
  }
  Serial.println("Initialization done.");

  Wire.begin();

  if (mySensor.beginI2C() == false) //Begin communication over I2C
  {
    Serial.println("The sensor did not respond. Please check wiring.");
    while(1); //Freeze
  }

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("sensor.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to sensor.txt...");
    //Build a first-row of column headers
    myFile.print("SampleNumber,");
    myFile.print("Time(ms),");
    myFile.print("T(deg C),");
    myFile.print("T(deg F),");
    myFile.print("P(Pa),");
    myFile.print("Alt(m),");
    myFile.print("Alt(ft),");
    myFile.print("%RH");
    myFile.println("");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}

void loop()
{

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("sensor.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    //Print each row in the loop
    //Start with temperature, as that data is needed for accurate compensation.
    //Reading the temperature updates the compensators of the other functions
    //in the background.
    Serial.print("Sample Number: ");
    Serial.println(sampleNumber);
    
    myFile.print(sampleNumber);
    myFile.print(",");
    myFile.print(millis());
    myFile.print(",");
    myFile.print(mySensor.readTempC(), 2);
    myFile.print(",");
    myFile.print(mySensor.readTempF(), 3);
    myFile.print(",");
    myFile.print(mySensor.readFloatPressure(), 0);
    myFile.print(",");
    myFile.print(mySensor.readFloatAltitudeMeters(), 3);
    myFile.print(",");
    myFile.print(mySensor.readFloatAltitudeFeet(), 3);
    myFile.print(",");
    myFile.print(mySensor.readFloatHumidity(), 0);
    myFile.println();
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening sensor.txt");
  }
	
	sampleNumber++;
	
	delay(300000);
}
