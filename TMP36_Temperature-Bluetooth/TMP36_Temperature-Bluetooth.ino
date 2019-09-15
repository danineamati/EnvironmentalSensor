#include "SoftwareSerial.h"
SoftwareSerial bluetoothComs(2, 3);

#define aref_voltage 3.3

int TMP36_temp_pin = 1; // Analog pin 1
int TMP36_temp_val = 0;


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  bluetoothComs.begin(9600);
  Serial.println("Starting Bluetooth");
}

void loop() {
  // put your main code here, to run repeatedly:

  // Read temp value
  TMP36_temp_val = analogRead(TMP36_temp_pin); // Raw analog out (0 - 1023)
  
  // Convert to voltage
  float volts = TMP36_temp_val * 3.3 / 1024.0;

  // Convert to Celcius (10 mV / DEG C where 500 mV = 0C)
  float tempC = (volts * 100) - 50;
  // COnvert Celcius to Fahrenheit
  float tempF = (tempC * 9.0 / 5.0) + 32.0;
 

  // Print values to serial
  if (bluetoothComs.available()) {
    bluetoothComs.flush();
    bluetoothComs.print(TMP36_temp_val);
    bluetoothComs.print(" = ");
    bluetoothComs.print(volts);
    bluetoothComs.println(" V");
    bluetoothComs.print(tempC);
    bluetoothComs.print(" oC = ");
    bluetoothComs.print(tempF); 
    bluetoothComs.println(" oF");
  }

  delay(1000);
}
