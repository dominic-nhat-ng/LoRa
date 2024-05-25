#include <iostream>
#include <cstring>
#include "mosquitto.h"

// MQTT broker details
const char *broker_address = "demo.thingsboard.io";
const int broker_port = 1883;
const char *client_id = "Nhat";
const char *topic = "v1/devices/me/telemetry";
const char *username = "Nhat";
const char *password = "Nhat";

// ThingsBoard access token
// const char *access_token = "your_access_token";

// Data to be sent
const char *payload = "{\"temperature\":25.6, \"humidity\":55.0}";

// MQTT client
struct mosquitto *client = nullptr;

// Callback function for successful connection
void on_connect(struct mosquitto *mosq, void *userdata, int rc) {
    int result;
    if (rc == 0) {
        std::cout << "Connected to the broker" << std::endl;
        // Publish data when connectedtest.cpp
        result = mosquitto_publish(client, nullptr, topic, strlen(payload), payload, 0, false);
        if (result == MOSQ_ERR_SUCCESS) {
            std::cout << "Data published successfully" << std::endl;
        } else {
            std::cerr << "Failed to publish data: " << mosquitto_strerror(result) << std::endl;
        }
        
    } else {
        std::cerr << "Failed to connect to the broker: " << mosquitto_strerror(rc) << std::endl;
    }
}

// Main function
int main(int argc, char *argv[]) {
    // Initialize Mosquitto library
    mosquitto_lib_init();

    // Create MQTT client instance
    client = mosquitto_new(client_id, true, nullptr);
    if (!client) {
        std::cerr << "Failed to create Mosquitto client" << std::endl;
        return 1;
    }

    // Set access token for authentication
    mosquitto_username_pw_set(client, username, password);

    // Set connection callback
    mosquitto_connect_callback_set(client, on_connect);

    // Connect to the MQTT broker
    if (mosquitto_connect(client, broker_address, broker_port, 60) != MOSQ_ERR_SUCCESS) {
        std::cerr << "Failed to connect to the broker" << std::endl;
        return 1;
    }

    // Loop forever for callbacks
    mosquitto_loop_forever(client, -1, 1);

    // Cleanup
    mosquitto_destroy(client);
    mosquitto_lib_cleanup();

    return 0;
}
