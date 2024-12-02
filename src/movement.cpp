#include "movement.h"

void reset() {
  analogWrite(left, 0);
  analogWrite(right, 0);
}

void forward(int distance, int speed) {
  speed = constrain(speed, 0, 255);
  analogWrite(left, 255);
  digitalWrite(lf, HIGH);
  digitalWrite(lb, LOW);
  analogWrite(right, 255);
  digitalWrite(rf, HIGH);
  digitalWrite(rb, LOW);
  
  // delay((unsigned long)(distance * 200 * (255.0 / speed)));
  // reset();
}

void reverse(int distance, int speed) {
  speed = constrain(speed, 0, 255);
  analogWrite(left, 255);
  digitalWrite(lf, LOW);
  digitalWrite(lb, HIGH);
  analogWrite(right, 255);
  digitalWrite(rf, LOW);
  digitalWrite(rb, HIGH);
  
  // delay((unsigned long)(distance * 200 * (255.0 / speed)));
  // reset();
}

void turnRight(int angle) {
  angle = constrain(angle, 0, 360);
  analogWrite(left, 255);
  digitalWrite(lf, HIGH);
  digitalWrite(lb, LOW);
  analogWrite(right, 255);
  digitalWrite(rf, LOW);
  digitalWrite(rb, HIGH);

  // delay((unsigned long)(angle * 800 / 180));
  // reset();
}

void turnLeft(int angle) {
  angle = constrain(angle, 0, 360);
  analogWrite(right, 255);
  digitalWrite(rf, HIGH);
  digitalWrite(rb, LOW);
  analogWrite(left, 255);
  digitalWrite(lf, LOW);
  digitalWrite(lb, HIGH);

  // delay((unsigned long)(angle * 800 / 180));
  // reset();
}

void circle(int innerSpeed, int outerSpeed, int duration) {
  innerSpeed = constrain(innerSpeed, 0, 255);
  outerSpeed = constrain(outerSpeed, 0, 255);
  digitalWrite(rf, HIGH);
  digitalWrite(rb, LOW);
  digitalWrite(lf, HIGH);
  digitalWrite(lb, LOW);
  analogWrite(right, outerSpeed);
  analogWrite(left, innerSpeed);

  delay(duration);
  reset();
}