/*
 * @title Alex2ESP Library
 * @version 1.0.0
 * @author David
 * @license MIT
 * @contributors chaos511
 *
 * @description The Alex2ESP library is a companion to the Alex2MQTT Alexa Skill,
 * providing seamless integration between ESP-based devices and the Alex2MQTT server.
 * This library connects to alex2mqtt.stormysdream.club, where the skill is hosted,
 * allowing your devices to communicate effortlessly with the Alexa Voice Service
 * using MQTT as the backbone.
 */
#include "Alex2ESP.h"

Alex2ESP::Alex2ESP()
    : rootTopic(), mqttUsername(nullptr), mqttPassword(nullptr), _state(Alex2ESPState::UNINITIALIZED), _disconnectReason(AsyncMqttClientDisconnectReason::TCP_DISCONNECTED) {}

void Alex2ESP::begin(const char *rootTopic, const char *username, const char *password)
{

    _state = Alex2ESPState::INITIALIZED;
    _disconnectReason = AsyncMqttClientDisconnectReason::TCP_DISCONNECTED;
    this->rootTopic = rootTopic;
    this->mqttUsername = username;
    this->mqttPassword = password;

    discoverTopic = (String(this->rootTopic) + String("/discover"));
    discoverTopicSend = (String(this->rootTopic) + String("/discover_r"));

    TopicESP = (String(this->rootTopic) + String("/+/alexaDirective_e"));

    // Log the root topic and credentials
    AlexaUtils::log("Setting root topic: ");
    AlexaUtils::log(rootTopic);
    AlexaUtils::log(" with creds ");
    AlexaUtils::log(username);
    AlexaUtils::log(":");
    AlexaUtils::logln(password);
    AlexaUtils::printMemoryInfo();

    // Set up MQTT client callbacks
    mqttClient.onConnect([this](bool sessionPresent)
                         { this->onMqttConnect(sessionPresent); });
    mqttClient.onDisconnect([this](AsyncMqttClientDisconnectReason reason)
                            { this->onMqttDisconnect(reason); });
    mqttClient.onSubscribe([this](uint16_t packetId, uint8_t qos)
                           { this->onSubscribe(packetId, qos); });
    mqttClient.onMessage([this](char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total)
                         { this->onMessage(topic, payload, properties, len, index, total); });

    // Configure MQTT client
    mqttClient.setServer(mqttServer, mqttPort);
    mqttClient.setCredentials(username, password);

    // TODO: Throw error if dns fails or has no internet access?
    _state = Alex2ESPState::CONNECTING;
    mqttClient.connect();
}

void Alex2ESP::onMqttConnect(bool sessionPresent)
{
    _state = Alex2ESPState::SUBSCRIBING;

    AlexaUtils::log("Connected to MQTT server, Now subscribing to: ");
    AlexaUtils::log(discoverTopic.c_str());
    AlexaUtils::log(" ");
    AlexaUtils::logln(TopicESP.c_str());

    mqttClient.subscribe(discoverTopic.c_str(), 1);
    mqttClient.subscribe(TopicESP.c_str(), 1);
}

void Alex2ESP::onSubscribe(uint16_t packetId, uint8_t qos)
{
    _state = Alex2ESPState::CONNECTED;

    AlexaUtils::log("Subscribed with packetId: ");
    AlexaUtils::log(packetId);
    AlexaUtils::log(" and QoS: ");
    AlexaUtils::logln(qos);
}

// Internal: Handle disconnection
// TODO: auto reconnect?
void Alex2ESP::onMqttDisconnect(AsyncMqttClientDisconnectReason reason)
{
    _state = Alex2ESPState::DISCONNECTED;
    _disconnectReason = reason;
}

void Alex2ESP::onMessage(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t length, size_t index, size_t total)
{
    AlexaUtils::logln("OnMessage Start");
    AlexaUtils::printMemoryInfo();

    clearToSend = false;

    if (strcmp(topic, discoverTopic.c_str()) == 0)
    {

        // boolean successful = messagePackExtractor(topic, payload, length, index, total);

        // if (successful && inputDoc["name"] == "Discover")
        // {
        for (const AlexaDevice &device : devices)
        {
            AlexaUtils::logln("Getting device json");
            JsonDocument jsonData = device.getDeviceJSON();
            String jsonString;
            serializeJson(jsonData, jsonString);
            jsonData.clear();
            AlexaUtils::enqueue(jsonString.c_str(), discoverTopicSend.c_str());
        }
        // }
    }
    else
    {
        for (auto &device : devices)
        {
            String directiveTopic = String(rootTopic) + "/" + device.getEndpointId() + "/alexaDirective_e";

            if (strcmp(topic, directiveTopic.c_str()) == 0)
            {
                AlexaUtils::logln(topic);
                payload[length] = '\0';
                AlexaUtils::logln(payload);
                AlexaUtils::enqueueReceive(payload);
            }
        }
    }
    AlexaUtils::logln("OnMessage End");
    AlexaUtils::printMemoryInfo();
    clearToSend = true;
}

// boolean Alex2ESP::messagePackExtractor(char *topic, char *payload, size_t length, size_t index, size_t total)
// {
// payload[length] = '\0';              // Truncate the payload

// uint8_t messageId = payload[0];      // Message ID (byte 0)
// uint8_t fragmentId = payload[1];     // Fragment ID (byte 1)
// uint8_t totalFragments = payload[2]; // Total Fragments (byte 2)

// if (totalFragments > MAX_FRAGMENT_COUNT)
// {
//     return false;                   //Message too long, skip.
// }

// if (fragmentId == 0)
// {
//     clearCache();
//     cache.totalParts = totalFragments;
//     cache.messageId = String(messageId);
// }

// if (cache.messageId != String(messageId))
// {
//     clearCache();
//     cache.messageId = String(messageId);
//     cache.totalParts = totalFragments;
// }

// if (fragmentId < cache.totalParts)
// {
//     strncpy(cache.message + cache.fragmentOffset, payload + 3, length - 3); // Copy the fragment data
//     cache.fragmentOffset=cache.fragmentOffset+(length-3);                   //
//     cache.receivedParts++;
//     Serial.printf("Received fragment %d of %d, length %d receivedParts: %d \n", fragmentId + 1, totalFragments, length, cache.receivedParts);

//     if (isMessageComplete())
//     {
//         AlexaUtils::logln("Full message received.");
//         AlexaUtils::logln(cache.message);

//         DeserializationError error = deserializeJson(inputDoc, cache.message);
//         if (error)
//         {
//             AlexaUtils::log("Failed to parse message: ");
//             AlexaUtils::logln(String(error.f_str()));
//             clearCache();
//             return false;
//         }
//         else
//         {
//             AlexaUtils::logln("JSON message parsed successfully!");
//             clearCache(true);
//             return true;
//         }
//     }
// }
//     return false;
// }

AlexaDevice *Alex2ESP::getDevice(const String &name, const String &endpointId)
{
    // Check if a device with the given endpointId already exists
    for (auto &device : devices)
    {
        if (device.getEndpointId() == endpointId)
        {
            return &device; // Return the existing device
        }
    }

    // If the device doesn't exist, create a new one
    devices.emplace_back(name, rootTopic, endpointId);

    Serial.print("Created new device: ");
    Serial.print(name);
    Serial.print(" with endpointId: ");
    Serial.println(endpointId);

    // Return a pointer to the newly created device
    return &devices.back();
}

// void Alex2ESP::clearCache(boolean skipDocClear)
// {
//     if (!skipDocClear)
//     {
//         inputDoc.clear();
//     }
//     cache.receivedParts = 0; // Reset the count of received parts
//     cache.messageId = "";    // Clear the message ID
//     cache.totalParts = 0;    // Reset the total parts count
//     cache.fragmentOffset = 0;
//     memset(cache.message, 0, sizeof(cache.message)); // Clear the message buffer
// }

// bool Alex2ESP::isMessageComplete()
// {
//     return cache.receivedParts == cache.totalParts; // Check if we have received all parts
// }

Alex2ESPState Alex2ESP::getState() const
{
    return _state;
}

AsyncMqttClientDisconnectReason Alex2ESP::getDisconnectReason() const
{
    return _disconnectReason;
}

void Alex2ESP::handleMqttReconnection()
{
    if (!mqttClient.connected() && _disconnectReason == AsyncMqttClientDisconnectReason::TCP_DISCONNECTED)
    {
        if (millis() - lastReconnectTime > 5000)
        {
            lastReconnectTime = millis();
            reconnectAttempt++;
            mqttClient.connect();
        }
    }
}
void Alex2ESP::processHttpPost()
{
    if (!AlexaUtils::isQueueEmpty())
    {
        AlexaUtils::logln("processHttpPost");

        const char *payload = AlexaUtils::dequeueVals(false);

        httpPOST.begin(wifiPOST, "http://alex2mqtt.stormysdream.club/Alex2ESP");
        httpPOST.setAuthorization(mqttUsername, mqttPassword);
        httpPOST.addHeader("Content-Type", "text/plain");

        AlexaUtils::log("Sending Data: ");
        AlexaUtils::logln(payload);

        int httpResponseCode = httpPOST.POST(payload);

        if (httpResponseCode != 200)
        {

            if (retryCountPOST >= MAX_RETRY_COUNT)
            {
                AlexaUtils::dequeueVals(true);
            }

            AlexaUtils::log("POST Error code: ");
            AlexaUtils::logln(httpResponseCode);
            retryCountPOST++;
            if (httpResponseCode > 0)
            {
                String response = httpPOST.getString();
                Serial.println("Response:");
                Serial.println(response);
            }
        }
        else
        {
            retryCountPOST = 0;
            AlexaUtils::dequeueVals(true);
        }
        httpPOST.end();
    }
}
void Alex2ESP::processHttpGet()
{
    if (!AlexaUtils::isReceiveQueueEmpty())
    {
        AlexaUtils::logln("processHttpGet");

        String uuid;
        AlexaUtils::dequeueReceive(uuid, false);
        AlexaUtils::log("Sending get request for uuid: ");
        // AlexaUtils::logln(uuid);

        httpGET.begin(wifiGET, "http://alex2mqtt.stormysdream.club/Alex2ESP/" + uuid);
        httpGET.setAuthorization(mqttUsername, mqttPassword);
        int httpResponseCode = httpGET.GET();

        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        if (httpResponseCode != 200)
        {
            Serial.print("Error code: ");
            Serial.println(httpResponseCode);
            if (retryCountGET >= MAX_RETRY_COUNT)
            {
                AlexaUtils::dequeueReceive(uuid, true);
            }

            retryCountGET++;
        }
        else
        {
            retryCountGET = 0;
            AlexaUtils::dequeueReceive(uuid, true);
            String payloadStr = httpGET.getString();
            size_t length = payloadStr.length();

            if (length < AlexaUtils::MAX_PAYLOAD_LENGTH - 1)
            {
                payloadStr.toCharArray(AlexaUtils::receivePayload, length + 1);
                payloadStr = "";
                AlexaUtils::receivePayload[length + 1] = '\0';
                // AlexaUtils::logln(AlexaUtils::receivePayload);

                DeserializationError error = deserializeJson(inputDoc, AlexaUtils::receivePayload);
                if (error)
                {
                    AlexaUtils::log("Failed to parse message: ");
                    AlexaUtils::logln(String(error.f_str()));
                    inputDoc.clear();
                }
                else
                {
                    AlexaUtils::logln("JSON message parsed successfully!");

                    for (auto &device : devices)
                    {
                        if (strcmp(device.getEndpointId().c_str(), inputDoc["directive"]["endpoint"]["endpointId"]) == 0)
                        {
                            serializeJson(inputDoc, Serial);
                            Serial.println();
                            device.triggerEvent("DirectiveReceived", inputDoc["directive"], AlexaInterfaceType::UNKNOWN);

                            if (inputDoc["directive"]["header"]["name"] == "ReportState")
                            {
                                device.triggerEvent("ReportState", inputDoc["directive"], AlexaInterfaceType::UNKNOWN);
                            }
                            else
                            {
                                device.triggerEvent("Event", inputDoc["directive"], AlexaInterfaceUtils::fromString(inputDoc["directive"]["header"]["namespace"]));
                            }
                        }
                    }
                }
            }
        }
        httpGET.end();
    }
}

void Alex2ESP::loop()
{

    handleMqttReconnection();
    if(clearToSend){
        processHttpPost();
        processHttpGet();
    }

    return;
}