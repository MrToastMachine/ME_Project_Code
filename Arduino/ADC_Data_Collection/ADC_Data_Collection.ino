#include "driver/gpio.h"
#include "driver/adc.h"

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
  delay(5000);



  // Serial.println("Collecting Data...");
  get_x_samples(num_samples);
  // print

  // delay(100);

  // printTimestamps();
}#include <driver/i2s.h>
#include <driver/adc.h>
#include <Arduino.h>

// I2S
#define I2S_SAMPLE_RATE (3000)
#define ADC_INPUT (ADC1_CHANNEL_4) //pin 32
#define I2S_DMA_BUF_LEN (8)

// The 4 high bits are the channel, and the data is inverted
size_t bytes_read;
uint16_t buffer[I2S_DMA_BUF_LEN] = {0};

unsigned long lastTimePrinted;
unsigned long loopTime = 0;

void i2sInit() {
  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_ADC_BUILT_IN),
    .sample_rate =  I2S_SAMPLE_RATE,              // The format of the signal using ADC_BUILT_IN
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT, // is fixed at 12bit, stereo, MSB
    .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
    .communication_format = I2S_COMM_FORMAT_I2S_MSB,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 2,
    .dma_buf_len = I2S_DMA_BUF_LEN,
    .use_apll = false,
    .tx_desc_auto_clear = false,
    .fixed_mclk = 0
  };

  i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
  i2s_set_adc_mode(ADC_UNIT_1, ADC_INPUT);
  i2s_adc_enable(I2S_NUM_0);
  adc1_config_channel_atten(ADC_INPUT, ADC_ATTEN_DB_11);
}

void setup() {
  Serial.begin(115200);

  i2sInit();
}

void loop() {

  unsigned long startMicros = ESP.getCycleCount();

  i2s_read(I2S_NUM_0, &buffer, sizeof(buffer), &bytes_read, 0);

  unsigned long stopMicros = ESP.getCycleCount();

  loopTime = stopMicros - startMicros;

  if (millis() - lastTimePrinted >= 100) {
    Serial.println("------------------");
    Serial.println(buffer[0] & 0x0FFF);
    Serial.println(loopTime);
    lastTimePrinted = millis();
  }
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

void get_x_samples(int n_samples) {
  // last_us = micros();

  for (int i = 0; i < n_samples; i++) {
    last_us = micros();
    while (micros() - last_us < period_us) {}

    timestamps[i] = micros();


    sample(i);
  }
}

void sample(int sample_index) {
  timestamps[sample_index] = micros();

  int readVal = adc1_get_raw(ADC_CHANNEL);

  Serial.println(readVal);

}