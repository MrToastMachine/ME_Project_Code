#include <Arduino.h>
#include "driver/adc.h"


void collectData();
void teleplotData();

// #define PERIOD 10  // period in us
#define SAMPLE_FREQ 100  // sample freq in kHz

unsigned long last_us = 0L;
int period_us = (int)(1000 / SAMPLE_FREQ);

const int num_samples = 3000;

int data[num_samples];

void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
  
  //set the resolution to 12 bits (0-4096)
  analogReadResolution(12);
  analogSetPinAttenuation(4, ADC_0db);

  Serial.println("Starting testing...");
}

void loop() {
  
  collectData();
  teleplotData();
  delay(500);
}


void collectData() {
  // last_us = micros();

  for (int i = 0; i < num_samples; i++) {
    last_us = micros();
    while (micros() - last_us < period_us) {}

    // timestamps[i] = micros();

    data[i] = analogReadMilliVolts(4);
    

    // sample(i);
  }
}

void teleplotData(){

  for (int i = 0; i < num_samples; i++){
    Serial.print(">ADC Read:");
    Serial.println(data[i]);
  }
}