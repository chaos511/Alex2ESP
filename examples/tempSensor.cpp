#include <Arduino.h>

#ifdef ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif

#include <Alex2ESP.h>

// Define constants for WiFi and Alexa Client configuration
const char *WIFI_SSID = "";

const char *ALEXA_USERNAME = "";
const char *ALEXA_PASSWORD = "";
const char *ALEXA_ROOT_TOPIC = "";

// Create the Alexa client object
Alex2ESP alexClient;
AlexaDevice* device1;

void setup() {
  
  // Initialize serial communication for debugging
  Serial.begin(74880);

  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID);

  Serial.print("[WIFI] Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }

  Serial.println();
  Serial.printf("[WIFI] Connected to SSID: %s, IP address: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());

  // Initialize the Alexa client
  alexClient.begin(ALEXA_USERNAME, ALEXA_PASSWORD, ALEXA_ROOT_TOPIC);

  // Register a new device with a unique ID and name
  device1 = alexClient.getDevice("ESP Temp", "ESP-01");

  // Set the device's display category to TEMPERATURE_SENSOR
  device1->setDisplayCategory(DisplayCategory::TEMPERATURE_SENSOR);

  // Add a temperature sensor capability to the device
  device1->addCapability(AlexaInterfaceType::TEMPERATURE_SENSOR);

  // Register event listener for "ReportState" directive
  device1->registerEvent("ReportState", [](const JsonDocument& directive, const AlexaInterfaceType& type) {
    // Build and send status report
    device1->buildStatusMessage(directive["header"]["correlationToken"])
      .AddHealthProp(EndpointHealth::OK)
      .AddTemperatureSensorProp(TemperatureSensorScale::FAHRENHEIT,69)
      .send();
  });

}

void loop() {
  // Process Alexa client communication
  alexClient.loop();
}
