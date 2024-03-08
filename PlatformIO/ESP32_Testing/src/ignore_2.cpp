#include <chrono>
#include <Arduino.h>
#include <driver/adc.h>

void setup() {
  Serial.begin(115200);
  // adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_0);
}

void loop() {
  const uint16_t samples = 10000;

  auto t1 = std::chrono::system_clock::now();

  for (uint32_t i=0; i<samples; i++) {
    adc1_get_raw(ADC1_CHANNEL_4); // GPIO32
  }

  auto t2 = std::chrono::system_clock::now();

  std::chrono::duration<double> diff = t2 - t1;
  auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();

  Serial.printf("Samples: %u\n", samples);
  Serial.printf("Duration: %llums\n", ms);
  Serial.printf("KSPS: %0.4f\n\n", static_cast<double>(samples) / ms);
}