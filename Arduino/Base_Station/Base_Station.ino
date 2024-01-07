/*
Base station code:
- This code is uploaded to the board collecting data the other ESP32 boards 
- The data is requested by the base station and collected when the
     other boards send back the JSON packets

*/

#include <esp_now.h>
#include <WiFi.h>
#include <ArduinoJson.h>

// Structure example to receive data
// Must match the sender structure
typedef struct sensor_data {
  int id;
  float sensor_A;
  float sensor_B;
  float sensor_C;
}sensor_data;

// Create a struct_message called myData
sensor_data myData;

// Create a structure to hold the readings from each board
sensor_data board1;

// BOARD MAC ADDRESSES
uint8_t board1_Address[] = {0x58, 0xCF, 0x79, 0xD7, 0x24, 0x6C};

// Create peer interface
esp_now_peer_info_t peerInfo_b1;

int timestamp = 0;

// time between polls from sensor boards, in ms
int time_between_scans = 500;


void SendJsonOverSerial(int board_id, int timestamp, float sensor_A, float sensor_B, float sensor_C){
  const size_t capacity = JSON_OBJECT_SIZE(5);
  StaticJsonDocument<capacity> data;
  
  data["board_id"] = board_id;
  data["ts"] = timestamp;
  data["sensor_A"] = sensor_A;
  data["sensor_B"] = sensor_B;
  data["sensor_C"] = sensor_C;

  // Serialize JSON to a string
  String jsonStr;
  serializeJson(data, jsonStr);

  // Send JSON packet over serial
  Serial.println(jsonStr);
}

// Create an array with all the structures
// struct_message boardsStruct[3] = {board1, board2, board3};

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac_addr, const uint8_t *incomingData, int len) {
  char macStr[18];

  timestamp = millis();

  // Serial.print("Packet received from: ");
  // snprinf: Composes a string with the same text that would be printed if format was used on printf,
  // but instead of being printed, the content is stored as a C string
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  //Serial.println(macStr);
  memcpy(&myData, incomingData, sizeof(myData));
  //Serial.printf("Board ID %u: %u bytes\n", myData.id, len);
  // Update the structures with the new incoming data
  board1.sensor_A = myData.sensor_A;
  board1.sensor_B = myData.sensor_B;
  board1.sensor_C = myData.sensor_C;

  SendJsonOverSerial(myData.id, timestamp, board1.sensor_A,board1.sensor_B,board1.sensor_C);
}

void setup() {
  //Initialize Serial Monitor
  Serial.begin(115200);
  
  //Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  //Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);

  // Register peers
  memcpy(peerInfo_b1.peer_addr, board1_Address, 6);
  peerInfo_b1.channel = 0;  
  peerInfo_b1.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo_b1) != ESP_OK){
    Serial.println("Failed to add board 1 peer");
    return;
  }
}
 
void loop() {
  uint8_t mode = 1;

  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(board1_Address, &mode, sizeof(mode));

  delay(time_between_scans);  
}
