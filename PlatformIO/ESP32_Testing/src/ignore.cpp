#include <Arduino.h>
#include "driver/gpio.h"
#include "driver/adc.h"
#include <SPI.h>

int old_readRegister(int bytesToRead);
int readRegister();
void SPI_collectData();
void teleplotData();

const int num_samples = 5000;

int result = 0;
int data[num_samples];

void setup(){
  Serial.begin(115200);

  pinMode(SS, OUTPUT);

  SPI.begin();

}

void loop(){
  
}

void SPI_collectData(){
  for (int i = 0; i < num_samples; i++){
    SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE1));
    
    data[i] = readRegister();

    SPI.endTransaction();
  }
}

void teleplotData(){
  for (int i = 0; i < num_samples; i++){
    Serial.print(">ReadVal: ");
    Serial.println(data[i]);
  }
}

//Read from or write to register from the SCP1000:
int old_readRegister(int bytesToRead) {
  byte inByte = 0;  // incoming byte from the SPI

  int result = 0;   // result to return

  // take the chip select low to select the device:
  digitalWrite(SS, LOW);

  // send the device the register you want to read:
  // SPI.transfer(0x00);

  // send a value of 0 to read the first byte returned:
  result = SPI.transfer(0x00);

  // decrement the number of bytes left to read:
  bytesToRead--;

  // if you still have another byte to read:
  if (bytesToRead > 0) {
    // shift the first byte left, then get the second byte:
    result = result << 8;

    inByte = SPI.transfer16(0x00);

    // combine the byte you just got with the previous one:
    result = result | inByte;

    // decrement the number of bytes left to read:
    bytesToRead--;
  }

  // take the chip select high to de-select:
  digitalWrite(SS, HIGH);

  // return the result:
  return (result);

}

int readRegister(){
  byte upper_byte = 0;
  byte lower_byte = 0;

  digitalWrite(SS, LOW);

  result = SPI.transfer(0x00);

  result = result << 8;

  lower_byte = SPI.transfer(0x00);

  result = result | lower_byte;

  digitalWrite(SS, HIGH);

  return result;
}
