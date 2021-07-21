/*
Author: Calvin Todd
Class: CS 344
Assignment: Assignment 3 - smallsh - zombieChildren.c
*/

//Imports
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include "smallsh.h"

//Constants


//Function Declarations

void zombieChildren (void) {
    pid_t childPID = -1;
    int statusCode;
    int exitCode;
    char cPID[50];
    char exitCodeArray[50];

    //Loop through any children that have finished execution since last input prompt
    childPID = waitpid(-1, &statusCode, WNOHANG);
    while (childPID != -1 && childPID)
    {
        //Get exit status
        if (WIFEXITED(statusCode))
        {
            exitCode = WEXITSTATUS(statusCode);
        }
        

        //Print message with pid and exit number
        fputs("Child Process with PID [", stdout);
        fflush(stdout);
        myItoa(childPID, cPID);
        fputs(cPID, stdout);
        fflush(stdout);
        fputs("] exited with exit code: ", stdout);
        fflush(stdout);
        myItoa(exitCode, exitCodeArray);
        fputs(exitCodeArray, stdout);
        fflush(stdout);
        fputs("\n", stdout);
        fflush(stdout);
        childPID = waitpid(-1, &statusCode, WNOHANG);
    }
}