#include <Arduino.h>
#include "driver/gpio.h"
#include "driver/adc.h"

float getRealDistance();
void customPulseRead();
void collectData();
void printData(float real_dist);


#define ADC_CHANNEL ADC1_CHANNEL_4

// #define PERIOD 10  // period in us
#define SAMPLE_FREQ 100  // sample freq in kHz

unsigned long last_us = 0L;
int period_us = (int)(1000 / SAMPLE_FREQ);

const int num_samples = 3000;
int read_val = 0;

const int trigPin = 5;
const int echoPin = 6;

float distance = 0.0;

int timestamps[num_samples] = {};
int samples[num_samples] = {};

int raw_data[2][num_samples];

void setup() {
  Serial.begin(115200);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  adc1_config_channel_atten(ADC_CHANNEL, ADC_ATTEN_DB_11);

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
  printData(distance);

  delay(1000);

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
  
  collectData();
  
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