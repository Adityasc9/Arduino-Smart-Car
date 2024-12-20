#include <Arduino.h>
#include "sensor.h"

float measureBackDistance() { // measure distance from behind the car
    digitalWrite(Trig_back, LOW);
    delayMicroseconds(2);
    digitalWrite(Trig_back, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trig_back, LOW);

    float duration = pulseIn(Echo_back, HIGH);
    return (duration * 0.0343) / 2;
}

float measureFrontDistance() { // measure distance from in front of the car
    digitalWrite(Trig_front, LOW);
    delayMicroseconds(2);
    digitalWrite(Trig_front, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trig_front, LOW);

    float duration = pulseIn(Echo_front, HIGH);
    return (duration * 0.0343) / 2;
}