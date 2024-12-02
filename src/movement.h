#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <Arduino.h>

extern int left;
extern int lf;
extern int lb;
extern int right;
extern int rf;
extern int rb;

void forward(int speed);
void reverse(int speed);
void turnRight(int speed);
void turnLeft(int speed);
void reset();
void circle(int innerSpeed, int outerSpeed, int duration);

#endif
