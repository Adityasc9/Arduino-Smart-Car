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
}

void loop() {
  for(int i; i < 10; i++){ // star pattern twice
    forward(10);
    turnRight(144);
  }
}