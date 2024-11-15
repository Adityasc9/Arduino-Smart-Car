#include "movement.h"

void forward(int distance) {
  analogWrite(left, 255);
  digitalWrite(lf, HIGH);
  digitalWrite(lb, LOW);
  analogWrite(right, 255);
  digitalWrite(rf, HIGH);
  digitalWrite(rb, LOW);
  
  delay(200 * distance);
  reset(left, right);
}

void reverse(int distance) {
  analogWrite(left, 255);
  digitalWrite(lf, LOW);
  digitalWrite(lb, HIGH);
  analogWrite(right, 255);
  digitalWrite(rf, LOW);
  digitalWrite(rb, HIGH);
  
  delay(200 * distance);
  reset(left, right);
}

void turnRight(int angle) {
  analogWrite(left, 255);
  digitalWrite(lf, HIGH);
  digitalWrite(lb, LOW);
  analogWrite(right, 255);
  digitalWrite(rf, LOW);
  digitalWrite(rb, HIGH);
  float turnTime = 960 * (float)angle / 180;
  delay(turnTime);
  reset(left, right);
}

void turnLeft(int angle) {
  analogWrite(right, 255);
  digitalWrite(rf, HIGH);
  digitalWrite(rb, LOW);
  analogWrite(left, 255);
  digitalWrite(lf, LOW);
  digitalWrite(lb, HIGH);
  float turnTime = 960 * (float)angle / 180;
  delay(turnTime);
  reset(left, right);
}

void reset(int left, int right) {
  analogWrite(left, 0);
  analogWrite(right, 0);
  delay(300);
}

void circle(){
  digitalWrite(rf, HIGH);
  digitalWrite(rb, LOW);
  digitalWrite(lf, HIGH);
  digitalWrite(lb, LOW);
  analogWrite(right, 255);
  analogWrite(left, 128);
  delay(3000);
}
