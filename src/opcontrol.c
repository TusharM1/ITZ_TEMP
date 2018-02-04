/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */
#include "drive.h"

/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */

int joystick1 = 0, joystick3 = 0;
int triggerUp5, triggerDown5, triggerUp6, triggerDown6;

void operatorControl() {

	while (1) {

		// Get Motor Values
		triggerUp5 = joystickGetDigital(1, 5, JOY_UP);
		triggerDown5 = joystickGetDigital(1, 5, JOY_DOWN);
		triggerUp6 = joystickGetDigital(1, 6, JOY_UP);
		triggerDown6 = joystickGetDigital(1, 6, JOY_DOWN);

		if((abs)(joystickGetAnalog(1, 1)) > 20) joystick1 = joystickGetAnalog(1, 1);
		if((abs)(joystickGetAnalog(1, 3)) > 20) joystick3 = joystickGetAnalog(1, 3);

		// Set Motor Values
		drive(joystick1, joystick3);
		claw(triggerUp5, triggerDown5);
		lift(triggerUp6, triggerDown6);

		if(joystickGetDigital(1, 7, JOY_LEFT)) {
			if(isRecording) {
				isRecording = !isRecording;
				fclose(fp);
			}
			if(!isReplaying && fp == NULL) {
				isRecording = !isRecording;
				fp = fopen("auton.txt", "a");
			}
		}

		if(joystickGetDigital(1, 7, JOY_RIGHT)) {
			if(isReplaying) {
				isReplaying = !isReplaying;
				fclose(fp);
			}
			if(!isRecording && fp == NULL) {
				isReplaying = !isReplaying;
				fp = fopen("auton.txt", "r");
			}
		}

		recordAuton();
		replayAuton();

		// This logic really needs to be stream-lined and reworked
		// Auton Processing (hopefully with minimal computational overhead)

		//If the Auton Recorder button is pressed
		if(joystickGetDigital(1, 7, JOY_LEFT)) {
			// If the file is not NULL (it already exists, either it is already recording or it is replaying),
			// then open the file in write mode.
			if(fp != NULL) {
				// Checks if the file is in write mode (if it is currently recording) and closed the file and sets the pointer to null.

				// if(isRecording)
				//if(access("auton.txt", W_OK)) {
					fclose(fp);
					fp = NULL;
				//}
			}
			else fp = fopen("auton.txt", "w");
		}

		if(joystickGetDigital(1, 7, JOY_RIGHT)) {
			// If the file is not NULL (it already exists, either it is already recording or it is replaying),
			// then open the file in write mode.
			if(fp != NULL) {
				// Checks if the file is in write mode (if it is currently recording) and closed the file and sets the pointer to null.
				//if(access("auton.txt", R_OK)) {
					fclose(fp);
					fp = NULL;
				//}
			}
			else fp = fopen("auton.txt", "r");
		}

		// Even if it is not recording or replaying, the function is still called
		// This may change later
		recordAuton();
		replayAuton();

		delay(20);

	}

}
