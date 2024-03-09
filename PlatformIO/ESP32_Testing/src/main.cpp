#include <Arduino.h>

void IRAM_ATTR OLD_reflectionDetect();
void IRAM_ATTR reflectionDetect();
float getRealDistance();
void printIntTriggers();

const int trigPin = 1;
const int echoPin = 2;

const int interruptPin = 4;

float distance = 0.0;
int trig_time = 0;
int int_time = 0;

const int buffer_len = 1000;
int interrupt_buffer[buffer_len];
int current_buffer_pos = 0;

void IRAM_ATTR OLD_reflectionDetect(){
    if(current_buffer_pos < buffer_len){
        int now_time = micros();
        // if (now_time - trig_time > 2000){
        if (now_time - trig_time > 2000 ){
            if (current_buffer_pos == 0 || now_time - interrupt_buffer[current_buffer_pos-1] > 500){
                interrupt_buffer[current_buffer_pos] = now_time;
                current_buffer_pos++;
            }
        }
    }
}

void IRAM_ATTR reflectionDetect(){
    if(current_buffer_pos < buffer_len){
        int delta_time = micros() - trig_time;
        if (delta_time < 30000 && delta_time > 0){
            interrupt_buffer[current_buffer_pos] = delta_time;
            current_buffer_pos++;
        }
    }
}

float getRealDistance(){
    float echoTime;
    float calcDist;

    memset(interrupt_buffer, 0, sizeof(interrupt_buffer));
    current_buffer_pos = 0;

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    trig_time = micros();
    digitalWrite(trigPin, LOW);

    echoTime = pulseIn(echoPin, HIGH);

    calcDist = echoTime * 0.034 / 2;

    return calcDist;

}

void printIntTriggers(){
    Serial.print("[");
    for (int i = 0; i < buffer_len - 1; i++){
        if (interrupt_buffer[i] != 0){
            Serial.print(interrupt_buffer[i]);
            Serial.print(",");
        }
    }
    Serial.print(interrupt_buffer[buffer_len-1]-trig_time);
    Serial.println("]");
}

void setup(){
    Serial.begin(115200);

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    attachInterrupt(interruptPin, reflectionDetect, HIGH);

    Serial.println("\nStarting...");
}


void loop(){
    distance = getRealDistance();
    // Serial.print("[Main] Distance: ");
    // Serial.println(distance);
    delay(50);

    printIntTriggers();

    delay(1000);
}