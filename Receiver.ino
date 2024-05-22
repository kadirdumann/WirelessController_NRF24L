#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

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
  Serial.begin(9600);
  bool init = radio.begin();
  if(init)
  Serial.println("SPI Succes");
  else
  Serial.println("SPI Fail");
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.setChannel(5);
  radio.startListening();
}

void loop() {
  if (radio.available()>0) {
    radio.read(&data, sizeof(data));

    Serial.print("Joystick 1 - X: ");
    Serial.print(data.joy1X);
    Serial.print(" | Y: ");
    Serial.println(data.joy1Y);

    Serial.print("Joystick 2 - X: ");
    Serial.print(data.joy2X);
    Serial.print(" | Y: ");
    Serial.println(data.joy2Y);
  }
}