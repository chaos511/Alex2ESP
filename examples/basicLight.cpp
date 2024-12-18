#include <Arduino.h>

#ifdef ESP32
  #include <WiFi.h>
#else
  #include <ESP8266WiFi.h>
#endif

#include <Alex2ESP.h>

// Define constants for WiFi and Alexa Client configuration
const char* WIFI_SSID = "";

const char* ALEXA_USERNAME = "";
const char* ALEXA_PASSWORD = "";
const char* ALEXA_ROOT_TOPIC = "";

// Create the Alexa client object
Alex2ESP alexClient;
AlexaDevice* device1;

// Initial state for the light (PowerController)
PowerController outputState = PowerController::OFF;

void setup() {
  // Initialize the LED as output
  pinMode(LED_BUILTIN, OUTPUT);
  
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
  device1 = alexClient.getDevice("Test Lamp", "ESP-01");

  // Set the device's display category to LIGHT
  device1->setDisplayCategory(DisplayCategory::LIGHT);

  // Add a power controller capability to the device
  device1->addCapability(AlexaInterfaceType::POWER_CONTROLLER);

  // Register event listener for "ReportState" directive
  device1->registerEvent("ReportState", [](const JsonDocument& directive, const AlexaInterfaceType& type) {
    // Build and send status report
    device1->buildStatusMessage(directive["header"]["correlationToken"])
      .AddHealthProp(EndpointHealth::OK)
      .AddPowerControllerProp(outputState)
      .send();
  });

  // Register event listener for "Event" directive to handle state changes
  device1->registerEvent("Event", [](const JsonDocument& directive, const AlexaInterfaceType& type) {
    if (type == AlexaInterfaceType::POWER_CONTROLLER) {
      if (directive["header"]["name"] == "TurnOn") {
        outputState = PowerController::ON;
        Serial.println("Turning ON");
      } else if (directive["header"]["name"] == "TurnOff") {
        outputState = PowerController::OFF;
        Serial.println("Turning OFF");
      }

      // Send the updated state after change
      device1->buildStatusMessage(directive["header"]["correlationToken"], true)
        .AddHealthProp(EndpointHealth::OK)
        .AddPowerControllerProp(outputState)
        .send();
    }
  });
}

void loop() {
  // Process Alexa client communication
  alexClient.loop();

  // Update the state of the LED based on the power controller state
  digitalWrite(LED_BUILTIN, outputState != PowerController::ON);
}
