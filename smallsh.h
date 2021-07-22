/*
Author: Calvin Todd
Class: CS 344
Assignment: Assignment 3 - smallsh - smallsh.h
*/
#define _POSIX_C_SOURCE 200809L

//Include
#include <stdbool.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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
void handleSIGTSTP (int sig);
void sigExit (int sid);

//Global Variable Declaration
extern volatile sig_atomic_t fgOnly;
