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
  delay(2000);
  turnRight(90);
  turnLeft(90);
  delay(2000);
  turnLeft(180);
  turnRight(180);
    //front and back
  // delay(5000);
  // forward(10);
  // reverse(10);
  // delay(5000);

  // // square
  // forward(10);
  // turnRight(90);
  // forward(10);
  // turnRight(90);
  // forward(10);
  // turnRight(90);
  // forward(10);

  // delay(5000);

  // //star
  // for(int i; i < 5; i++){ // star pattern twice
  //   forward(10);
  //   turnRight(144);
  // }
}