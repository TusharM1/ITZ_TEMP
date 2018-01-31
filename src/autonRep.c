#include "autonRep.h"
#include "variables.h"
#include "main.h"
//NOTE: ACCOUNT FOR NEGATIVE SIGNS WHEN READING
void autonRep(){
  int A3, A1, U5, D5, U6, D6;
  FILE * fp;
  //if(fileNumber == 1)
    fp = fopen("auton1.txt", "r");
  /*if(fileNumber == 2)
    fp = fopen("auton2.txt", "r");
  if(fileNumber == 3)
    fp = fopen("auton3.txt", "r");
  //fp = fopen("TestDoc.txt", "r");*/
  char line[17];
  char ch;
  int lines = 0;
  //Count Lines:
/*  do {
    ch = fgetc(fp);
    if(ch == '\n')
        lines++;
  }while(ch != EOF);*/


  int timeInMs = 0;
  while (timeInMs <= 15000 && feof(fp) == 0) {
    fread(line, sizeof(char), 17, fp);
    printf("%s", line);


    A3 = (int)line[1]*100 + (int)line[2]*10 + (int)line[3];
    if(line[0] == '-')
      A3*=-1;
    A1 = (int)line[6]*100 + (int)line[7]*10 + (int)line[8];
    if(line[5] == '-')
      A1*=-1;
    U5 = (int)line[10];
    D5 = (int)line[12];
    U6 = (int)line[14];
    D6 = (int)line[16];

    drive(A3, A1);
    lift(U6, D6);
    claw(U5, D5);

    delay(1);
    timeInMs++;

    fseek(fp, sizeof(char), SEEK_CUR);
  }
  fclose(fp);
}

//fscanf(fileptr, "%d %d %d %d",mt.analog[0], mt.analog[1], );
