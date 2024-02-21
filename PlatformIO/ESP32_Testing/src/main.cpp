#include <Arduino.h>
#include "driver/gpio.h"
#include "driver/adc.h"

int pot_pin = 0;

#define ADC_CHANNEL ADC1_CHANNEL_4

void setup() {
  Serial.begin(115200);

  adc1_config_channel_atten(ADC_CHANNEL, ADC_ATTEN_DB_11);

  Serial.println("Starting tests...");
}

void loop() {
  pot_pin = adc1_get_raw(ADC_CHANNEL);

  Serial.print("Pot read val: ");
  Serial.println(pot_pin);

  delay(2000);
}
