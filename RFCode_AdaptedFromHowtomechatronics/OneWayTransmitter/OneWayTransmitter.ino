/*
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24Network.h>

RF24 radio(7, 8); // CE, CSN
//RF24Network network(radio);
//const uint16_t masterNode = 00;

const byte address[6] = "00001";
const uint16_t testAddress = 00001;
const uint16_t node01 = 01;

void setup() {
  SPI.begin();
  Serial.begin(9600);
  radio.begin();
//  radio.openWritingPipe(address);
//  radio.setPALevel(RF24_PA_MIN);
//  radio.stopListening();

//  network.begin(90, masterNode);
  
  Serial.println("Transmitter Ready");
}
void loop() {
  Serial.println("Start Loop");
//  network.update();
  
  const char text[] = "Hello World";
  Serial.println("Starting to write");
  // Look at address next
//  uint16_t address = testAddress;
//  RF24NetworkHeader header(address);
//  network.write(header, &text, sizeof(text));
//  radio.write(&text, sizeof(text));


  const int num = 12345;
  radio.write(&num, sizeof(num));
  
  delay(1000);
  Serial.print("Sent: ");
  Serial.println(text);
}
