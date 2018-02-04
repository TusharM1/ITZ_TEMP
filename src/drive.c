#include "drive.h"

// A more efficient version of the drive code.
// This code assumes that Joystick3 controls the forwards-backwards motion of the drive,
// while Joystick1 controls the point turning of the drive.

void drive(int Joystick1, int Joystick3) {

  if (Joystick3 != 0) {
    motorSet(MOTOR_BASE_LB, Joystick3);
    motorSet(MOTOR_BASE_LF, Joystick3);
    motorSet(MOTOR_BASE_RB, -Joystick3);
    motorSet(MOTOR_BASE_RF, -Joystick3);
  }
  else {
    motorSet(MOTOR_BASE_LB, Joystick1);
    motorSet(MOTOR_BASE_LF, Joystick1);
    motorSet(MOTOR_BASE_RB, Joystick1);
    motorSet(MOTOR_BASE_RF, Joystick1);
  }

}

//QUESTION Where did 127 come from?
void claw(int triggerUp5, int triggerDown5) {
  motorSet(CLAW, (triggerDown5 - triggerUp5) * 127);
}

//QUESTION Where did 65 come from?
void lift(int triggerUp6, int triggerDown6) {
    motorSet(LIFT_L, (triggerUp6 - triggerDown6) * 65);
    motorSet(LIFT_R, (triggerDown6 - triggerUp6) * 65);
}
