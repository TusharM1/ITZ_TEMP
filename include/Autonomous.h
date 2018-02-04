#ifndef AUTONOMOUS_H_
#define AUTONOMOUS_H_

//#include <unistd.h>
#include <API.h>
#include "main.h"

// Makes boolean variables accessable from all classes
extern bool isRecording;
extern bool isReplaying;

extern FILE *fp;

void recordAuton();
void replayAuton();

#endif
