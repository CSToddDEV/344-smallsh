/*
Author: Calvin Todd
Class: CS 344
Assignment: Assignment 3 - smallsh - smallsh.h
*/

//Include
#include <stdbool.h>

//Function Declarations
bool exitShell ();
void cdShell (char **args);
void status (int * statusCode);
void smallshLoop (void);
void printEnv (char * envp[]);
char* getInput ();
bool executeArgs (char *input, int *pStatusCode);
char* variableExpansion (char *input);
void myItoa (int pid, char *pPID);
void zombieChildren (void);
