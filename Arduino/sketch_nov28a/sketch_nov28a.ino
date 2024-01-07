#include <WiFi.h>
#include <ESPAsyncWebSrv.h>

const char *ssid = "OMahony";
const char *password = "Toby&Ellie111";

const int analogPin = 34; // Analog pin for temperature sensor
float sensorReading = 0.0;
float temperature = 0.0;

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());

  // Route for root
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    String html = "<html><body>";
    html += "<h1>ESP32 Temperature</h1>";
    html += "<p>Temperature: " + String(temperature) + " &deg;C</p>";
    html += "</body></html>";
    request->send(200, "text/html", html);
  });

  // Start server
  server.begin();


}

void loop() {
  // Read analog temperature
  sensorReading = (analogRead(0) / 4095.0) * 5.0;

  temperature = (sensorReading - 1.375) / 0.0225;

  Serial.print(temperature);
  Serial.println(" deg Celsius");

  delay(1000); // Update every 1 second
}