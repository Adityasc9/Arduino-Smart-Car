#include <Arduino.h>
#include "movement.h"

int left = 5;
int lf = 6;
int lb = 7;
int right = 11;
int rf = 13;
int rb = 12;
int stby = 8;

void setup() {
    pinMode(left, OUTPUT);
    pinMode(lf, OUTPUT);
    pinMode(lb, OUTPUT);
    pinMode(right, OUTPUT);
    pinMode(rf, OUTPUT);
    pinMode(rb, OUTPUT);
    pinMode(stby, INPUT);
    digitalWrite(stby, HIGH);
    delay(1000); // Shorter startup delay

    // Gradually increase speed
    for (int speed = 50; speed <= 200; speed += 10) {
        forward(1, speed); // Move forward with increasing speed
    }

    digitalWrite(stby, LOW);
}

void loop() {
}