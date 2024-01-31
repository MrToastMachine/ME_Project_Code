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

void transmitSignal(){
  while(true){
    digitalWrite(trigPin, HIGH);
    delay(2000);
    Serial.println("Still going...");
    digitalWrite(trigPin, LOW);
    delay(1);

  }
}

void loop() {
  // put your main code here, to run repeatedly:
  distance = getDistance();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(500);

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