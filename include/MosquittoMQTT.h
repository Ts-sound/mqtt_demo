
#pragma once

#include <mosquitto.h>

#include <cstring>
#include <iostream>

class MosquittoMQTT {
 public:
  MosquittoMQTT() {
    mosquitto_lib_init();
    mosq = mosquitto_new(NULL, true, NULL);
    if (!mosq) {
      std::cerr << "Failed to create mosquitto object!" << std::endl;
      return;
    }
    mosquitto_connect_callback_set(mosq, on_connect);
    mosquitto_message_callback_set(mosq, on_message);
  }

  ~MosquittoMQTT() {
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
  }

  bool connect(const char *host, int port, int keepalive) {
    if (mosquitto_connect(mosq, host, port, keepalive) != MOSQ_ERR_SUCCESS) {
      std::cerr << "Failed to connect to MQTT broker!" << std::endl;
      return false;
    }
    return true;
  }

  bool publish(const char *topic, const char *payload, int payloadlen, int qos,
               bool retain) {
    if (mosquitto_publish(mosq, NULL, topic, payloadlen, payload, qos,
                          retain) != MOSQ_ERR_SUCCESS) {
      std::cerr << "Failed to publish message to topic " << topic << std::endl;
      return false;
    }
    return true;
  }

  bool subscribe(const char *topic, int qos) {
    if (mosquitto_subscribe(mosq, NULL, topic, qos) != MOSQ_ERR_SUCCESS) {
      std::cerr << "Failed to subscribe to topic " << topic << std::endl;
      return false;
    }
    return true;
  }

  void loop() { mosquitto_loop(mosq, -1, 1); }

  void loop_forever() { mosquitto_loop_forever(mosq, -1, 1); }

 private:
  static void on_connect(struct mosquitto *mosq, void *userdata, int rc) {
    std::cout << "Connected to MQTT broker!" << std::endl;
  }

  static void on_message(struct mosquitto *mosq, void *userdata,
                         const struct mosquitto_message *message) {
    std::cout << "Received message on topic " << message->topic << ": "
              << (char *)message->payload << std::endl;
  }

  struct mosquitto *mosq;
};
