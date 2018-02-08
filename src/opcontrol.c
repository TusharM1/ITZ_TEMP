#include "main.h"
#include "opControl.h"
//#include "Tushar.h"

// This is AutonRecorderv3
// Everything is in one file to reduce complexity

// Motor Values declaration
int joystick1, joystick3;
int triggerUp5, triggerDown5, triggerUp6, triggerDown6;

// Auton Handling variables declaration
FILE *fp = NULL;
bool isRecording = false;

int currentTime = 0, recordTime = 0, tickSpeed = 50;

void operatorControl() {

	while (1) {

		getMotors();
		setMotors();

		//printf("%d %d ", joystick1, joystick3);

		// Auton Recorder
		if(joystickGetDigital(1, 7, JOY_LEFT) && (currentTime > (recordTime + 1000))) {
			if(isRecording){
				isRecording = false;
				fclose(fp);
				printf("Recording End\n");
			}
			else {
				isRecording = true;
				fp = fopen("auton.txt", "w");
				printf("Recording Start\n");
			}
			recordTime = currentTime;
		}
		if(isRecording) {
			fseek(fp, 0, SEEK_END);
			fprintf(fp, "%+04d %+04d %d%d%d%d ", joystick1, joystick3, triggerUp5, triggerDown5, triggerUp6, triggerDown6);
			printf("%+04d %+04d %d%d%d%d\n", joystick1, joystick3, triggerUp5, triggerDown5, triggerUp6, triggerDown6);
		}

		// Auton Replayer
		if(joystickGetDigital(1, 7, JOY_RIGHT)) {
			if(!isRecording) {
				printf("Replaying Start \n");
				fp = fopen("auton.txt", "r");
				// Start Replaying
				fseek(fp, 0, SEEK_SET);
				while(1) {

					//printf("Start ");
					// Line and Value buffers for the reading the file;
					// There are 15 indexes but counting is 0-14
					char motorValues[16], valueBuffer[4], buttonValue[1];
					// Read and print the whole line from the file
					fgets(motorValues, 16, fp);
					printf("%s", motorValues);

					// Really Innefficient Code Here:
					// Not something I am particularly proud of, but it works.
					valueBuffer[0] = motorValues[0];
					valueBuffer[1] = motorValues[1];
					valueBuffer[2] = motorValues[2];
					valueBuffer[3] = motorValues[3];
					joystick1 = atoi(valueBuffer);
					printf("%d ", joystick1);

					valueBuffer[0] = motorValues[5];
					valueBuffer[1] = motorValues[6];
					valueBuffer[2] = motorValues[7];
					valueBuffer[3] = motorValues[8];
					joystick3 = atoi(valueBuffer);
					printf("%d ", joystick3);

					// Horribly innefficient way to convert characters to
					buttonValue[0] = motorValues[10];
					triggerUp5 = atoi(buttonValue);
					printf("%d ", triggerUp5);

					buttonValue[0] = motorValues[11];
					triggerDown5 = atoi(buttonValue);
					printf("%d ", triggerDown5);

					buttonValue[0] = motorValues[12];
					triggerUp6 = atoi(buttonValue);
					printf("%d ", triggerUp6);

					buttonValue[0] = motorValues[13];
					triggerDown6 = atoi(buttonValue);
					printf("%d ", triggerDown6);

					// Here is the old code that unfortunetly doesn't work for this project
					// Outside this project this code runs beautifully and efficiently

					// Save first value and print it
					// sprintf(valueBuffer," %.4s", motorValues);
					// joystick1 = atoi(valueBuffer);
					// printf("%d ", joystick1);

					// Save second value and print it
					// sprintf(valueBuffer," %.4s", motorValues + 5);
					// joystick3 = atoi(valueBuffer);
					// printf("%d ", joystick3);

					// Save all other values and print it
					// triggerUp5 = motorValues[10] - '0';
					// printf("%c ", motorValues[10]);
					//
					// triggerDown5 = motorValues[11] - '0';
					// printf("%c ", motorValues[11]);
					//
					// triggerUp6 = motorValues[12] - '0';
					// printf("%c ", motorValues[12]);
					//
					// triggerDown6 = motorValues[13] - '0';
					// printf("%c ", motorValues[13]);

					printf("\n");

					if(feof(fp)) break;
					setMotors(); // Sets the values of the motors.

					delay(tickSpeed);

				}

				fclose(fp);
				fp = NULL;

				printf("Replaying End\n");
			}
		}

		delay(tickSpeed);

		currentTime += tickSpeed;

	}

}

// Declare Motor Values:
// 2 Joysticks, 4 Triggers, 2 Buttons
void getMotors() {

	// Drive Controller
	if((abs)(joystickGetAnalog(1, 1)) > 20) joystick1 = joystickGetAnalog(1, 1); else joystick1 = 0;
	if((abs)(joystickGetAnalog(1, 3)) > 20) joystick3 = joystickGetAnalog(1, 3); else joystick3 = 0;

	// Claw Controller
	triggerUp5 = joystickGetDigital(1, 5, JOY_UP);
	triggerDown5 = joystickGetDigital(1, 5, JOY_DOWN);

	// Lift Controller
	triggerUp6 = joystickGetDigital(1, 6, JOY_UP);
	triggerDown6 = joystickGetDigital(1, 6, JOY_DOWN);

}

// Process Motors:
// Drive, Claw, and Lift
void setMotors() {

	// I don't understand any of this logic, but I'm assuming this works

	// Drive
	if (joystick3 != 0) {
		motorSet(MOTOR_BASE_LB, joystick3);
		motorSet(MOTOR_BASE_LF, joystick3);
		motorSet(MOTOR_BASE_RB, -joystick3);
		motorSet(MOTOR_BASE_RF, -joystick3);
	}
	else {
		motorSet(MOTOR_BASE_LB, joystick1);
		motorSet(MOTOR_BASE_LF, joystick1);
		motorSet(MOTOR_BASE_RB, joystick1);
		motorSet(MOTOR_BASE_RF, joystick1);
	}

	// Claw
	motorSet(CLAW, (triggerDown5 - triggerUp5) * 127);

	// Lift
	motorSet(LIFT_L, (triggerUp6 - triggerDown6) * 65);
	motorSet(LIFT_R, (triggerDown6 - triggerUp6) * 65);

}
