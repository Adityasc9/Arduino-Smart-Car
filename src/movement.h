#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <Arduino.h>

extern int left;
extern int lf;
extern int lb;
extern int right;
extern int rf;
extern int rb;

void forward(int distance);
void reverse(int distance);
void turnRight(int angle);
void turnLeft(int angle);
void reset(int left, int right);
void circle();

#endif
