#include <Arduino.h>
#include <ArduinoHttpClient.h>
#include <WiFi.h>

// Fake WiFi credentials (not used in simulation)
const char* ssid = "SIM_WIFI";
const char* password = "SIM_PASS";

// dweet.io settings
const char* server = "dweet.io";
const int port = 80;
const char* thingName = "esp32-software-only-demo";

WiFiClient wifi;
HttpClient client = HttpClient(wifi, server, port);

void setup() {
    Serial.begin(9600);
    delay(1000);

    Serial.println("ESP32 REST API Simulation Started");
}

void loop() {
    int sensorValue = random(20, 40);  // Fake temperature

    String url = "/dweet/for/";
    url += thingName;
    url += "?temperature=";
    url += sensorValue;

    Serial.println("Sending data to dweet.io...");
    client.get(url);

    int statusCode = client.responseStatusCode();
    String response = client.responseBody();

    Serial.print("Status Code: ");
    Serial.println(statusCode);

    Serial.println("Response:");
    Serial.println(response);

    delay(5000);  // Send every 5 seconds
}
