/*
* Arduino Wireless Communication Tutorial
*       Example 1 - Receiver Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

int LED = 3;
bool LEDon = 1;

RF24 radio(8, 7); // CE, CSN
const byte address[6] = "00001";
void setup() {
  Serial.begin(9600);
  SPI.begin();
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  Serial.println("Receiver Ready");
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
}
void loop() {
  if (radio.available()) {
    switchLED(LED);
//    char text[32] = "";
    int num;
//    radio.read(&text, sizeof(text));
    radio.read(&num, sizeof(num));

    Serial.print("Arduino Read: ");
//    Serial.println(text);
    Serial.println(num);
  }
}

void switchLED(int LED){
  LEDon = !LEDon;
  if(LEDon){
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }
}

