#include "autonRec.h"
#include "variables.h"
#include "main.h"
//IDEA: make a file, "auton1copy.txt" and record that to computer
void recordAuton(){
  FILE * fp;
  //if(fileNumber == 1)
    fp = fopen("auton1.txt", "w");
  /*if(fileNumber == 2)
    fp = fopen("auton2.txt", "w");
  if(fileNumber == 3)
    fp = fopen("auton3.txt", "w");*/

  int timeInMs = 0;
  bool recAuton = true;

  while(timeInMs <= 15000 && recAuton){

    int A3, A1, U5, D5, U6, D6;
    int THRESH = 20;

    if((abs)(joystickGetAnalog(1, 3)) > THRESH) {
      A3 = joystickGetAnalog(1, 3);
    }
    else A3 = 0;
    if((abs)(joystickGetAnalog(1, 1)) > THRESH) {
      A1 = joystickGetAnalog(1, 1);
    }
    else A1 = 0;
    if(A3 != 0)
      A1 = 0;
    D5 = joystickGetDigital(1, 5, JOY_DOWN);
    U5 = joystickGetDigital(1, 5, JOY_UP);
    D6 = joystickGetDigital(1, 6, JOY_DOWN);
    U6 = joystickGetDigital(1, 6, JOY_UP);

    drive(A3, A1);

    lift(U6, D6);

    claw(U5, D5);

    if(-100 < A3 && A3 < -THRESH) {
      fprintf(fp, "-0");
      printf("-0");
    }
    if(100 > A3 && A3 > THRESH) {
      fprintf(fp, "00");
      printf("00");
    }

    if(-100 < A3 && A3 < -THRESH) {
      fprintf(fp, "%d ", -A3);
      printf("%d ", -A3);
    }
    else if(A3 < -100) {
      fprintf(fp, "%d ", A3);
      printf("%d ", A3);
    }
    else if(A3 > THRESH && A3 < 100) {
      fprintf(fp, "%d ", A3);
      printf("%d ", A3);
    }
    else if(A3 > 100) {
      fprintf(fp, "0%d ", A3);
      printf("0%d ", A3);
    }
    else {
      fprintf(fp, "0000 ");
      printf("0000 ");
    }

    if(-100 < A1 && A1 < -THRESH) {
      fprintf(fp, "-0");
      printf("-0");
    }
    if(100 > A1 && A1 > THRESH) {
      fprintf(fp, "00");
      printf("00");
    }

    if(-100 < A1 && A1 < -THRESH) {
      fprintf(fp, "%d ", -A1);
      printf("%d ", -A1);
    }
    else if(A1 < -100) {
      fprintf(fp, "%d ", A1);
      printf("%d ", A1);
    }
    else if(A1 > THRESH && A1 < 100){
      fprintf(fp, "%d ", A1);
      printf("%d ", A1);
    }
    else if(A1 > 100) {
      fprintf(fp, "0%d ", A1);
      printf("0%d ", A1);
    }
    else {
      fprintf(fp, "0000 ");
      printf("0000 ");
    }

    fprintf(fp, "%d %d %d %d\n", U5, D5, U6, D6);
    printf("%d %d %d %d\n",  U5, D5, U6, D6);
    //printf("TEST3");
    delay(20);
    timeInMs+=20;
  //  printf("TEST4");

    if(joystickGetDigital(1, 7, JOY_LEFT) && timeInMs > 1000) { //ya i cant get it to stop
      recAuton = false;
      break;
      return;
    }
  }

  fprintf(fp, " ");
  printf(" ");
  fclose(fp);
}


//Something my brother told me about idk: fprintf(fileptr, "%d %d %d %d", analog[0]);
