
#include "include/MosquittoMQTT.h"

#include <gtest/gtest.h>

#include <thread>

TEST(mqtt, main) {
  MosquittoMQTT mqtt;
  mqtt.connect("localhost", 1883, 60);
  mqtt.subscribe("test_topic", 0);
  mqtt.publish("test_topic", "Hello, MQTT!", strlen("Hello, MQTT!"), 0, false);

  mqtt.loop_start();
  int cc = 10;
  while (cc--) {
    std::string s = "hello " + std::to_string(cc);
    mqtt.publish("test_topic", s.c_str(), s.size(), 0, false);
  }

  sleep(5);

  mqtt.loop_stop();
}