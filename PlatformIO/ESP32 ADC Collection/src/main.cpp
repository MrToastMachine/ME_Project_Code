#include <Arduino.h>
#include "driver/gpio.h"
#include "driver/adc.h"

void customPulseRead();
void transmitSignal();
void printTimestamps();
void collectData();
void sample(int sample_index);
void printData();


#define ADC_CHANNEL ADC1_CHANNEL_4

// #define PERIOD 10  // period in us
#define SAMPLE_FREQ 100  // sample freq in kHz

unsigned long last_us = 0L;
int period_us = (int)(1000 / SAMPLE_FREQ);

const int num_samples = 5000;
int read_val = 0;

const int trigPin = 5;
const int echoPin = 6;

float distance = 0.0;


/*
Put array here to hold sampled values
- Know length before sampling starts -> 4000
- Can send entire array over Serial then maybe
*/

int timestamps[num_samples] = {};
int samples[num_samples] = {};

int raw_data[2][num_samples];

void setup() {
  Serial.begin(115200);

  // pinMode(trigPin, OUTPUT);
  // pinMode(echoPin, INPUT);

  adc1_config_channel_atten(ADC_CHANNEL, ADC_ATTEN_DB_11);

  Serial.println("Starting program");
  Serial.print("Period in us: ");
  Serial.println(period_us);
}

void loop() {
  customPulseRead();
  delay(500);
  printData();

  delay(3000);

  // printTimestamps();
}

void customPulseRead(){
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  collectData();
  
}

void transmitSignal(){
  while(true){
    digitalWrite(trigPin, HIGH);
    delay(2000);
    Serial.println("Still going...");
    digitalWrite(trigPin, LOW);
    delay(1);

  }
}

void printTimestamps() {
  // Serial.println("Printing Timestamps... ");
  for (int i = 0; i < num_samples; i++) {
    // Serial.print((String)i + " : ");
    Serial.println(timestamps[i]);
  }
}

void collectData() {
  // last_us = micros();

  for (int i = 0; i < num_samples; i++) {
    last_us = micros();
    while (micros() - last_us < period_us) {}

    // timestamps[i] = micros();

    raw_data[0][i] = micros();
    raw_data[1][i] = adc1_get_raw(ADC_CHANNEL);

    // sample(i);
  }
}

void sample(int sample_index) {
  timestamps[sample_index] = micros();

  int readVal = adc1_get_raw(ADC_CHANNEL);
  // Serial.println(readVal);

}

void printData(){
  Serial.print("[");
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