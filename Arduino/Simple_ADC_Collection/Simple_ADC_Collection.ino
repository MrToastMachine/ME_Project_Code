#include "driver/gpio.h"
#include "driver/adc.h"

const int INPUT_PIN = 4;
const int ANALOG_MAX_VAL = 4095;

#define ADC_CHANNEL ADC1_CHANNEL_4

int sample_rate = 100; // in Hz

sample_delay = (1/sample_rate) * 1000; // in ms

void setup(){
  Serial.begin(115200);

  adc1_config_channel_atten(ADC_CHANNEL, ADC_ATTEN_DB_11);

  // pinMode(INPUT_PIN, INPUT);
}


void loop(){
  int readVal = adc1_get_raw(ADC_CHANNEL);

  Serial.println((String)readVal);

  delay(sample_delay);
}