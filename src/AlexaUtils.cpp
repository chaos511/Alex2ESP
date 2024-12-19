#include "AlexaUtils.h"

// #define Alex2ESP_DEBUG

uint8_t AlexaUtils::nextMessageId = 0;

char AlexaUtils::receiveQueue[MAX_QUEUE_LENGTH][16]={};
char AlexaUtils::receivePayload[MAX_PAYLOAD_LENGTH];
char AlexaUtils::topicQueue[MAX_QUEUE_LENGTH][MAX_TOPIC_LENGTH] = {};
char AlexaUtils::packetQueue[MAX_QUEUE_LENGTH][MAX_PACKET_LENGTH] = {};
char AlexaUtils::combinedData[MAX_TOPIC_LENGTH + MAX_PACKET_LENGTH + 32];

int AlexaUtils::queueStart = 0;
int AlexaUtils::queueEnd = 0;
int AlexaUtils::queueCount = 0;


int AlexaUtils::queueStartReceive = 0;
int AlexaUtils::queueEndReceive = 0;
int AlexaUtils::queueCountReceive = 0;

// Enqueue a packet into the receive queue
bool AlexaUtils::enqueueReceive(const char* packet) {
    if (isReceiveQueueFull()) {
        return false; // Queue is full
    }
    AlexaUtils::log("Enqueing: ");
    AlexaUtils::logln(packet);

    // Copy the packet into the receive queue
    strncpy(receiveQueue[queueEndReceive], packet, sizeof(receiveQueue[0]) - 1);
    receiveQueue[queueEndReceive][sizeof(receiveQueue[0]) - 1] = '\0'; // Ensure null-termination

    // Update the queueEnd and queueCount
    queueEndReceive = (queueEndReceive + 1) % MAX_QUEUE_LENGTH;
    queueCountReceive++;

    return true;
}

// Dequeue a packet from the receive queue
bool AlexaUtils::dequeueReceive(String& packet,bool remove) {
    if (isReceiveQueueEmpty()) {
        return false; // Queue is empty
    }

    // Read the front of the receive queue
    packet = String(receiveQueue[queueStartReceive]);

    if(remove){
        // Clear the dequeued slot (optional but good for debugging)
        memset(receiveQueue[queueStartReceive], 0, sizeof(receiveQueue[0]));

        // Update the queueStart and queueCount
        queueStartReceive = (queueStartReceive + 1) % MAX_QUEUE_LENGTH;
        queueCountReceive--;
    }
    return true;
}

// Check if the receive queue is empty
bool AlexaUtils::isReceiveQueueEmpty() {
    return queueCountReceive == 0;
}

// Check if the receive queue is full
bool AlexaUtils::isReceiveQueueFull() {
    return queueCountReceive == MAX_QUEUE_LENGTH;
}


// Enqueue a topic and packet into the queue
bool AlexaUtils::enqueue(const char* packet,const char* topic) {
    if (isQueueFull()) {
        return false; // Queue is full
    }

    // Copy the topic and packet into the respective arrays
    strncpy(topicQueue[queueEnd], topic, MAX_TOPIC_LENGTH - 1);
    topicQueue[queueEnd][MAX_TOPIC_LENGTH - 1] = '\0'; // Ensure null-termination

    strncpy(packetQueue[queueEnd], packet, MAX_PACKET_LENGTH - 1);
    packetQueue[queueEnd][MAX_PACKET_LENGTH - 1] = '\0'; // Ensure null-termination

    // Update the queueEnd and queueCount
    queueEnd = (queueEnd + 1) % MAX_QUEUE_LENGTH;
    queueCount++;

    return true;
}

// Dequeue a topic and packet from the queue
bool AlexaUtils::dequeue(String& topic, String& packet) {
    if (isQueueEmpty()) {
        return false; // Queue is empty
    }

    // Read the front of the queue
    topic = String(topicQueue[queueStart]);
    packet = String(packetQueue[queueStart]);

    // Clear the dequeued slot (optional but good for debugging)
    memset(topicQueue[queueStart], 0, MAX_TOPIC_LENGTH);
    memset(packetQueue[queueStart], 0, MAX_PACKET_LENGTH);

    // Update the queueStart and queueCount
    queueStart = (queueStart + 1) % MAX_QUEUE_LENGTH;
    queueCount--;

    return true;
}


const char* AlexaUtils::dequeueVals(bool remove) {
    if (isQueueEmpty()) {
        return nullptr; // Queue is empty
    }

    // Reset combinedData before use to ensure no leftover data from previous calls
    memset(combinedData, 0, sizeof(combinedData));

    // Get lengths of the topic and packet
    int topicLen = strlen(topicQueue[queueStart]);
    int packetLen = strlen(packetQueue[queueStart]);

    // Calculate available space in the combinedData buffer
    size_t availableSpace = sizeof(combinedData) - 1; // Reserve space for the null terminator

    // Check if the combined data can fit in the buffer
    if ((topicLen + packetLen + strlen(MESSAGE_PAYLOAD_SPLIT)) > availableSpace) {
        // Return null if the combined data is too large for the buffer
        AlexaUtils::logln("Error: Combined data exceeds buffer size.");
        return nullptr;
    }

    // Concatenate the topic, separator, and packet into combinedData
    snprintf(combinedData, sizeof(combinedData), "%s%s%s", topicQueue[queueStart], MESSAGE_PAYLOAD_SPLIT, packetQueue[queueStart]);

    if (remove) {
        // Clear the dequeued slot
        memset(topicQueue[queueStart], 0, MAX_TOPIC_LENGTH);
        memset(packetQueue[queueStart], 0, MAX_PACKET_LENGTH);

        // Update the queueStart and queueCount
        queueStart = (queueStart + 1) % MAX_QUEUE_LENGTH;
        queueCount--;
    }

    // Return the pointer to the combined data
    return combinedData;
}



// Check if the queue is empty
bool AlexaUtils::isQueueEmpty() {
    return queueCount == 0;
}

// Check if the queue is full
bool AlexaUtils::isQueueFull() {
    return queueCount == MAX_QUEUE_LENGTH;
}



void AlexaUtils::log(const char *string) {
#ifdef Alex2ESP_DEBUG
    Serial.print(string);
#endif
}

void AlexaUtils::logln(const char *string) {
#ifdef Alex2ESP_DEBUG
    Serial.println(string);
#endif
}

void AlexaUtils::log(int num) {
#ifdef Alex2ESP_DEBUG
    Serial.print(num);
#endif
}

void AlexaUtils::logln(int num) {
#ifdef Alex2ESP_DEBUG
    Serial.println(num);
#endif
}

void AlexaUtils::log(uint16_t num) {
#ifdef Alex2ESP_DEBUG
    Serial.print(num);
#endif
}

void AlexaUtils::logln(uint16_t num) {
#ifdef Alex2ESP_DEBUG
    Serial.println(num);
#endif
}

void AlexaUtils::log(uint8_t num) {
#ifdef Alex2ESP_DEBUG
    Serial.print(num);
#endif
}

void AlexaUtils::logln(uint8_t num) {
#ifdef Alex2ESP_DEBUG
    Serial.println(num);
#endif
}


void AlexaUtils::logln(String string) {
#ifdef Alex2ESP_DEBUG
    Serial.println(string);
#endif
}
