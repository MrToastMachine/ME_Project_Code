#include <Arduino.h>

//FUNCTION DECLARATIONS
void getRandomArray();
void fetchData();
void printData();
void writeData();
float getDistance();

const int num_datapoints = 100;

int data[2][num_datapoints] = {};

const int trigPin = 5;
const int echoPin = 6;

float distance = 0.0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("fuckin tasty baby...");

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  /* - Testing US-100 code
  distance = getDistance();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(500);
  */

  getRandomArray();


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

float getDistance(){
  float echoTime;
  float calcDist;

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  echoTime = pulseIn(echoPin, HIGH);

  calcDist = echoTime * 0.034 / 2;

  return calcDist;

}

void getRandomArray(){

  fetchData();
  delay(100);
  printData();
  // writeData();

  // Wait for a moment before generating a new set of random numbers
  delay(1000);
}

// generate random data to fill array
void fetchData(){
  // Seed the random number generator with an analogRead value
  randomSeed(analogRead(0));

  for (int i = 0; i < num_datapoints; i++){
    data[0][i] = micros();
    data[1][i] = random(100);
    delayMicroseconds(10);
  }
}

// print array to Serial
void printData(){
  Serial.print("[");
  for (int i = 0; i < num_datapoints - 1; i++){
    Serial.print(data[0][i]);
    Serial.print(",");
    Serial.print(data[1][i]);
    Serial.print(";");
  }
  Serial.print(data[0][num_datapoints - 1]);
  Serial.print(",");
  Serial.print(data[1][num_datapoints - 1]);
  Serial.print("]");
}

void writeData(){
  Serial.write((uint8_t*)data, 2 * num_datapoints * sizeof(int));
}