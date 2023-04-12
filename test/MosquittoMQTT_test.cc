
#include "include/MosquittoMQTT.h" 
#include <gtest/gtest.h> 


TEST(mqtt,main){
  MosquittoMQTT mqtt;
    mqtt.connect("localhost", 1883, 60);
    mqtt.subscribe("test_topic", 0);
    mqtt.publish("test_topic", "Hello, MQTT!", strlen("Hello, MQTT!"), 0, false);
    mqtt.loop_forever();

}