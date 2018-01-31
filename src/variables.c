#include "variables.h"
#include "main.h"

fileNumber = 1;

<<<<<<< HEAD
void drive(int A3, int A1) {
  if(A3 !=0) {
    motorSet(MOTOR_BASE_LB, A3);
    motorSet(MOTOR_BASE_LM, A3);
    motorSet(MOTOR_BASE_LF, A3);
    motorSet(MOTOR_BASE_RB, -A3);
    motorSet(MOTOR_BASE_RM, -A3);
    motorSet(MOTOR_BASE_RF, -A3);
  }
  else {
    motorSet(MOTOR_BASE_LB, A1);
    motorSet(MOTOR_BASE_LM, A1);
    motorSet(MOTOR_BASE_LF, A1);
    motorSet(MOTOR_BASE_RB, A1);
    motorSet(MOTOR_BASE_RM, A1);
    motorSet(MOTOR_BASE_RF, A1);
  }
=======
void drive(int A2, int A3) {
  motorSet(MOTOR_BASE_LB, -A3);
  motorSet(MOTOR_BASE_LM, -A3);
  motorSet(MOTOR_BASE_LF, A3);
  motorSet(MOTOR_BASE_RB, -A2);
  motorSet(MOTOR_BASE_RM, -A2);
  motorSet(MOTOR_BASE_RF, -A2);
>>>>>>> 3ee8196ede603b22942b827d56699702a551bc06
}

void lift(int U6, int D6) {
    motorSet(LIFT_L, (U6-D6)*65);
    motorSet(LIFT_R, -(U6-D6)*65);
}

void claw(int U5, int D5) {
  motorSet(CLAW, -(U5-D5)*127);
}

void moveFunctions() {
  int A2, A3, D5, U5, D6, U6, U8;
  int THRESH = 20;
  while(true){
      if((abs)(joystickGetAnalog(1, 2)) > THRESH) {
        A2 = joystickGetAnalog(1, 2);
      }
      else A2 = 0;
      if((abs)(joystickGetAnalog(1, 3)) > THRESH) {
        A3 = joystickGetAnalog(1, 3);
      }
      else A3 = 0;
      D5 = joystickGetDigital(1, 5, JOY_DOWN);
      U5 = joystickGetDigital(1, 5, JOY_UP);
      D6 = joystickGetDigital(1, 6, JOY_DOWN);
      U6 = joystickGetDigital(1, 6, JOY_UP);
      U8 = joystickGetDigital(1, 8, JOY_UP);

      /*if(U8) {
        if(fileNumber == 1)
          fileNumber = 2;
        if(fileNumber == 2)
          fileNumber = 3;
        if(fileNumber == 3)
          fileNumber = 1;
      }*/

      drive(A2, A3);

      lift(U6, D6);

      claw(U5, D5);
    }
}
