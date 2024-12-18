#ifndef ALEXA_UTILS_H
#define ALEXA_UTILS_H

#include <vector>
#include <string>
#include <Arduino.h>
#include <AsyncMqttClient.h>
#include <cstring> // Include for strcpy and memset

class AlexaUtils
{
public:
    static const int MAX_PAYLOAD_LENGTH                 = 2048;     // Maximum length for receive packets
    static char receivePayload[MAX_PAYLOAD_LENGTH];

    static bool enqueueReceive(const char* packet); 
    static bool dequeueReceive(String& packet,bool remove);    
    static bool isReceiveQueueEmpty();            
    static bool isReceiveQueueFull();           

    static bool enqueue(const char* topic, const char* packet);
    static bool dequeue(String& topic, String& packet);
    static bool isQueueEmpty();
    static bool isQueueFull();
    static const char* dequeueVals(bool remove);

    static void log(const char *string);
    static void logln(const char *string);

    static void log(int num);
    static void logln(int num);

    static void log(uint16_t  num);
    static void logln(uint16_t  num);

    static void log(uint8_t  num);
    static void logln(uint8_t  num);

    static void logln(String string);

    // Incrementing message ID
    static uint8_t nextMessageId;

    // Static function to set the MQTT client reference
    static void printMemoryInfo()
    {
        size_t freeHeap = ESP.getFreeHeap();
        size_t freeStack = ESP.getFreeContStack(); // Requires ESP8266 core 3.0.0+
        size_t sketchSize = ESP.getSketchSize();
        size_t freeSketchSpace = ESP.getFreeSketchSpace();

        // Print in custom format
        Serial.printf("freeHeap: %u, freeStack: %u, freeROM: %u, usedROM: %u\n",
            freeHeap,
            freeStack,
            freeSketchSpace,
            sketchSize);
    }


private:
    static const int MAX_QUEUE_LENGTH                   = 5;        // Define maximum queue length
    static const int MAX_TOPIC_LENGTH                   = 128;      // Maximum length for topics
    static const int MAX_PACKET_LENGTH                  = 2048;     // Maximum length for sending packets
    static constexpr char MESSAGE_PAYLOAD_SPLIT[32]     = "{MESSAGE_PAYLOAD_SPLIT}";
    
    
    // Static arrays for topics and packets
    static char topicQueue[MAX_QUEUE_LENGTH][MAX_TOPIC_LENGTH];
    static char packetQueue[MAX_QUEUE_LENGTH][MAX_PACKET_LENGTH];
    static char combinedData[MAX_TOPIC_LENGTH + MAX_PACKET_LENGTH + 32];

    static char receiveQueue[MAX_QUEUE_LENGTH][16];
    static int queueStart; // Index of the front of the queue
    static int queueEnd;   // Index of the back of the queue
    static int queueCount; // Number of items in the queue

    static int queueStartReceive;
    static int queueEndReceive;
    static int queueCountReceive;
};

#endif // ALEXA_UTILS_H
