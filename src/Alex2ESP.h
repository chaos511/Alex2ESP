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

#ifndef ALEX2ESP_H
#define ALEX2ESP_H
class AlexaDevice;

#include <Arduino.h>
#include <AsyncMqttClient.h>
#include <ArduinoJson.h>
#include "AlexaDevice.h"
#include <AlexaInterface.h>
#include <vector> 
#include <AlexaUtils.h>

#include <ESP8266HTTPClient.h>


enum class Alex2ESPState
{
    UNINITIALIZED,
    INITIALIZED,
    CONNECTING,
    SUBSCRIBING,
    CONNECTED,
    DISCONNECTED
};

class Alex2ESP
{
public:
    // Constructor
    Alex2ESP();

    // Begin function for initialization
    void begin(const char *rootTopic, const char *username, const char *password);
    Alex2ESPState getState() const;
    void loop();

    AsyncMqttClientDisconnectReason getDisconnectReason() const;

    AlexaDevice *getDevice(const String &name, const String &endpointId);
    void messageSplitAndSend(String messagepackString, String topic);

private:
    static const int MAX_RETRY_COUNT = 2;        // Define maximum retry count
    int retryCountPOST=0;
    int retryCountGET=0;

    boolean clearToSend=false;
    AsyncMqttClient mqttClient; // MQTT client instance
    String rootTopic;      // Root topic for communication
    String discoverTopic;       // The topic we listen on for discovery messages
    String discoverTopicSend;   // The topic we send discovery messages

    String TopicESP;            // The topic we listen on for esp messages

    const char *mqttUsername;   // Username for authentication
    const char *mqttPassword;   // Password for authentication

    unsigned long lastReconnectTime;
    int reconnectAttempt;

    HTTPClient httpGET;
    HTTPClient httpPOST;

    WiFiClient wifiGET;
    WiFiClient wifiPOST;
    JsonDocument inputDoc;
    
    std::vector<AlexaDevice> devices; // Collection of devices

    Alex2ESPState _state;
    AsyncMqttClientDisconnectReason _disconnectReason;

    // MQTT connection details
    const char *mqttServer = "alex2mqtt.stormysdream.club";
    uint16_t mqttPort = 1883;

    // Internal event handlers
    void onMqttConnect(bool sessionPresent);
    void onMqttDisconnect(AsyncMqttClientDisconnectReason reason);
    void onSubscribe(uint16_t packetId, uint8_t qos);
    void onMessage(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t length, size_t index, size_t total);

    //loop processing function
    void handleMqttReconnection();
    void processHttpPost();
    void processHttpGet();

};

#endif // ALEX2ESP_H
