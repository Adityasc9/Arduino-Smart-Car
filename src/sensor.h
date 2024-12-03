#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

extern int Trig_back;
extern int Echo_back;
extern int Trig_front;
extern int Echo_front;


float measureBackDistance();
float measureFrontDistance();

#endif