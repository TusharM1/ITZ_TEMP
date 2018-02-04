#include "drive.h"

FILE *fp;
bool isRecording = false, isReplaying = false;

void recordAuton() {

  // Checks if the file exists and if it is writable (and not readable)
  // If the file pointer is null, the button hasn't been pressed.
  //if(fp == NULL || access("auton.txt", F_OK) == -1 || access("auton.txt", W_OK) == -1) return

  if(fp == NULL || !isRecording) return;

  // Goes to the end of the file (it should anyway)
  //fseek(fp, 0, SEEK_END);

  // First 5 characters of recorder line.
  // Prints out sign, leading 0 (3 digit number), and space - Note: it needs to be %+04d and nothing else.
  // For example, the number -42 would be:
  // -042_
  fprintf(fp, "%+04d %+04d %d%d%d%d\n", joystick1, joystick3, triggerUp5, triggerDown5, triggerUp6, triggerDown6);

}

// Do nothing if it is replaying (it was probably a mistake)
//if(!isRecording || isReplaying) return;

// Whenever the recordAuton function is called, the isRecording boolean will toggle.
// For example, if it was not recording before, it is now.
// If it was recording before, it is not anymore.
////isRecording = !isRecording;

// It is not recording anymore so it will not do anything.
////if(!isRecording) return;

// The following code will only run if it is Recording now and not replaying.
//fp = fopen("auton.txt", "w");

void replayAuton() {

  // Don't run auton replayer of Button was not pressed.
  if(fp == NULL || !isRecording) return;

  // Goes to the beginning of the file (it should anyway)
  fseek(fp, 0, SEEK_SET);

  // For as many lines there are in the program, it should replay all of them.
	while(1) {

    // Character buffer, it should set the Motor values according to this.
		char arr[16];

    // Gets the Motor values for this tick
		fgets(arr, 15, fp);

    // Print the values to console (this should br removed after sufficient testing)
		printf("%s \n", arr);

    // TODO implement char[] to bin values converter

    // Returns if it reaches the end of the file
		if(fgetc(fp) == EOF) break;
	}

}
