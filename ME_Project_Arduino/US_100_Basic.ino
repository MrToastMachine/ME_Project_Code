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
  // put your main code here, to run repeatedly:
  Serial.println("Got here!!!");
  distance = getDistance();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(50);

}

float getDistance(){
  float echoTime;
  float calcDist;

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  echoTime = pulseIn(echoPin, HIGH);

  calcDist = echoTime / 148.0;

  return calcDist;

}