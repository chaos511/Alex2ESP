#include "AlexaDevice.h"

AlexaDevice::AlexaDevice(const String& name, const String& rootTopic, const String& endpointId)
    : name(name), endpointId(endpointId), rootTopic(rootTopic) {
    // Initialize event arrays to nullptr
    for (int i = 0; i < MAX_EVENTS; ++i) {
        eventNames[i] = nullptr;       // Set all event names to nullptr
        eventCallbacks[i] = nullptr;   // Set all callbacks to nullptr
    }
}

// Setters and Getters
void AlexaDevice::setName(const String& name) {
    this->name = name;
}

String AlexaDevice::getName() const {
    return name;
}

String AlexaDevice::getEndpointId() const {
    return endpointId;
}

DisplayCategory AlexaDevice::getDisplayCategory() const {
    return displayCategory;
}

void AlexaDevice::setDisplayCategory(DisplayCategory category) {
    displayCategory = category;
}

String AlexaDevice::getDescription() const {
    return description;
}

void AlexaDevice::setDescription(const String& description) {
    this->description = description;
}

String AlexaDevice::getManufacturerName() const {
    return manufacturerName;
}

void AlexaDevice::setManufacturerName(const String& manufacturerName) {
    this->manufacturerName = manufacturerName;
}

String AlexaDevice::getManufacturer() const {
    return manufacturer;
}

void AlexaDevice::setManufacturer(const String& manufacturer) {
    this->manufacturer = manufacturer;
}

String AlexaDevice::getModel() const {
    return model;
}

void AlexaDevice::setModel(const String& model) {
    this->model = model;
}

String AlexaDevice::getSoftwareVersion() const {
    return softwareVersion;
}


AlexaInterface* AlexaDevice::addCapability(AlexaInterfaceType type) {
    // Check if a interface with the given type already exists
    for (auto& iface : capabilities) {
        if (iface.getType() == type) {
            return &iface; // Return the existing interface
        }
    }

    // If the interface doesn't exist, create a new one
    capabilities.emplace_back(type);

    Serial.print("Created new interface with type: ");
    Serial.println(capabilities.back().getTypeString());

    // Return a pointer to the newly created device
    return &capabilities.back();
}



JsonDocument AlexaDevice::getDeviceJSON() const {

    JsonDocument json;

    // Main device attributes
    json["endpointId"] = endpointId;
    json["friendlyName"] = name;
    json["description"] = description;
    json["manufacturerName"] = manufacturerName;
    


    JsonArray displayCategories = json["displayCategories"].to<JsonArray>();
    displayCategories.add(DisplayCategoryUtils::toString(displayCategory));

    JsonObject additionalAttributes = json["additionalAttributes"].to<JsonObject>();
    additionalAttributes["manufacturer"] = manufacturer;
    additionalAttributes["model"] = model;
    additionalAttributes["serialNumber"] = "ESP2Alex";
    additionalAttributes["firmwareVersion"] = "1.0.0";
    additionalAttributes["softwareVersion"] = softwareVersion;
    additionalAttributes["customIdentifier"] = "ESP2Alex";

    JsonArray capabilitiesArray = json["capabilities"].to<JsonArray>();
    
    for (AlexaInterface capability : capabilities) {
        capabilitiesArray.add(capability.getJSON().as<JsonObject>());
    }

    // capabilitiesArray.add(capability.getJSON().as<JsonObject>());

    return json;
}

// void AlexaDevice::registerEvent(const String& eventName, std::function<void(const JsonDocument&,const AlexaInterfaceType&)> callback) {
//     eventCallbacks[eventName] = callback;
// }

// void AlexaDevice::triggerEvent(const String& eventName, const JsonDocument& directive,const AlexaInterfaceType& type) const {
//     auto it = eventCallbacks.find(eventName);
//     if (it != eventCallbacks.end()) {
//         // Call the registered callback function
//         it->second(directive,type);
//     } else {
//         Serial.print("No event registered for: ");
//         Serial.println(eventName);
//     }
// }


// Register an event callback function
void AlexaDevice::registerEvent(const char* eventName, void (*callback)(const JsonDocument&, const AlexaInterfaceType&)) {
    for (int i = 0; i < MAX_EVENTS; ++i) {
        // Find an empty slot for the new event
        if (eventNames[i] == nullptr) {
            eventNames[i] = eventName;  // Store the event name
            eventCallbacks[i] = callback;  // Store the callback function
            break;
        }
    }
}

// Trigger the event and invoke the corresponding callback
void AlexaDevice::triggerEvent(const char* eventName, const JsonDocument& directive, const AlexaInterfaceType& type) const {
    for (int i = 0; i < MAX_EVENTS; ++i) {
        if (eventNames[i] != nullptr && strcmp(eventNames[i], eventName) == 0) {
            // Found the event name, call the corresponding callback function
            eventCallbacks[i](directive, type);
            return;
        }
    }
    // If no event was found, print an error message
    Serial.print("No event registered for: ");
    Serial.println(eventName);
}