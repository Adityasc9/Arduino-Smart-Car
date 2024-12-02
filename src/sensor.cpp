#include <Arduino.h>
#include "sensor.h"

float measureBackDistance() {
    digitalWrite(Trig_back, LOW);
    delayMicroseconds(2);
    digitalWrite(Trig_back, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trig_back, LOW);

    float duration = pulseIn(Echo_back, HIGH);
    return (duration * 0.0343) / 2;
}