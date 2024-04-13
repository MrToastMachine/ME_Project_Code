/* Collector Board Code Slave
Operations:
    - Master Board (not this one) sends request over Wifi to this board
    - This board triggers and collects interrupts for each of its sensors
      sequentially
    - The interrupts are parsed into objects and sizes (STRUCT???)
    - Once collection and parsing complete, send 3 structs back to master

Other Notes
    - Timestamps?


*/

#include <Arduino.h>
#include <vector>

void IRAM_ATTR reflectionDetect();
void parseInterruptsToObjects(std::vector<std::vector<int>>& sensor_X_interrupt_times);
void collectSensorData();
void pulseTrigPinX(int trigPin);
float getDistFromMicros(int uS);

//float getRealDistance();
//void printIntTriggers();

const int sensor_A_trigPin = 1;
const int sensor_B_trigPin = 2;
const int sensor_C_trigPin = 3;

const int sensor_A_interruptPin = 4;
const int sensor_B_interruptPin = 5;
const int sensor_C_interruptPin = 6;

float distance = 0.0;
int trig_time = 0;
int interrupt_time = 0;

const int MAX_RANGE = 30000;
const int MIN_RANGE = 2000;

// min num interrupts to classify as object
const int MIN_COUNT_FOR_OBJECT = 15;
// max time allowed between interrupts to be part of same object
const int MAX_DELTA = 30;


//sensor_X_interrupt_times[0] => start times
//sensor_X_interrupt_times[1] => lengths
std::vector<std::vector<int>> sensor_A_interrupt_times{{},{}};
std::vector<std::vector<int>> sensor_B_interrupt_times{{},{}};
std::vector<std::vector<int>> sensor_C_interrupt_times{{},{}};

// std::vector<int> interrupt_times;

const int NUM_INT_TIMES = 200;
int interrupt_times[NUM_INT_TIMES];
int current_int_index = 0;

int total_interrupt_count = 0;
int total_valid_int_count = 0;

int temp_interrupts[NUM_INT_TIMES]; 
int temp_index = 0;

void IRAM_ATTR reflectionDetect(){
    total_interrupt_count++;
    if(current_int_index < NUM_INT_TIMES){
        // int now_time = micros();

        int delta_time = micros() - trig_time;
        temp_interrupts[temp_index] = delta_time;
        temp_index++;

        total_valid_int_count++;
        if (delta_time < MAX_RANGE && delta_time > MIN_RANGE){
            interrupt_times[current_int_index] = delta_time;
            current_int_index++;
        }
    }
}

void parseInterruptsToObjects(std::vector<std::vector<int>>& sensor_X_interrupt_times){
    int current_object_start = interrupt_times[0];

    int count = 1;

    for (int i = 1; i < NUM_INT_TIMES; i++){
        if (interrupt_times[i] < 1200){
            continue;
        }

        int delta = interrupt_times[i] - interrupt_times[i-1];

        if (delta < MAX_DELTA){
            count++;
        }
        else {
            if (count >= MIN_COUNT_FOR_OBJECT){

                Serial.print("I'm Here");
                // sensor_X_interrupt_times[0].push_back(current_object_start);
                // sensor_X_interrupt_times[1].push_back(interrupt_times[i-1] - current_object_start);
            }
            current_object_start = interrupt_times[i];
            count = 1;
        }

        
    }       
    if (count >= MIN_COUNT_FOR_OBJECT) {
        // sensor_X_interrupt_times[0].push_back(current_object_start);
        // sensor_X_interrupt_times[1].push_back(interrupt_times[sensor_X_interrupt_times[1].size()-1] - current_object_start);
    }

}

void collectSensorData(){
    // interrupt_times.clear();

    // sensor_A_interrupt_times.clear();
    // sensor_B_interrupt_times.clear();
    // sensor_C_interrupt_times.clear();


    pulseTrigPinX(sensor_A_trigPin);
    delay(50);

    // detachInterrupt(sensor_A_interruptPin);


    for (int i = 0; i < NUM_INT_TIMES; i++){
        // Serial.print("[INTERRUPT]: ");
        // Serial.println(temp_interrupts[i] == 1);
        if (interrupt_times[i] > 0){
            Serial.print(i);
            Serial.print(" : ");
            Serial.print(interrupt_times[i]);
            Serial.print(" : ");
            Serial.print(getDistFromMicros(interrupt_times[i]));
            Serial.println("m");
        }
    }

    // parseInterruptsToObjects(sensor_A_interrupt_times);

    /*
    attachInterrupt(sensor_B_interruptPin, reflectionDetect, HIGH);
    pulseTrigPinX(sensor_B_trigPin);
    delayMicroseconds(30);
    detachInterrupt(sensor_B_interruptPin);
    parseInterruptsToObjects(sensor_B_interrupt_times);

    attachInterrupt(sensor_C_interruptPin, reflectionDetect, HIGH);
    pulseTrigPinX(sensor_C_trigPin);
    delayMicroseconds(30);
    detachInterrupt(sensor_C_interruptPin);
    parseInterruptsToObjects(sensor_C_interrupt_times);
    */
}

void pulseTrigPinX(const int trigPin){
    memset(interrupt_times, 0, sizeof(interrupt_times));
    current_int_index = 0;

    memset(temp_interrupts, 0, sizeof(temp_interrupts));
    temp_index = 0;
    

    Serial.println("SETTING A HIGH");
    digitalWrite(sensor_A_trigPin, HIGH);
    delayMicroseconds(10);
    trig_time = micros();
    Serial.println("SETTING A LOW");
    digitalWrite(sensor_A_trigPin, LOW);

    Serial.print("Trig Time: ");
    Serial.println(trig_time);
}

double getDistFromMicros(int uS){
    double c = 343.0; // Speed of sound m/s
    return c * uS / 2000000.0;
}

void setup(){
    Serial.begin(115200);

    pinMode(sensor_A_trigPin, OUTPUT);
    pinMode(sensor_B_trigPin, OUTPUT);
    pinMode(sensor_C_trigPin, OUTPUT);

    attachInterrupt(sensor_A_interruptPin, reflectionDetect, RISING);

    Serial.println("\nStarting...");
}


void loop(){
    collectSensorData();

    delay(5000);
}

/*
void printIntTriggers(){
    Serial.print("[");
    for (int i = 0; i < MAX_NUM_INTERRUPTS - 1; i++){
        if (interrupt_buffer[i] != 0){
            Serial.print(interrupt_buffer[i]);
            Serial.print(",");
        }
    }
    Serial.print(interrupt_buffer[MAX_NUM_INTERRUPTS-1]-trig_time);
    Serial.println("]");
}
*/

/*
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
*/