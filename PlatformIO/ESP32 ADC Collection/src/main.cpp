#include <Arduino.h>
#include "driver/gpio.h"
#include "driver/adc.h"
#include <SPI.h>

float getRealDistance();
void customPulseRead();
void collectData();
void SPI_Collect_Data();
void printData(float real_dist);
void teleplotData(float real_dist);
int readRegister();


#define ADC_CHANNEL ADC1_CHANNEL_4

// #define PERIOD 10  // period in us
#define SAMPLE_FREQ 100  // sample freq in kHz

unsigned long last_us = 0L;
int period_us = (int)(1000 / SAMPLE_FREQ);

const int num_samples = 3000;
int read_val = 0;

const int trigPin = 1;
const int echoPin = 2;

float distance = 0.0;

int timestamps[num_samples] = {};
int samples[num_samples] = {};

int raw_data[2][num_samples];

void setup() {
  Serial.begin(115200);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // SPI Setup
  pinMode(SS, OUTPUT);
  SPI.begin();


  // old code - this uses esp32 adc library
  // adc1_config_channel_atten(ADC_CHANNEL, ADC_ATTEN_DB_11);

  //set the resolution to 12 bits (0-4096)
  analogReadResolution(12);

  // analogSetAttenuation(ADC_11db);

  Serial.println("Starting program");
  Serial.print("Period in us: ");
  Serial.println(period_us);
}

void loop() {
  distance = getRealDistance();
  // Serial.print("[loop] distance: ");
  // Serial.println(distance);
  delay(1000);
  customPulseRead();
  delay(100);
  // printData(distance);
  teleplotData(distance);

  delay(500);

  // printTimestamps();
}

float getRealDistance(){
  float echoTime;
  float calcDist;

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  echoTime = pulseIn(echoPin, HIGH);

  calcDist = echoTime * 0.034 / 2;

  return calcDist;

}

void customPulseRead(){
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // SPI_Collect_Data();
  
}

void collectData() {
  // last_us = micros();

  for (int i = 0; i < num_samples; i++) {
    last_us = micros();
    while (micros() - last_us < period_us) {}

    // timestamps[i] = micros();

    raw_data[0][i] = micros();
    raw_data[1][i] = analogReadMilliVolts(ADC_CHANNEL);

    

    // sample(i);
  }
}

void SPI_Collect_Data(){
  for (int i = 0; i < num_samples; i++){
    SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE1));
    

    raw_data[1][i] = readRegister();

    SPI.endTransaction();
  }
}

void printData(float real_dist){
  Serial.print("[");

  // print actual dist from US-100
  Serial.print(real_dist);
  Serial.print(";");

  for (int i = 0; i < num_samples - 1; i++){
    Serial.print(raw_data[0][i]);
    Serial.print(",");
    Serial.print(raw_data[1][i]);
    Serial.print(";");
  }
  Serial.print(raw_data[0][num_samples - 1]);
  Serial.print(",");
  Serial.print(raw_data[1][num_samples - 1]);
  Serial.print("]");
}

void teleplotData(float real_dist){
  Serial.print("Real Distance: ");

  // print actual dist from US-100
  Serial.println(real_dist);

  for (int i = 0; i < num_samples; i++){
    Serial.print(">ADC Read:");
    Serial.println(raw_data[1][i]);
  }
}

int readRegister(){
  byte upper_byte = 0;
  byte lower_byte = 0;

  digitalWrite(SS, LOW);

  int result = SPI.transfer(0x00);

  result = result << 8;

  lower_byte = SPI.transfer(0x00);

  result = result | lower_byte;

  digitalWrite(SS, HIGH);

  return result;
}
