#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

/*
 * Program Filename: campav.buildrooms.c
 * Author: Victor Daniel Campa
 * Date: 1/1/19
 * Description: creates a directory where multiple files are contained inside a folder where in the contents of each file has
 * the contents of each room along with it's connection and type where the connnections are randomized and the amount of rooms being 7\
 * the connections can be between 3 to 6.
*/

/*structure that contains the name the type of room, the number of outboundConnections and structure that contains the room*/
struct room
{
  char* name;
  char* type;
  int numOutboundConnections;
  struct room* outboundConnections[6];
};

/*
######################################
 * Function: PrintRoomOutboundConnections
 * Description: prints the connections in a folder depending on the room
 * Parameter: all the structure rooms created, identify which is what it wants to open and buffer so we can write on the files
 * Pre-Conditions: input has the structure created on main, identify has the pid and buffer is an array that lets me write on the files
 * Post-Conditions: the structure gets called on it's name type and connections and creates a folder then creates the file which will
 * contain the information stored in the structure.
#######################################
*/
void PrintRoomOutboundConnections(struct room* input, int identify, char* buffer)
{
  FILE *fp; /*we create a file pointer so we can add the files to the directory*/
  sprintf(buffer, "./campav.rooms.%d/%s", identify, input->name);
  fp = fopen (buffer, "w");
  int m;
  /*we first start with writing the name*/
  fprintf(fp, "ROOM NAME: %s\n", input->name);
  /*we loop through the number of outbound connections*/
  for (m = 0; m < input->numOutboundConnections; m++) {
    fprintf(fp, "CONNECTION %d: ", m);
    fprintf(fp, "%s\n", input->outboundConnections[m]->name);
  }
  /*finally we get the room type*/
  fprintf(fp, "ROOM TYPE: %s\n", input->type);
  fclose (fp); /*we finish off by closing the file*/
}

/*
######################################
 * Function: resetRooms
 * Description: changes the whole array number to -1
 * Parameter: we pass the array number and the amount we want to iterate through.
 * Pre-Conditions: the array num contains nothing or something
 * Post-Conditions: all the info in array gets set to -1
#######################################
*/
void resetRooms(int *num, int counting)
{
  int b;
  /*we are looping thorugh the size of num and replacing the whole contents with -1*/
  for (b = 0; b < counting; b++) {
    num[b] = -1;
  }
}

/*
######################################
 * Function: GenerateConnections
 * Description: using an array we want to get unique random numbers and with those unique random numbers
 * we are going to assign a unique room to a connection
 * Parameter: we pass the array num and counting which will iterate to a certain amount and randomize a unique connection
 * Pre-Conditions: num contains -1's and counting contains a number depending on what kind of connnections we want.
 * Post-Conditions: num contains random numbers to a certain amount which is determined by counting
#######################################
*/
void GenerateConnections(int *num, int counting)
{
  /*we initate count to 0*/
  int count = 0;
  /*we create randNum*/
  int randNum;
  /*we create found*/
  bool obtained;
  int i;
  /*we are going to loop until we get all random unique numbers*/
  while (count < counting) {
    obtained = false; /*we initalize obtained to false to start off it it's actually false*/
    randNum = rand() % counting;
    for (i = 0; i < counting; i++) {
      if(num[i] == randNum) /*checks if the numbers stored in the array are equal if they are we dont want to store it in the arr num*/
      {
        obtained = true; /*turns true if the numbers are the same*/
        break; /*we break so since we don't have to check anymore numbers*/
      }
    }
    /*we enter this if if the first if does not change the variable to true*/
    if(obtained == false)
    {
      num[count] = randNum; /*we store the random number*/
      count++; /*we increment the index for arr*/
    }
  }
}

/*
######################################
 * Function: main
 * Description: we will create our pid our buffer and randomization on the start of main then after I am going to allocate room
 * for all my structures and assign them a name which should be random. Once finished I am going to create a array of structures
 * then I can refer to certain structure while avoiding having connection connecting to itself. Once done I will call the functions
 * above then afterwards I'll be able to for loop through each connection and assign them the proper connections.
 * Parameter: NONE
 * Pre-Conditions: NONE
 * Post-Conditions: NONE
#######################################
*/
int main(int argc, char* argv[])
{
  /*we call these two lines to actually get random values*/
  time_t t;
  srand((unsigned) time(&t));

/*buffer will be used to write to the file*/
  char buffer[50];
  pid_t pid = getpid(); /*the pid get a unique id number when a folder is created*/
  sprintf(buffer, "campav.rooms.%d", (int)pid); /*we create the exact format for the folder*/
  mkdir(buffer, 0700); /*we create the directory*/
  int id = (int)pid; /*we assign pid to id so we can use it for a function*/

/*we create the struct and assign their types*/
/*this is the startroom we allocate the name and type and assign them*/
  struct room startRoom;
  startRoom.name = calloc(16, sizeof(char));
  strcpy(startRoom.name, "Room0");
  startRoom.type = calloc(16, sizeof(char));
  strcpy(startRoom.type, "START_ROOM");
/*this is the midroom we allocate the name and type and assign them*/
  struct room midRoom1;
  midRoom1.name = calloc(16, sizeof(char));
  strcpy(midRoom1.name, "Room1");
  midRoom1.type = calloc(16, sizeof(char));
  strcpy(midRoom1.type, "MID_ROOM");
/*this is the midroom we allocate the name and type and assign them*/
  struct room midRoom2;
  midRoom2.name = calloc(16, sizeof(char));
  strcpy(midRoom2.name, "Room2");
  midRoom2.type = calloc(16, sizeof(char));
  strcpy(midRoom2.type, "MID_ROOM");
/*this is the midroom we allocate the name and type and assign them*/
  struct room midRoom3;
  midRoom3.name = calloc(16, sizeof(char));
  strcpy(midRoom3.name, "Room3");
  midRoom3.type = calloc(16, sizeof(char));
  strcpy(midRoom3.type, "MID_ROOM");
/*this is the midroom we allocate the name and type and assign them*/
  struct room midRoom4;
  midRoom4.name = calloc(16, sizeof(char));
  strcpy(midRoom4.name, "Room4");
  midRoom4.type = calloc(16, sizeof(char));
  strcpy(midRoom4.type, "MID_ROOM");
/*this is the midroom we allocate the name and type and assign them*/
  struct room midRoom5;
  midRoom5.name = calloc(16, sizeof(char));
  strcpy(midRoom5.name, "Room5");
  midRoom5.type = calloc(16, sizeof(char));
  strcpy(midRoom5.type, "MID_ROOM");
/*this is the endroom we allocate the name and type and assign them*/
  struct room endRoom;
  endRoom.name = calloc(16, sizeof(char));
  strcpy(endRoom.name, "Room6");
  endRoom.type = calloc(16, sizeof(char));
  strcpy(endRoom.type, "END_ROOM");

  int num[7]; /*we use num to assign the right connections to the outboundconnections*/

/*this whole piece of code reset rooms and loop assigns connections for the startroom*/
  resetRooms(num,7);
  struct room start[7]={midRoom1,midRoom2,midRoom3,midRoom4,midRoom5};

  startRoom.numOutboundConnections = 3 + rand() % 3; /*gets a random connection*/
  GenerateConnections(num,5); /*gets a random rooms*/
  int i;
  /*assigns the random numbers to the outboundconnections*/
    for (i = 0; i < startRoom.numOutboundConnections; i++) {
      startRoom.outboundConnections[i] = &start[num[i]];
    }

/*this whole piece of code reset rooms and loop assigns connections for the midroom1*/
  resetRooms(num,7);
  struct room arrmid1[7]={startRoom,midRoom2,midRoom3,midRoom4,midRoom5,endRoom};

  midRoom1.numOutboundConnections = 3 + rand() % 4; /*gets a random connection*/
  GenerateConnections(num,6); /*gets a random rooms*/
  int a;
    /*assigns the random numbers to the outboundconnections*/
    for (a = 0; a < midRoom1.numOutboundConnections; a++) {
      midRoom1.outboundConnections[a] = &arrmid1[num[a]];
    }

/*this whole piece of code reset rooms and loop assigns connections for the midroom2*/
  resetRooms(num,7);
  struct room arrmid2[7]={startRoom,midRoom1,midRoom3,midRoom4,midRoom5,endRoom};

  midRoom2.numOutboundConnections = 3 + rand() % 4; /*gets a random connection*/
  GenerateConnections(num,6); /*gets a random rooms*/
  int b;
    /*assigns the random numbers to the outboundconnections*/
    for (b = 0; b < midRoom2.numOutboundConnections; b++) {
      midRoom2.outboundConnections[b] = &arrmid2[num[b]];
    }

/*this whole piece of code reset rooms and loop assigns connections for the midroom3*/
  resetRooms(num,7);
  struct room arrmid3[7]={startRoom,midRoom1,midRoom2,midRoom4,midRoom5,endRoom};

  midRoom3.numOutboundConnections = 3 + rand() % 4; /*gets a random connection*/
  GenerateConnections(num,6); /*gets a random rooms*/
  int c;
    /*assigns the random numbers to the outboundconnections*/
    for (c = 0; c < midRoom3.numOutboundConnections; c++) {
      midRoom3.outboundConnections[c] = &arrmid3[num[c]];
    }

/*this whole piece of code reset rooms and loop assigns connections for the midroom4*/
  resetRooms(num,7);
  struct room arrmid4[7]={startRoom,midRoom1,midRoom2,midRoom3,midRoom5,endRoom};

  midRoom4.numOutboundConnections = 3 + rand() % 4; /*gets a random connection*/
  GenerateConnections(num,6); /*gets a random rooms*/
  int d;
    /*assigns the random numbers to the outboundconnections*/
    for (d = 0; d < midRoom4.numOutboundConnections; d++) {
      midRoom4.outboundConnections[d] = &arrmid4[num[d]];
    }

/*this whole piece of code reset rooms and loop assigns connections for the midroom5*/
  resetRooms(num,7);
  struct room arrmid5[7]={startRoom,midRoom1,midRoom2,midRoom3,midRoom4,endRoom};

  midRoom5.numOutboundConnections = 3 + rand() % 4; /*gets a random connection*/
  GenerateConnections(num,6); /*gets a random rooms*/
  int e;
    /*assigns the random numbers to the outboundconnections*/
    for (e = 0; e < midRoom5.numOutboundConnections; e++) {
      midRoom5.outboundConnections[e] = &arrmid5[num[e]];
    }

/*this whole piece of code reset rooms and loop assigns connections for the finalroom*/
    resetRooms(num,7);
    struct room end[7]={startRoom,midRoom1,midRoom2,midRoom3,midRoom4,midRoom5};

    endRoom.numOutboundConnections = 3 + rand() % 4; /*gets a random connection*/
    GenerateConnections(num,6); /*gets a random rooms*/
    int f;
      /*assigns the random numbers to the outboundconnections*/
      for (f = 0; f < endRoom.numOutboundConnections; f++) {
        endRoom.outboundConnections[f] = &end[num[f]];
      }

/*we loop through all the outbound connections to write to the file*/
  PrintRoomOutboundConnections(&startRoom,id,buffer);
  PrintRoomOutboundConnections(&midRoom1,id,buffer);
  PrintRoomOutboundConnections(&midRoom2,id,buffer);
  PrintRoomOutboundConnections(&midRoom3,id,buffer);
  PrintRoomOutboundConnections(&midRoom4,id,buffer);
  PrintRoomOutboundConnections(&midRoom5,id,buffer);
  PrintRoomOutboundConnections(&endRoom,id,buffer);

  return 0;
}
