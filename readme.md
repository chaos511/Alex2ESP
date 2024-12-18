# Alex2ESP

Alex2ESP is a lightweight C++ library for integrating ESP8266 and ESP32 microcontrollers with Amazon Alexa smart home APIs. The library simplifies the process of creating Alexa-compatible devices using MQTT. 

For more details on how to configure Alex2ESP, visit [Alex2ESP Documentation](https://alex2mqtt.stormysdream.club/).

---

## Features
- Supports various Alexa smart home capabilities.
- Provides action mapping for advanced customization.
- Simple integration with Wi-Fi and MQTT.
- Event-driven architecture for handling Alexa directives.

---

## Quick Start
### Installation
Download the library and include it in your Arduino IDE project:
```cpp
#include <Alex2ESP.h>
```

---

## Creating a Basic Device
### Example: Light Control

Here’s how to create a simple device that controls a light:

First create an instance of the alexa client and initilize it with your MQTT Credentials
```cpp
Alex2ESP alexClient;
```

Credentials can be found at https://alex2mqtt.stormysdream.club/ after logging in with amazin
```cpp
  alexClient.begin(ALEXA_USERNAME, ALEXA_PASSWORD, ALEXA_ROOT_TOPIC);
```

Once initilized you can begin to add virtual devices, in this example we add a power controller to toggle a light
```cpp

  AlexaDevice* device1 = alexClient.getDevice("Test Lamp", "ESP-01");
  device1->setDisplayCategory(DisplayCategory::LIGHT);
  device1->addCapability(AlexaInterfaceType::POWER_CONTROLLER);

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
```
---
### Example: Toggle Controller for Blinds
Alex2ESP also supports action mapping so we can map keywords such as "open" and "close" to a toggle controller 
For a comprehensive list of Alexa actions and mappings, visit the [Alexa Developer Documentation](https://developer.amazon.com/en-US/docs/alexa/device-apis/alexa-discovery-objects.html#action-mapping)

```cpp
AlexaDevice* device = alexClient.getDevice("Bedroom Blinds", "ESP-01");
device->setDisplayCategory(DisplayCategory::LIGHT);

AlexaInterface* toggleController = device->addCapability(AlexaInterfaceType::TOGGLE_CONTROLLER);
toggleController->setInstance("ESP-01.Toggle");
toggleController->addFriendlyName("Bedroom Blinds", "en-US");

ActionMapping closeMapping({AlexaActions::Close}, "TurnOn");
ActionMapping openMapping({AlexaActions::Open}, "TurnOff");
toggleController->addActionMapping(closeMapping);
toggleController->addActionMapping(openMapping);
```

---

## Interface Types
| Alexa Interface Type                                 | Status      |
|-----------------------------------------------------|-------------|
| AlexaInterfaceType::AUTOMATION_MANAGEMENT           | Supported*  |
| AlexaInterfaceType::BRIGHTNESS_CONTROLLER           | Supported*  |
| AlexaInterfaceType::CHANNEL_CONTROLLER              | Supported*  |
| AlexaInterfaceType::COLOR_CONTROLLER                | Supported*  |
| AlexaInterfaceType::COLOR_TEMPERATURE_CONTROLLER    | Supported*  |
| AlexaInterfaceType::CONTACT_SENSOR                  | Supported*  |
| AlexaInterfaceType::POWER_CONTROLLER                | Fully Supported  |
| AlexaInterfaceType::ENDPOINT_HEALTH                 | Supported*  |
| AlexaInterfaceType::TOGGLE_CONTROLLER               | Fully Supported  |
| AlexaInterfaceType::APPLICATION_STATE_REPORTER      | Supported*  |
| AlexaInterfaceType::AUDIO_PLAY_QUEUE                | Supported*  |
| AlexaInterfaceType::AUTHORIZATION_CONTROLLER        | Supported*  |
| AlexaInterfaceType::AUTOMOTIVE_VEHICLE_DATA         | Supported*  |
| AlexaInterfaceType::CAMERA_LIVE_VIEW_CONTROLLER     | Supported*  |
| AlexaInterfaceType::CAMERA_STREAM_CONTROLLER        | Supported*  |
| AlexaInterfaceType::COMMISSIONABLE                  | Supported*  |
| AlexaInterfaceType::CONSENT_MANAGEMENT_CONSENT_REQUIRED_REPORTER | Supported* |
| AlexaInterfaceType::COOKING                         | Supported*  |
| AlexaInterfaceType::DATA_CONTROLLER                 | Supported*  |
| AlexaInterfaceType::DEVICE_USAGE_ESTIMATION         | Supported*  |
| AlexaInterfaceType::DEVICE_USAGE_METER              | Supported*  |
| AlexaInterfaceType::DOORBELL_EVENT_SOURCE           | Supported*  |
| AlexaInterfaceType::EQUALIZER_CONTROLLER            | Supported*  |
| AlexaInterfaceType::INPUT_CONTROLLER                | Supported*  |
| AlexaInterfaceType::INVENTORY_LEVEL_SENSOR          | Supported*  |
| AlexaInterfaceType::INVENTORY_LEVEL_USAGE_SENSOR    | Supported*  |
| AlexaInterfaceType::INVENTORY_USAGE_SENSOR          | Supported*  |
| AlexaInterfaceType::KEYPAD_CONTROLLER               | Supported*  |
| AlexaInterfaceType::LAUNCHER                        | Supported*  |
| AlexaInterfaceType::LOCK_CONTROLLER                 | Supported*  |
| AlexaInterfaceType::MEDIA_PLAYBACK                  | Supported*  |
| AlexaInterfaceType::MEDIA_SEARCH                    | Supported*  |
| AlexaInterfaceType::MODE_CONTROLLER                 | Supported*  |
| AlexaInterfaceType::MOTION_SENSOR                   | Supported*  |
| AlexaInterfaceType::PERCENTAGE_CONTROLLER           | Supported*  |
| AlexaInterfaceType::PLAYBACK_CONTROLLER             | Supported*  |
| AlexaInterfaceType::PLAYBACK_STATE_REPORTER         | Supported*  |
| AlexaInterfaceType::PROACTIVE_NOTIFICATION_SOURCE   | Supported*  |
| AlexaInterfaceType::RANGE_CONTROLLER                | Supported*  |
| AlexaInterfaceType::RECORD_CONTROLLER               | Supported*  |
| AlexaInterfaceType::REMOTE_VIDEO_PLAYER             | Supported*  |
| AlexaInterfaceType::RTC_SESSION_CONTROLLER          | Supported*  |
| AlexaInterfaceType::SCENE_CONTROLLER                | Supported*  |
| AlexaInterfaceType::SECURITY_PANEL_CONTROLLER       | Supported*  |
| AlexaInterfaceType::SEEK_CONTROLLER                 | Supported*  |
| AlexaInterfaceType::SIMPLE_EVENT_SOURCE             | Supported*  |
| AlexaInterfaceType::SMART_VISION_OBJECT_DETECTION_SENSOR | Supported* |
| AlexaInterfaceType::SMART_VISION_SNAPSHOT_PROVIDER  | Supported*  |
| AlexaInterfaceType::SPEAKER                         | Supported*  |
| AlexaInterfaceType::STEP_SPEAKER                    | Supported*  |
| AlexaInterfaceType::TEMPERATURE_SENSOR              | Supported*  |
| AlexaInterfaceType::THERMOSTAT_CONTROLLER           | Supported*  |
| AlexaInterfaceType::THERMOSTAT_CONTROLLER_CONFIGURATION | Supported* |
| AlexaInterfaceType::THERMOSTAT_CONTROLLER_HVAC_COMPONENTS | Supported* |
| AlexaInterfaceType::THERMOSTAT_CONTROLLER_SCHEDULE  | Supported*  |
| AlexaInterfaceType::TIME_HOLD_CONTROLLER            | Supported*  |
| AlexaInterfaceType::UI_CONTROLLER                   | Supported*  |
| AlexaInterfaceType::USER_PREFERENCE                 | Supported*  |
| AlexaInterfaceType::VIDEO_RECORDER                  | Supported*  |
| AlexaInterfaceType::WAKE_ON_LAN_CONTROLLER          | Supported*  |


(*Partial support or limited implementation advanced configuration is required)

---


## Advanced ussage
For devices with limited or partial support, Alex2ESP provides functions that allow you to attach custom JSON objects to the status report. For example, to report the status of a PowerController type, you can use the `AddPowerControllerProp` function. However, if a specific "add props" function does not exist for your use case, you can utilize the `AddContextProp` function to pass a custom JSON object.

For instance, to manually report the state of a PowerController, you can use the following code:

```cpp
    JsonDocument doc;

    doc["namespace"] = "Alexa.PowerController";
    doc["name"] = "powerState";
    doc["value"] = "ON";
    doc["timeOfSample"] = "{REPLACE_WITH_DATETIME}"; // Alex2MQTT server wil do the replace
    doc["uncertaintyInMilliseconds"] = 0;
    AddContextProp(doc.as<JsonObject>())
```

---

## Contributing
Feel free to submit pull requests or issues for feature requests and bug fixes.

---

## License
This project is licensed under the MIT License. See the LICENSE file for details.

