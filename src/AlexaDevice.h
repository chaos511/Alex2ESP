#ifndef ALEXADEVICE_H
#define ALEXADEVICE_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include "AlexaInterface.h"
#include <functional> 
#include <map>
#include <unordered_map>
#include <string>
#include <AlexaStatusMessage.h>
#include <Alex2ESP.h>


#define MAX_EVENTS 10

enum class DisplayCategory {
    ACTIVITY_TRIGGER,
    AIR_CONDITIONER,
    AIR_FRESHENER,
    AIR_PURIFIER,
    AIR_QUALITY_MONITOR,
    ALEXA_VOICE_ENABLED,
    AUTO_ACCESSORY,
    BLUETOOTH_SPEAKER,
    CAMERA,
    CHRISTMAS_TREE,
    COFFEE_MAKER,
    COMPUTER,
    CONTACT_SENSOR,
    DISHWASHER,
    DOOR,
    DOORBELL,
    DRYER,
    EXTERIOR_BLIND,
    FAN,
    GAME_CONSOLE,
    GARAGE_DOOR,
    HEADPHONES,
    HUB,
    INTERIOR_BLIND,
    LAPTOP,
    LIGHT,
    MICROWAVE,
    MOBILE_PHONE,
    MOTION_SENSOR,
    MUSIC_SYSTEM,
    NETWORK_HARDWARE,
    OTHER,
    OVEN,
    PHONE,
    PRINTER,
    REMOTE,
    ROUTER,
    SCENE_TRIGGER,
    SCREEN,
    SECURITY_PANEL,
    SECURITY_SYSTEM,
    SLOW_COOKER,
    SMARTLOCK,
    SMARTPLUG,
    SPEAKER,
    STREAMING_DEVICE,
    SWITCH,
    TABLET,
    TEMPERATURE_SENSOR,
    THERMOSTAT,
    TV,
    VACUUM_CLEANER,
    VEHICLE,
    WASHER,
    WATER_HEATER,
    WEARABLE
};

class DisplayCategoryUtils {
public:
    static String toString(DisplayCategory category) {
        static const std::unordered_map<DisplayCategory, String> categoryMap = {
            {DisplayCategory::ACTIVITY_TRIGGER, "ACTIVITY_TRIGGER"},
            {DisplayCategory::AIR_CONDITIONER, "AIR_CONDITIONER"},
            {DisplayCategory::AIR_FRESHENER, "AIR_FRESHENER"},
            {DisplayCategory::AIR_PURIFIER, "AIR_PURIFIER"},
            {DisplayCategory::AIR_QUALITY_MONITOR, "AIR_QUALITY_MONITOR"},
            {DisplayCategory::ALEXA_VOICE_ENABLED, "ALEXA_VOICE_ENABLED"},
            {DisplayCategory::AUTO_ACCESSORY, "AUTO_ACCESSORY"},
            {DisplayCategory::BLUETOOTH_SPEAKER, "BLUETOOTH_SPEAKER"},
            {DisplayCategory::CAMERA, "CAMERA"},
            {DisplayCategory::CHRISTMAS_TREE, "CHRISTMAS_TREE"},
            {DisplayCategory::COFFEE_MAKER, "COFFEE_MAKER"},
            {DisplayCategory::COMPUTER, "COMPUTER"},
            {DisplayCategory::CONTACT_SENSOR, "CONTACT_SENSOR"},
            {DisplayCategory::DISHWASHER, "DISHWASHER"},
            {DisplayCategory::DOOR, "DOOR"},
            {DisplayCategory::DOORBELL, "DOORBELL"},
            {DisplayCategory::DRYER, "DRYER"},
            {DisplayCategory::EXTERIOR_BLIND, "EXTERIOR_BLIND"},
            {DisplayCategory::FAN, "FAN"},
            {DisplayCategory::GAME_CONSOLE, "GAME_CONSOLE"},
            {DisplayCategory::GARAGE_DOOR, "GARAGE_DOOR"},
            {DisplayCategory::HEADPHONES, "HEADPHONES"},
            {DisplayCategory::HUB, "HUB"},
            {DisplayCategory::INTERIOR_BLIND, "INTERIOR_BLIND"},
            {DisplayCategory::LAPTOP, "LAPTOP"},
            {DisplayCategory::LIGHT, "LIGHT"},
            {DisplayCategory::MICROWAVE, "MICROWAVE"},
            {DisplayCategory::MOBILE_PHONE, "MOBILE_PHONE"},
            {DisplayCategory::MOTION_SENSOR, "MOTION_SENSOR"},
            {DisplayCategory::MUSIC_SYSTEM, "MUSIC_SYSTEM"},
            {DisplayCategory::NETWORK_HARDWARE, "NETWORK_HARDWARE"},
            {DisplayCategory::OTHER, "OTHER"},
            {DisplayCategory::OVEN, "OVEN"},
            {DisplayCategory::PHONE, "PHONE"},
            {DisplayCategory::PRINTER, "PRINTER"},
            {DisplayCategory::REMOTE, "REMOTE"},
            {DisplayCategory::ROUTER, "ROUTER"},
            {DisplayCategory::SCENE_TRIGGER, "SCENE_TRIGGER"},
            {DisplayCategory::SCREEN, "SCREEN"},
            {DisplayCategory::SECURITY_PANEL, "SECURITY_PANEL"},
            {DisplayCategory::SECURITY_SYSTEM, "SECURITY_SYSTEM"},
            {DisplayCategory::SLOW_COOKER, "SLOW_COOKER"},
            {DisplayCategory::SMARTLOCK, "SMARTLOCK"},
            {DisplayCategory::SMARTPLUG, "SMARTPLUG"},
            {DisplayCategory::SPEAKER, "SPEAKER"},
            {DisplayCategory::STREAMING_DEVICE, "STREAMING_DEVICE"},
            {DisplayCategory::SWITCH, "SWITCH"},
            {DisplayCategory::TABLET, "TABLET"},
            {DisplayCategory::TEMPERATURE_SENSOR, "TEMPERATURE_SENSOR"},
            {DisplayCategory::THERMOSTAT, "THERMOSTAT"},
            {DisplayCategory::TV, "TV"},
            {DisplayCategory::VACUUM_CLEANER, "VACUUM_CLEANER"},
            {DisplayCategory::VEHICLE, "VEHICLE"},
            {DisplayCategory::WASHER, "WASHER"},
            {DisplayCategory::WATER_HEATER, "WATER_HEATER"},
            {DisplayCategory::WEARABLE, "WEARABLE"}
        };

        auto it = categoryMap.find(category);
        if (it != categoryMap.end()) {
            return it->second;
        }
        return "UNKNOWN";
    }
};



class AlexaDevice {
public:
    AlexaDevice(const String& name, const String& rootTopic, const String& endpointId);

    void setName(const String& name);
    String getName() const;

    String getEndpointId() const;

    DisplayCategory getDisplayCategory() const;
    void setDisplayCategory(DisplayCategory category);

    String getDescription() const;
    void setDescription(const String& description);

    String getManufacturerName() const;
    void setManufacturerName(const String& manufacturerName);

    String getManufacturer() const;
    void setManufacturer(const String& manufacturer);

    String getModel() const;
    void setModel(const String& model);

    String getSoftwareVersion() const;

    JsonDocument getDeviceJSON() const;

    AlexaInterface* addCapability(AlexaInterfaceType type);

    void registerEvent(const char* eventName, void (*callback)(const JsonDocument&, const AlexaInterfaceType&));

    void triggerEvent(const char* eventName, const JsonDocument& directive, const AlexaInterfaceType& type) const;

    AlexaStatusMessage buildStatusMessage(const String& correlationToken,const bool isResponse=false) {
        return AlexaStatusMessage(correlationToken,rootTopic,endpointId,isResponse);
    }

private:
    String name;       
    String endpointId; 
    String rootTopic;
    const char* eventNames[MAX_EVENTS];
    void (*eventCallbacks[MAX_EVENTS])(const JsonDocument&, const AlexaInterfaceType&);

    DisplayCategory displayCategory = DisplayCategory::OTHER; 
    String description = "Alexa2MQTT Default Device";
    String manufacturerName = "Alexa2MQTT";          
    String manufacturer = "Alexa2MQTT";             
    String model = "Alexa2MQTT";                     
    const String softwareVersion = "1.0.0";    

    std::vector<AlexaInterface> capabilities;
      
};

#endif
