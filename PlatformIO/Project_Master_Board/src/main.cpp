#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <vector>
#include <ArduinoJson.h>

const int MAX_NUM_OBJECTS = 5;

typedef struct objects_detected {
    int object_starts[MAX_NUM_OBJECTS];
    int object_sizes[MAX_NUM_OBJECTS];
} objects_detected;

typedef struct sensor_data {
    char sensor_id;
    objects_detected sensor_A_objs;
    objects_detected sensor_B_objs;
    objects_detected sensor_C_objs;
} sensor_data;

// put function declarations here:
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
void OnDataRecv(const uint8_t * mac_addr, const uint8_t *incomingData, int len);
void printObjectsDetected(sensor_data myData);
void resetObjectsDetected(objects_detected& objs);
void resetSensorData(sensor_data& sd);
double getDistFromMicros(int uS_val);


sensor_data board_01;
sensor_data board_02;
sensor_data board_03;

// BOARD MAC ADDRESSES
uint8_t board_01_MAC[] = {0x58, 0xCF, 0x79, 0xD8, 0x42, 0xD4};
uint8_t board_02_MAC[] = {0x58, 0xCF, 0x79, 0xDB, 0x11, 0x24};
uint8_t board_03_MAC[] = {0x58, 0xCF, 0x79, 0xD8, 0x30, 0x94};

esp_now_peer_info_t peerInfo_b1;
esp_now_peer_info_t peerInfo_b2;
esp_now_peer_info_t peerInfo_b3;

const int TIME_BETWEEN_SCANS = 2000;
// const int DELAY_BETWEEN_BOARDS;

bool data_recieved = false;
int active_board = 1;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
	Serial.print("\r\nLast Packet Send Status:\t");
	Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void OnDataRecv(const uint8_t * mac_addr, const uint8_t *incomingData, int len) {
	
	switch (active_board)
	{
	case 1:
		memcpy(&board_01, incomingData, sizeof(board_01));
		// Serial.println("Collected data from board 1\n");
		break;

	case 2:
		memcpy(&board_02, incomingData, sizeof(board_02));
		// Serial.println("Collected data from board 2\n");
		break;

	case 3:
		memcpy(&board_03, incomingData, sizeof(board_03));
		// Serial.println("Collected data from board 3\n");
		break;
	
	default:
		Serial.println("[ERROR] No active board!");
		break;
	}

	data_recieved = true;
}

void printObjectsDetected(sensor_data myData){;
    Serial.println("Sensor A objects: ");
    for (int i = 0; i < MAX_NUM_OBJECTS; i++){
		if(myData.sensor_A_objs.object_starts[i] == 0){ continue; }
        // Serial.print(myData.sensor_A_objs.object_starts[i]);
        Serial.print(getDistFromMicros(myData.sensor_A_objs.object_starts[i]));
        Serial.print(" : ");
        Serial.print(myData.sensor_A_objs.object_sizes[i]);
        Serial.println();
    }

    Serial.println("Sensor B objects: ");
    for (int i = 0; i < MAX_NUM_OBJECTS; i++){
		if(myData.sensor_B_objs.object_starts[i] == 0){ continue; }
        Serial.print(getDistFromMicros(myData.sensor_B_objs.object_starts[i]));
        Serial.print(" : ");
        Serial.print(myData.sensor_B_objs.object_sizes[i]);
        Serial.println();
    }

    Serial.println("Sensor C objects: ");
    for (int i = 0; i < MAX_NUM_OBJECTS; i++){
		if(myData.sensor_C_objs.object_starts[i] == 0){ continue; }
        Serial.print(getDistFromMicros(myData.sensor_C_objs.object_starts[i]));
        Serial.print(" : ");
        Serial.print(myData.sensor_C_objs.object_sizes[i]);
        Serial.println();
    }
	Serial.println();
}

// Function to reset all data in objects_detected
void resetObjectsDetected(objects_detected& objs) {
    memset(objs.object_starts, 0, sizeof(objs.object_starts));
    memset(objs.object_sizes, 0, sizeof(objs.object_sizes));
}

// Function to reset all sensor data
void resetSensorData(sensor_data& sd) {
    resetObjectsDetected(sd.sensor_A_objs);
    resetObjectsDetected(sd.sensor_B_objs);
    resetObjectsDetected(sd.sensor_C_objs);
}

double getDistFromMicros(int uS_val){
    double c = 343.0; // Speed of sound m/s
    return c * uS_val / 2000000.0;
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
    esp_now_register_send_cb(OnDataSent);
    esp_now_register_recv_cb(OnDataRecv);

    // Register peers
    memcpy(peerInfo_b1.peer_addr, board_01_MAC, 6);
    peerInfo_b1.channel = 0;  
    peerInfo_b1.encrypt = false;

	memcpy(peerInfo_b2.peer_addr, board_02_MAC, 6);
    peerInfo_b2.channel = 0;  
    peerInfo_b2.encrypt = false;

	memcpy(peerInfo_b3.peer_addr, board_03_MAC, 6);
    peerInfo_b3.channel = 0;  
    peerInfo_b3.encrypt = false;
    
    // Add peer        
    if (esp_now_add_peer(&peerInfo_b1) != ESP_OK){
      Serial.println("Failed to add board 1 peer");
      return;
    }
	if (esp_now_add_peer(&peerInfo_b2) != ESP_OK){
      Serial.println("Failed to add board 2 peer");
      return;
    }
	if (esp_now_add_peer(&peerInfo_b3) != ESP_OK){
      Serial.println("Failed to add board 3 peer");
      return;
    }
}

void loop() {
	uint8_t mode = 1;

	resetSensorData(board_01);
	resetSensorData(board_02);
	resetSensorData(board_03);

	// Serial.println("Requesting Data from board 01...");
	active_board = 1;
	esp_err_t result_01 = esp_now_send(board_01_MAC, &mode, sizeof(mode));

	while (!data_recieved){
		delay(10);
	}
	data_recieved = false;
	delay(20);

	// Serial.println("Requesting Data from board 02...");
	active_board = 2;
	esp_err_t result_02 = esp_now_send(board_02_MAC, &mode, sizeof(mode));

	while (!data_recieved){
		delay(10);
	}
	data_recieved = false;
	delay(20);

	// Serial.println("Requesting Data from board 03...");
	active_board = 3;
	esp_err_t result_03 = esp_now_send(board_03_MAC, &mode, sizeof(mode));

	while (!data_recieved){
		delay(10);
	}
	data_recieved = false;
	delay(20);

	Serial.println("Data collected from all boards");
	Serial.println();
	Serial.println("Data from board 01: ");
	printObjectsDetected(board_01);
	
	Serial.println("Data from board 02: ");
	printObjectsDetected(board_02);
	
	Serial.println("Data from board 03: ");
	printObjectsDetected(board_03);



	delay(TIME_BETWEEN_SCANS);  
}
