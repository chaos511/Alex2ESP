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
AlexaDevice *device1;

// Initial state for the blinds (PowerController)
PowerController outputState = PowerController::OFF;

void setup()
{
  // Initialize the LED as output
  pinMode(LED_BUILTIN, OUTPUT);

  // Initialize serial communication for debugging
  Serial.begin(74880);

  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID);

  Serial.print("[WIFI] Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(100);
  }

  Serial.println();
  Serial.printf("[WIFI] Connected to SSID: %s, IP address: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());

  // Initialize the Alexa client
  alexClient.begin(ALEXA_USERNAME, ALEXA_PASSWORD, ALEXA_ROOT_TOPIC);

  String deviceName="Bedroom Blinds";

  // Register a new device with a unique ID and name
  device1 = alexClient.getDevice(deviceName, "ESP-01");

  // Set the device's display category to LIGHT
  device1->setDisplayCategory(DisplayCategory::LIGHT);

  //a power controller will allow us to "turn on/off" the blinds (not really usefull but is possable)
  device1->addCapability(AlexaInterfaceType::POWER_CONTROLLER);

  // Add a toggle controller capability to the device
  AlexaInterface* toggleController=device1->addCapability(AlexaInterfaceType::TOGGLE_CONTROLLER);
  
  //toggle controllers are unique in that they require some additinal attrabutes by default we first need to set an instance name
  toggleController->setInstance("ESP-01.Toggle");

  //we also need to set a name for the interface, this is a sub device listed under the main device name
  //to allow open/close commands as well as on/off commands we can use the same name as device name
  toggleController->addFriendlyName(deviceName.c_str(),"en-US");

  // Example of adding action mappings to map open/close to on/off
  ActionMapping closeMapping({AlexaActions::Close}, "TurnOn");

  ActionMapping openMapping({AlexaActions::Open}, "TurnOff");
  // the full supported list of alexa action mappings can be found on
  // https://developer.amazon.com/en-US/docs/alexa/device-apis/alexa-discovery-objects.html#action-mapping
  //note, only 'generic controller interffaces support action mappings for a full list visit
  //https://developer.amazon.com/en-US/docs/alexa/device-apis/generic-controllers.html


  toggleController->addActionMapping(closeMapping);
  toggleController->addActionMapping(openMapping);

  // Register event listener for "ReportState" directive
  device1->registerEvent("ReportState", [](const JsonDocument &directive, const AlexaInterfaceType &type)
                         {

    Serial.println("Report state requested.");

    // Build and send status report
    device1->buildStatusMessage(directive["header"]["correlationToken"])
      .AddHealthProp(EndpointHealth::OK)
        .AddToggleControllerProp(outputState,"ESP-01.Toggle")
        .AddPowerControllerProp(outputState)
      .send(); });

  // Register event listener for "Event" directive to handle state changes
  device1->registerEvent("Event", [](const JsonDocument &directive, const AlexaInterfaceType &type)
                         {
    if (type == AlexaInterfaceType::TOGGLE_CONTROLLER||type == AlexaInterfaceType::POWER_CONTROLLER) {
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
        .AddToggleControllerProp(outputState,"ESP-01.Toggle")
        .AddPowerControllerProp(outputState)
        .send();
    } });
}


void loop()
{
  // Process Alexa client communication
  alexClient.loop();

  // Update the state of the LED based on the power controller state
  digitalWrite(LED_BUILTIN, outputState != PowerController::ON);
}
