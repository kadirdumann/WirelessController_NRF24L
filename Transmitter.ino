#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const int joy1X = A0;
const int joy1Y = A1;
const int joy2X = A2;
const int joy2Y = A3;

// CE ve CSN pinleri
RF24 radio(5, 6);

// Adres
const byte address[6] = "00001";

struct Data_Package {
  int joy1X;
  int joy1Y;
  int joy2X;
  int joy2Y;
};
Data_Package data;

void setup() {
//  Serial.begin(9600);
  Serial.begin(9600);
  
  bool init=  radio.begin(); 
  if (init) {
    Serial.println("SPI succes");
  }
  else{
    Serial.println("SPI fail");
  }
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.setChannel(5);
  radio.stopListening();
}

void loop() {
  data.joy1X = analogRead(joy1X);
  data.joy1Y = analogRead(joy1Y);
  data.joy2X = analogRead(joy2X);
  data.joy2Y = analogRead(joy2Y);

  radio.write(&data, sizeof(data));

  delay(50);
}