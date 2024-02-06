#include "driver/gpio.h"
#include "driver/adc.h"

#define ADC_CHANNEL ADC1_CHANNEL_4

// #define PERIOD 10  // period in us
#define SAMPLE_FREQ 40  // sample freq in kHz

unsigned long last_us = 0L;
int period_us = (int)(1000/SAMPLE_FREQ);

int num_samples = 10;
int read_val = 0;

/*
Put array here to hold sampled values
- Know length before sampling starts -> 3000
- Can send entire array over Serial then maybe
*/

int timestamps[num_samples];

void setup(){
  Serial.begin(115200);

  adc1_config_channel_atten(ADC_CHANNEL, ADC_ATTEN_DB_11);

  Serial.println("Starting program");
}

void loop ()
{
  delay(5000);

  Serial.println("Collecting Data...");
  get_x_samples(num_samples);


}

void print_timestamps(){
  // Serial.println("Printing Timestamps... ")
  for(int i = 0; i < num_samples; i++){
    Serial.print((String)i + " : ");
    Serial.prinln(timestamps[i]);
  }
}

void get_x_samples(int n_samples){
  last_us = 0;

  for (int i = 0; i < n_samples; i++){
    if (micros() - last_us > period_us){
        last_us += period_us ;
        // sample();
        Serial.print(micros());
    }
  }
}

void sample ()
{
  int readVal = adc1_get_raw(ADC_CHANNEL);

  Serial.println((String)readVal);
}