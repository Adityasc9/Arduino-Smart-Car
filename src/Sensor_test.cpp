#include <Arduino.h>
#include "sensor.h"

void setup() {
    Serial.begin(9600);
    pinMode(Trig_back, OUTPUT);
    pinMode(Echo_back, INPUT);
    Serial.println("Testing ultrasonic sensor");
}

void loop() {
    float distance = measureBackDistance();
    Serial.print("Measured Distance: ",distance);
    delay(1000);
}
