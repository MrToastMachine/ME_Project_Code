/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-many-to-one-esp32/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/

/*
Sender code:
- This code is uploaded to the board collecting data from sensors
- The data will be sent to the board with mac address 'broadcastAddress'

*/

#include <esp_now.h>
#include <WiFi.h>

// US Sensor Info
const int trigPin_A = 4;
const int echoPin_A = 5;

const int trigPin_B = 6;
const int echoPin_B = 7;

const int trigPin_C = 1;
const int echoPin_C = 2;

float distance_A = 0.0;
float distance_B = 0.0;
float distance_C = 0.0;

// REPLACE WITH THE RECEIVER'S MAC Address
uint8_t broadcastAddress[] = {0x58, 0xCF, 0x79, 0xDB, 0x11, 0x24};

// Structure example to send data
// Must match the receiver structure
typedef struct sensor_data {
    int id; // must be unique for each sender board
    float sensor_A;
    float sensor_B;
    float sensor_C;
} sensor_data;

// Create a struct_message called myData
sensor_data myData;

// Create peer interface
esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

float getSensorData(int trigPin, int echoPin){
  float echoTime;
  float calcDist;

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  echoTime = pulseIn(echoPin, HIGH);

  calcDist = echoTime * 0.034 / 2;

  Serial.println("----- Sensor Data -----");
  Serial.println(calcDist);
  
  return calcDist;
}

// When request recieved from base station board
void OnDataRecv(const uint8_t * mac_addr, const uint8_t *incomingData, int len){
  myData.id = 1;
  myData.sensor_A = getSensorData(trigPin_A, echoPin_A);
  myData.sensor_B = getSensorData(trigPin_B, echoPin_B);
  myData.sensor_C = getSensorData(trigPin_C, echoPin_C);

  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
}
 
void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
  Serial.println("Beginning Program...");

  // sensor setup
  pinMode(trigPin_A, OUTPUT);
  pinMode(echoPin_A, INPUT);

  pinMode(trigPin_B, OUTPUT);
  pinMode(echoPin_B, INPUT);

  pinMode(trigPin_C, OUTPUT);
  pinMode(echoPin_C, INPUT);

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
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}
 
void loop() {
  // Set values to send
  /*
  myData.id = 1;
  myData.sensor_A = getSensorData(trigPin_A, echoPin_A);
  myData.sensor_B = getSensorData(trigPin_B, echoPin_B);
  myData.sensor_C = getSensorData(trigPin_C, echoPin_C);

  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  delay(3000);
  */
}
