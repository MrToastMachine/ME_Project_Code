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
#include <esp_now.h>
#include <WiFi.h>
#include <vector>

void IRAM_ATTR reflectionDetect();
void parseInterruptsToObjects(std::vector<std::vector<int>>& sensor_X_interrupt_times);
void collectSensorData();
void pulseTrigPinX(int trigPin);
double getDistFromMicros(int uS);
void clearAllStoredData();
void printAllInterrupts();
void printObjectsDetected();
//float getRealDistance();
//void printIntTriggers();

typedef struct objects_detected {
    std::vector<int> object_starts{};
    std::vector<int> object_sizes{};
} objects_detected;

typedef struct sensor_data {
    char sensor_id;
    objects_detected sensor_A_objs;
    objects_detected sensor_B_objs;
    objects_detected sensor_C_objs;
} sensor_data;

sensor_data myData;


// SET BOARD ID TO MATCH SENSOR UNIT
int board_id = 1;

uint8_t MASTER_BOARD_ADD[] = {0x58, 0xCF, 0x79, 0xD7, 0x24, 0x6C};

esp_now_peer_info_t peerInfo;


// SENSOR INFORMATION
const int sensor_A_trigPin = 1;
const int sensor_B_trigPin = 2;
const int sensor_C_trigPin = 3;

const int sensor_A_interruptPin = 4;
const int sensor_B_interruptPin = 5;
const int sensor_C_interruptPin = 6;

int trig_time = 0;


// OBJECT DETECTION PARAMETERS
const int MAX_RANGE = 30000;
const int MIN_RANGE = 2000;

// min num interrupts to classify as object
const int MIN_COUNT_FOR_OBJECT = 3;
// max time allowed between interrupts to be part of same object
const int MAX_DELTA = 30;


//sensor_X_interrupt_times[0] => start times
//sensor_X_interrupt_times[1] => lengths

// std::vector<int> interrupt_times;


// INTERRUPTS 
const int NUM_INT_TIMES = 500;
int interrupt_times[NUM_INT_TIMES];
// std::vector<int> interrupt_times{};
int current_int_index = 0;

int total_interrupt_count = 0;


void IRAM_ATTR reflectionDetect(){
    total_interrupt_count++;
    if(current_int_index < NUM_INT_TIMES){

        int delta_time = micros() - trig_time;

        if (delta_time < MAX_RANGE && delta_time > MIN_RANGE){
            interrupt_times[current_int_index] = delta_time;
            current_int_index++;
        }
    }
}


void parseInterruptsToObjects(objects_detected& obj_data_address){
    int current_object_start = interrupt_times[0];

    int count = 1;

    for (int i = 1; i < NUM_INT_TIMES; i++){
        if (interrupt_times[i] == 0){
            if (count >= MIN_COUNT_FOR_OBJECT) {
                obj_data_address.object_starts.push_back(current_object_start);
                obj_data_address.object_sizes.push_back(interrupt_times[i-1] - current_object_start);

                // sensor_X_interrupt_times[0].push_back(current_object_start);
                // sensor_X_interrupt_times[1].push_back(interrupt_times[sensor_X_interrupt_times[1].size()-1] - current_object_start);
            }
            return;
        }

        int delta = interrupt_times[i] - interrupt_times[i-1];

        if (delta < MAX_DELTA){
            count++;
        }
        else {
            if (count >= MIN_COUNT_FOR_OBJECT){
                obj_data_address.object_starts.push_back(current_object_start);
                obj_data_address.object_sizes.push_back(interrupt_times[i-1] - current_object_start);

                // sensor_X_interrupt_times[0].push_back(current_object_start);
                // sensor_X_interrupt_times[1].push_back(interrupt_times[i-1] - current_object_start);
            }
            current_object_start = interrupt_times[i];
            count = 1;
        }

        
    }       
    if (count >= MIN_COUNT_FOR_OBJECT) {
        obj_data_address.object_starts.push_back(current_object_start);
        obj_data_address.object_sizes.push_back(interrupt_times[NUM_INT_TIMES-1] - current_object_start);

        // sensor_X_interrupt_times[0].push_back(current_object_start);
        // sensor_X_interrupt_times[1].push_back(interrupt_times[sensor_X_interrupt_times[1].size()-1] - current_object_start);
    }

}

void clearAllStoredData(){
    myData.sensor_A_objs.object_starts.clear();
    myData.sensor_A_objs.object_sizes.clear();

    myData.sensor_B_objs.object_starts.clear();
    myData.sensor_B_objs.object_sizes.clear();

    myData.sensor_C_objs.object_starts.clear();
    myData.sensor_C_objs.object_sizes.clear();
}

void printAllInterrupts(){
    for (int i = 0; i < NUM_INT_TIMES; i++){
        // Serial.print("[INTERRUPT]: ");
        // Serial.println(temp_interrupts[i] == 1);
        if (interrupt_times[i] == 0){
            return;
        }
        Serial.print(i);
        Serial.print(" : ");
        Serial.print(interrupt_times[i]);
        Serial.print(" : ");
        Serial.print(getDistFromMicros(interrupt_times[i]));
        Serial.println("m");
    }
}

void printObjectsDetected(){
    int num_A_detects = myData.sensor_A_objs.object_starts.size();
    Serial.print("Num Sensor A objects: ");
    Serial.println(num_A_detects);
    for (int i = 0; i < num_A_detects; i++){
        Serial.print(myData.sensor_A_objs.object_starts[i]);
        Serial.print(" : ");
        Serial.print(myData.sensor_A_objs.object_sizes[i]);
        Serial.println();
    }

    int num_B_detects = myData.sensor_B_objs.object_starts.size();
    Serial.print("Num Sensor B objects: ");
    Serial.println(num_B_detects);
    for (int i = 0; i < num_B_detects; i++){
        Serial.print(myData.sensor_B_objs.object_starts[i]);
        Serial.print(" : ");
        Serial.print(myData.sensor_B_objs.object_sizes[i]);
        Serial.println();
    }

    int num_C_detects = myData.sensor_C_objs.object_starts.size();
    Serial.print("Num Sensor C objects: ");
    Serial.println(num_C_detects);
    for (int i = 0; i < num_C_detects; i++){
        Serial.print(myData.sensor_C_objs.object_starts[i]);
        Serial.print(" : ");
        Serial.print(myData.sensor_C_objs.object_sizes[i]);
        Serial.println();
    }

}

void collectSensorData(){

    clearAllStoredData();
    
    // SENSOR A DATA COLLECTION

    attachInterrupt(sensor_A_interruptPin, reflectionDetect, HIGH);

    pulseTrigPinX(sensor_A_trigPin);

    Serial.println("[DEBUG] Before Delay");
    delay(60);

    Serial.println("[DEBUG] Before detaching interrupt");
    detachInterrupt(sensor_A_interruptPin);

    Serial.println("[DEBUG] Before parsing data");

    parseInterruptsToObjects(myData.sensor_A_objs);

    Serial.println("[DEBUG] After parsing data");

    // SENSOR B DATA COLLECTION
    
    // interrupt_times.clear();
    // total_interrupt_count = 0;

    attachInterrupt(sensor_B_interruptPin, reflectionDetect, HIGH);

    pulseTrigPinX(sensor_B_trigPin);
    delay(60);

    detachInterrupt(sensor_B_interruptPin);

    parseInterruptsToObjects(myData.sensor_B_objs);

    // SENSOR C DATA COLLECTION

    // interrupt_times.clear();
    // total_interrupt_count = 0;

    attachInterrupt(sensor_A_interruptPin, reflectionDetect, RISING);

    pulseTrigPinX(sensor_A_trigPin);
    delay(60);

    detachInterrupt(sensor_A_interruptPin);

    parseInterruptsToObjects(myData.sensor_A_objs);

    printObjectsDetected();

}

void pulseTrigPinX(const int trigPin){
    memset(interrupt_times, 0, sizeof(interrupt_times));
    current_int_index = 0;

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    trig_time = micros();
    digitalWrite(trigPin, LOW);

    Serial.print("Trig Time: ");
    Serial.println(trig_time);
}

double getDistFromMicros(int uS){
    double c = 343.0; // Speed of sound m/s
    return c * uS / 2000000.0;
}

// FUNCTIONS CALLED WHEN SENDING OR RECIEVING DATA

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

// When request recieved from base station board
void OnDataRecv(const uint8_t * mac_addr, const uint8_t *incomingData, int len){
  collectSensorData();

  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(MASTER_BOARD_ADD, (uint8_t *) &myData, sizeof(myData));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
}

void setup(){
    Serial.begin(115200);

    pinMode(sensor_A_trigPin, OUTPUT);
    pinMode(sensor_B_trigPin, OUTPUT);
    pinMode(sensor_C_trigPin, OUTPUT);

    // attachInterrupt(sensor_A_interruptPin, reflectionDetect, RISING);

    // COMMUNICATIONS SETUP

    // Set device as a Wi-Fi Station
    WiFi.mode(WIFI_STA);

    // Init ESP-NOW
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    // Once ESPNow is successfully Init, we will register for Send CB to
    // get the status of Trasnmitted packet
    esp_now_register_send_cb(OnDataSent);
    esp_now_register_recv_cb(OnDataRecv);
    
    // Register peer
    memcpy(peerInfo.peer_addr, MASTER_BOARD_ADD, 6);
    peerInfo.channel = 0;  
    peerInfo.encrypt = false;
    
    // Add peer        
    if (esp_now_add_peer(&peerInfo) != ESP_OK){
        Serial.println("Failed to add peer");
        return;
  }

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