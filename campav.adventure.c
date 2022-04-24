#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pthread.h>

/*
 * Program Filename: campav.buildrooms.c
 * Author: Victor Daniel Campa
 * Date: 11/1/19
 * Description: this part starts the game but first we get all of the content from my files stored inside a folder once
 * I have all the information inside I will run the game for the user.
*/


/*using a similar structure to store my information*/
struct room
{
  char* name;
  char* type;
  int numOutboundConnections;
  struct room* outboundConnections[6];
};

pthread_mutex_t mutex; /*declaring the mutex globally*/


/*
######################################
 * Function: readfiles
 * Description: we read each file we get the number of lines the arr filled up corresponding to the connections
 * Parameter: we are passing the struct room the num arr the integer amount and final result which cointains the path
 * Pre-Conditions: the full arr num contains -1's, has the amount which is initally 0, and the finalresult which is the directory and contains the struct
 * Post-Conditions: some of the arr num change depending on the midroom connections and amount gets overwritten by the number of lines in the file -2, and the roomname for the name and type get assigned
#######################################
*/
void readfiles(struct room roomname, int *num, int *amount, char **finalresult)
{
  /*the FILE* fptr's are for being able to open a file and char ch will be used to read each individual character*/
  FILE* fPtr;
  FILE* fPtr2;
  char ch;

  /*we are going to open and read the contents of each room file*/
  fPtr = fopen(*finalresult, "r");
  fPtr2 = fopen(*finalresult, "r");


/*I initalize a char arr of 1000 and a integer counter that will keep track of my arr position*/
  char arr[1000];
  int counter = 0;

  int count = 0;
  char c;
  /*in here we are going to loop thorugh multiple times to get the count of lines*/
  for (c = getc(fPtr2); c != EOF; c = getc(fPtr2))
  {
    if (c == '\n')
    {
      count++;
    }
  }
  /*we are then going to assign the count to amount which is originally declared in main so we can assign it to the the numOutboundConnections*/
  *amount = count - 2;


int space = 0; /*used to determine when to read the characters*/
int stop = 0; /*used to determine when to stop while loop*/
int a = 0; /*used to go through my arr indexes*/
int numrooms = 0;
  while(stop < count)
  {
    ch = fgetc(fPtr); /*we read all the contents of the file character by character*/
    if(space == 2) /*we will enter here when we have dectected two spaces in the file*/
    {
      arr[counter] = ch; /*we assign the contents of the file into counter*/
      counter++; /*we then increment so we don't overwrite the information stored*/
    }

    if(ch == ' ')
    {
      space++; /*a space was dectected so we increment space by 1*/
    }

    if(ch == '\n')
    {
      strtok(arr, "\n"); /*we get get rid of the newline that was added*/
      if(numrooms == 0)
    {
      strcpy(roomname.name, arr); /*we are going to copy the arr into the name structure*/
      numrooms++;
    }

    /*REFERENCES TO OBJECTS*/
    /*objects[0] is Room5*/
    /*objects[1] is startRoom0*/
    /*objects[2] is Room3*/
    /*objects[3] is End_Room6*/
    /*objects[4] is Room2*/
    /*objects[5] is Room1*/
    /*objects[6] is Room4*/
    /*I have no idea why they are refernece this way*/
    /*I went to the instructors office hours and he had no clue as well*/
    /*This is why num is being assigned different numbers on these cases*/
    /*in the giant if we are going to check if numrooms is not on the first line nor the last line and I can assign the correct information to my num array*/
    if(numrooms != count && numrooms != 1)
    {
      if (strcmp(arr, "Room0") == 0) {
        num[a] = 1;
        a++;
      }
      else if (strcmp(arr, "Room1") == 0) {
        num[a] = 5;
        a++;
      }
      else if (strcmp(arr, "Room2") == 0) {
        num[a] = 4;
        a++;
      }
      else if (strcmp(arr, "Room3") == 0) {
        num[a] = 2;
        a++;
      }
      else if (strcmp(arr, "Room4") == 0) {
        num[a] = 6;
        a++;
      }
      else if (strcmp(arr, "Room5") == 0) {
        num[a] = 0;
        a++;
      }
      else if (strcmp(arr, "Room6") == 0) {
        num[a] = 3;
        a++;
      }
    }

    if(numrooms == count) /*if we reach the last line we want to store the room type*/
    {
      strcpy(roomname.type, arr);
      memset(arr, 0, sizeof(arr));
      break; /*we break once we have all the information since we have already got the last information needed from the room file*/
    }
    /*variables here are added to make sure nothing goes out of bound or gets overwritten or segfaults*/
      stop++;
      memset(arr, 0, sizeof(arr));
      counter -= counter;
      space -= space;
      numrooms++;
    }
  }
}


/*
######################################
 * Function: GetCurrentTime
 * Description: gets the format and write to the file currentTime.txt
 * Parameter: NONE
 * Pre-Conditions: NONE
 * Post-Conditions: NONE
#######################################
*/
void* GetCurrentTime(void *args)
{
/*we initalize current time and obtain the time here*/
time_t CurrentTime;
time(&CurrentTime);
struct tm* now = localtime(&CurrentTime); /*we get the current time right now into now*/
char timestring[1000];
/*we use strftime and put in a string the follwing format shown in the assignment page*/
strftime(timestring,1000, "%l:%M%P %A, %B %d, %Y", now);
char *finaltime = malloc(strlen(timestring) + 2);
strcpy(finaltime, timestring);
/*we are adding the new line to the final time*/
strcat(finaltime, "\n");
FILE *ptr = fopen("currentTime.txt", "w"); /*we are opening this next file so we can write the time*/
fprintf(ptr, finaltime); /*we write the time into the file called CurrentTime.txt*/
fclose(ptr);
}

/*
######################################
 * Function: Read
 * Description: prints the current time by reading from the file currentTime.txt
 * Parameter: NONE
 * Pre-Conditions: NONE
 * Post-Conditions: NONE
#######################################
*/
void ReadTime()
{
/*we create a file pointer to read the contents inside currentTime*/
FILE *fptr;
fptr = fopen("currentTime.txt", "r");
  char c;
  int x = 0;
  printf("\n");
  /*prints the whole contents of the line line by line*/
  while (c != EOF)
  {
      printf ("%c", c);
      c = fgetc(fptr);
  }
  /*adds a new line and closes file*/
  printf("\n");
  fclose(fptr);
}

/*
######################################
 * Function: resetRooms
 * Description: changes the nums to -1's
 * Parameter: int pointer num which is an array and int counting which is the amount that we loop through
 * Pre-Conditions: num which is null initially and counting which is always 7
 * Post-Conditions: NONE
#######################################
*/
void resetRooms(int *num, int counting)
{
  /*we are looping thorugh the size of num and replacing the whole contents with -1*/
  int b;
  for (b = 0; b < counting; b++) {
    num[b] = -1;
  }
}

/*
######################################
 * Function: main
 * Description: creates part of the directory and gets the current directory and starts the game assigns the outboundconnections in here from arr num
 * Parameter: NONE
 * Pre-Conditions: NONE
 * Post-Conditions: NONE
#######################################
*/
int main()
{
/*USING EXAMPLE CODE FROM BLOCK 2 FOR GETTING THE MOST CURRENT DIRECTORY*/
int newestDirTime = -1;
char targetDirPrefix[32] = "campav.rooms.";
char newestDirName[256]; /*tihs is where we will store the most current directory*/
memset(newestDirName, '\0', sizeof(newestDirName));
DIR* dirToCheck; /*used to read the directories*/
struct dirent *fileInDir; /*will be used to check the files*/
struct dirent *files; /*will be used to check the files*/
struct stat dirAttributes; /*used to get the time*/
dirToCheck = opendir("."); /*we will be opening the directory we are currently on*/
pthread_t tid;


if (dirToCheck > 0)
{
  while ((fileInDir = readdir(dirToCheck)) != NULL) /*we are going to loop thorugh all the files in the directory*/
  {
    if (strstr(fileInDir->d_name, targetDirPrefix) != NULL) /*check if that file has the target prefix campav.rooms.*/
    {
      if ((int)dirAttributes.st_mtime > newestDirTime) /*if it has the prefix we want to get the mmost currently created campav.rooms.*/
      {
        /*in here we store the most newly created file directory in newestDirTime*/
        newestDirTime = (int)dirAttributes.st_mtime;
        memset(newestDirName, '\0', sizeof(newestDirName));
        strcpy(newestDirName, fileInDir->d_name);
      }
    }
  }
}
/*we open the most newest directory created if it can't be open we will display an error and return 0*/
DIR *dr = opendir(newestDirName);
if (dr == NULL)
{
    printf("Could not open current directory" );
    return 0;
}


/*this struct refers to */
struct room objects[7];
int num[7];
int amount = 0;
int inc = 0;
/*this whole while loop will loop thorugh the the files inside the folder
and will read the contents and store them in the struct in summary*/
while ((files = readdir(dr)) != NULL)
{
  /*we want to ignore . and .. since they are not files*/
  if ( !strcmp(files->d_name, ".") || !strcmp(files->d_name, "..") )
  {
    /* don't do anything */
  }
  else
  {
    /*this will get the path in this case campav.rooms.(pid_here)/(room_here)*/
    const char* pathdir = "/";

    /*in here I am adding the / to the current directory and copying the new variable result*/
    const size_t len1 = strlen(newestDirName);
    const size_t len2 = *pathdir;
    char *result = malloc(len1 + len2 + 1);
    memcpy(result, newestDirName, len1);
    memcpy(result + len1, pathdir, len2 + 1);

    /*In here I am then getting each directory name and storing it to the new variable finalresult*/
    const size_t len3 = strlen(result);
    const size_t len4 = strlen(files->d_name);
    char* finalresult = malloc(len3 + len4 + 1);
    memcpy(finalresult, result, len3);
    memcpy(finalresult + len3, files->d_name, len4 + 1);

    /*In here I get all the information stored to my struct*/
    amount = 0;
    resetRooms(num, 7); /*this resets the values of num to -1's*/

    /*these two allocate memory for the name and type*/
    objects[inc].name = calloc(16, sizeof(char));
    objects[inc].type = calloc(16, sizeof(char));

    /*readfiles reads each file rooms contents name, type, and connections*/
    /*connections will be stored as numbers in the array num and the amount*/
    /*will carry the number of connections for that room file*/
    readfiles(objects[inc],num, &amount, &finalresult);
    objects[inc].numOutboundConnections = amount;

    /*in this loop we are going to assign all the corresponding object to a outboundconnection*/
    int h;
    for (h = 0; h < objects[inc].numOutboundConnections; h++)
    {
      objects[inc].outboundConnections[h] = &objects[num[h]];
    }
    /*increments by 1 so we know what struct room object we are refering to*/
    inc++;
  }
}

/*declaring these to use it when the game starts*/
/*store route will store the route the user took*/
/*pick connection will store the input of the user*/
char pickconnection[20];
char *storeroute[1000];
/*there two bools where if game is false the game will end*/
/*the other bool wis for checking if the connection is bad*/
bool game = true;
bool badconnection = true;
/*loc refers to the room I am refering to in this case this is the start room*/
/*the step is just a counter on how many rooms has been taken*/
int loc = 1;
int steps = 0;

/*this giant while loop is going to initiate to start the game*/
while (game == true) {
  badconnection = true;
  printf("CURRENT LOCATION: %s\n", objects[loc].name);
  int m;
  printf("%s", "POSSIBLE CONNECTIONS: ");
  /*we loop through the connections that are possible for that room*/
  for (m = 0; m < objects[loc].numOutboundConnections; m++) {
    printf("%s", objects[loc].outboundConnections[m]->name);
    /*formats , and . so that it's the right format from the example used*/
    if(objects[loc].numOutboundConnections-1 > m)
      {
        printf(", ");
      }
    else
      {
        printf(".");
      }
  }
  printf("\n");
  printf("WHERE TO? >");
  scanf("%s", &pickconnection); /*gets the input from the user*/
  int b;
  /*this first for loop is going to loop thorugh all the connections based on the input*/
  for (b = 0; b < objects[loc].numOutboundConnections; b++)
  {
    /*check if the connection is equal to one of the connections*/
    if(strcmp(pickconnection, objects[loc].outboundConnections[b]->name) == 0)
    {
      printf("\n");
      badconnection = false; /*we turn badconnection to false since we don't want want to print saying that the room is invalid*/
      int p;
      for (p = 0; p < 6; p++) {
      if(strcmp(objects[p].name, objects[loc].outboundConnections[b]->name) == 0)
      {
        /*check if the path is the final room in this case its room6*/
        if(strcmp("Room6", objects[loc].outboundConnections[b]->name) == 0)
        {
          storeroute[steps] = objects[loc].outboundConnections[b]->name;
          printf("YOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n");
          printf("YOU TOOK %d STEPS. YOUR PATH TO VICTORY WAS:\n", steps+1);
          int s;
          /*prints the full path taken*/
          for (s = 0; s < steps+1; s++) {
            printf("%s\n", storeroute[s]);
          }
          return 0;
        }
        storeroute[steps] = objects[loc].outboundConnections[b]->name;
        loc = p;
        steps++;
        break;
      }
    }
    }
  }
  /*if the user says time we will create a thread and proceed to do multithreading*/
  if(strcmp(pickconnection, "time") == 0)
  {
    pthread_t thread; /*creates a thread*/
    pthread_mutex_init(&mutex,NULL); /*initalize the mutex first*/
    pthread_mutex_lock(&mutex); /*we then lock the mutex and work on that thread*/
    pthread_create(&thread, NULL, GetCurrentTime, NULL); /*process the thread*/
    pthread_mutex_unlock(&mutex); /*unlocks the mutex*/
    pthread_join(thread, NULL); /*join the thread*/
    ReadTime(); /*show the user the current time*/
  }
  /*if none of the connections exist them we are going to print the error message below and ask the user for input again*/
  else if(badconnection == true)
  {
    printf("\nHUH? I DON’T UNDERSTAND THAT ROOM. TRY AGAIN.\n\n");
    badconnection = true;
  }
}
/*we close the files that are open at the end*/
  closedir(dr);
  closedir(dirToCheck);
  return 0;
}
