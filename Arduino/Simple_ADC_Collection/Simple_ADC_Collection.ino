const int INPUT_PIN = 4;
const int ANALOG_MAX_VAL = 4095;

void setup(){
  Serial.begin(115200);

  pinMode(INPUT_PIN, INPUT);
}


void loop(){
  int readVal = analogRead(INPUT_PIN);

  Serial.println((String)readVal);

  delay(10);
}