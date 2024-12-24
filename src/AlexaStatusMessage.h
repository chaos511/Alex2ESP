#include <ArduinoJson.h>
#include <Alex2ESP.h>
#include <AlexaUtils.h>

#ifndef ALEXA_STATUS_MESSAGE_H
#define ALEXA_STATUS_MESSAGE_H

#define MAX_STATUS_REPORT_SIZE 2048

enum class EndpointHealth
{
    OK,
    UNREACHABLE
};

enum class PowerController
{
    ON,
    OFF
};
enum class TemperatureSensorScale
{
    CELSIUS,
    FAHRENHEIT
};

class AlexaStatusMessage
{
public:
    AlexaStatusMessage(const String &correlationToken, const String &rootTopic, const String &endpointId, const bool isResponse)
    {
        this->endpointId = endpointId;
        this->rootTopic = rootTopic;

        JsonObject event = doc["event"].to<JsonObject>();

        JsonObject event_header = event["header"].to<JsonObject>();
        event_header["namespace"] = "Alexa";
        if (isResponse)
        {
            event_header["name"] = "Response";
        }
        else
        {
            event_header["name"] = "StateReport";
        }
        event_header["payloadVersion"] = "3";
        event_header["messageId"] = generateMessageId();
        event_header["correlationToken"] = correlationToken;

        JsonObject event_endpoint = event["endpoint"].to<JsonObject>();
        event_endpoint["endpointId"] = endpointId;
        contextProperties = doc["context"]["properties"].to<JsonArray>();
    }

    void setEndpointId(const String &endpointId)
    {
        // event["endpoint"]["endpointId"] = endpointId;
    }

    AlexaStatusMessage &AddHealthProp(EndpointHealth endpointHealth, unsigned int uncertaintyInMs = 0)
    {
        JsonDocument healthValue;
        healthValue["value"] = (endpointHealth == EndpointHealth::OK) ? "OK" : "UNREACHABLE";
        return AddProperty(AlexaInterfaceType::ENDPOINT_HEALTH, "connectivity", healthValue.as<JsonObject>(), uncertaintyInMs);
    }

    AlexaStatusMessage &AddPowerControllerProp(PowerController powerController, unsigned int uncertaintyInMs = 0)
    {
        String value = (powerController == PowerController::ON) ? "ON" : "OFF";
        return AddProperty(AlexaInterfaceType::POWER_CONTROLLER, "powerState", value, uncertaintyInMs);
    }

    AlexaStatusMessage &AddTemperatureSensorProp(TemperatureSensorScale tempSensor,float value, unsigned int uncertaintyInMs = 0)
    {
        JsonDocument tempValue;
        tempValue["scale"] = "CELSIUS";
        tempValue["value"] = value;
        if((tempSensor == TemperatureSensorScale::FAHRENHEIT)){
            tempValue["value"] = (value - 32) * 5.0 / 9.0;
        }
        return AddProperty(AlexaInterfaceType::TEMPERATURE_SENSOR, "temperature", tempValue.as<JsonObject>(), uncertaintyInMs);
    }

    AlexaStatusMessage &AddBrightnessControllerProp(unsigned int brightness, unsigned int uncertaintyInMs = 0)
    {
        return AddProperty(AlexaInterfaceType::BRIGHTNESS_CONTROLLER, "brightness", brightness, uncertaintyInMs);
    }
    AlexaStatusMessage &AddColorTemperatureControllerProp(unsigned int colorTemperature, unsigned int uncertaintyInMs = 0)
    {
        return AddProperty(AlexaInterfaceType::COLOR_TEMPERATURE_CONTROLLER, "colorTemperatureInKelvin", colorTemperature, uncertaintyInMs);
    }
    AlexaStatusMessage &AddToggleControllerProp(PowerController powerController,String instanceName, unsigned int uncertaintyInMs = 0)
    {
        String value = (powerController == PowerController::ON) ? "ON" : "OFF";
        return AddProperty(AlexaInterfaceType::TOGGLE_CONTROLLER, "toggleState", value, uncertaintyInMs,instanceName);
    }

    AlexaStatusMessage &AddContextProp(const JsonObject &property)
    {
        contextProperties.add(property);
        return *this; // Return a reference to the current object
    }

    void send()
    {
        doc.shrinkToFit();
        serializeJson(doc, outputString);
        doc.clear();
        String topic = rootTopic + "/" + endpointId + "/alexaResponce";
        AlexaUtils::enqueue(outputString, topic.c_str());
        
    }

private:
    String rootTopic;
    String endpointId;
    JsonDocument doc;
    JsonArray contextProperties;
    static char outputString[MAX_STATUS_REPORT_SIZE];

    // TODO: make real uuid4 gen function
    String generateMessageId()
    {
        char buffer[38];
        const char charset[] = "0123456789abcdefABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"; // Allowed characters

        // Seed the random number generator (optional)
        srand(static_cast<unsigned int>(time(nullptr)));

        // Generate 37 random characters
        for (int i = 0; i < 37; ++i)
        {
            buffer[i] = charset[rand() % (sizeof(charset) - 1)]; // Pick a random character
        }

        buffer[37] = '\0'; // Null-terminate the string
        return String(buffer);
    }

    template <typename T>
    AlexaStatusMessage &AddProperty(AlexaInterfaceType type, const String &propertyName, const T &value, unsigned int uncertaintyInMs = 0,const String &instanceName="")
    {
        JsonDocument prop;
        prop["namespace"] = AlexaInterfaceUtils::toString(type);
        prop["name"] = propertyName;

        if (!instanceName.isEmpty()) {
            prop["instance"] = instanceName;
        }
        if constexpr (std::is_same_v<T, JsonObject>)
        {
            prop["value"] = value;
        }
        else
        {
            prop["value"] = value;
        }

        prop["timeOfSample"] = "{REPLACE_WITH_DATETIME}";
        prop["uncertaintyInMilliseconds"] = uncertaintyInMs;

        contextProperties.add(prop.as<JsonObject>());
        return *this;
    }
};
#endif
