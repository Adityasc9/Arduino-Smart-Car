#include <Arduino.h>
#include "movement.h"

int left = 5;
int lf = 6;
int lb = 7;
int right = 11;
int rf = 13;
int rb = 12;

void setup() {
    pinMode(left, OUTPUT);
    pinMode(lf, OUTPUT);
    pinMode(lb, OUTPUT);
    pinMode(right, OUTPUT);
    pinMode(rf, OUTPUT);
    pinMode(rb, OUTPUT);
    delay(5000);

    forward(5);
    reverse(5);

    //square
    for(int i = 0; i < 4; i++){
        forward(5);
        turnRight(90);
    }
    turnRight(120);

    circle();
  
}

void loop() {
}