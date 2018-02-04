#ifndef DRIVE_H_
#define DRIVE_H_

#include "Autonomous.h"

#define MOTOR_BASE_LF 2
#define MOTOR_BASE_LM 3
#define MOTOR_BASE_LB 4
#define MOTOR_BASE_RF 5
#define MOTOR_BASE_RM 6
#define MOTOR_BASE_RB 7
#define LIFT_L 8
#define LIFT_R 9
#define CLAW 10

// Global "static" variables for multiple classes.
extern int joystick1;
extern int joystick3;
extern int triggerUp5;
extern int triggerDown5;
extern int triggerUp6;
extern int triggerDown6;

void drive(int joystick1, int joystick3);
void claw(int triggerUp5, int triggerDown5);
void lift(int triggerUp6, int triggerDown6);

#endif
