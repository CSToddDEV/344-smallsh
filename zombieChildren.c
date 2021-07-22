/*
Author: Calvin Todd
Class: CS 344
Assignment: Assignment 3 - smallsh - zombieChildren.c
*/

//Imports
#include "smallsh.h"

//Constants


//Function Declarations

void zombieChildren (void) {
    pid_t childPID = -1;
    int statusCode;
    int exitCode;
    int sigCode;
    char codeArray[50];

    //Loop through any children that have finished execution since last input prompt
    childPID = waitpid(-1, &statusCode, WNOHANG|WUNTRACED);
    while (childPID != -1 && childPID)
    {
        //Handle Signal exits
        if (WIFSIGNALED(statusCode))
        {
            sigCode = WTERMSIG(statusCode);
            fputs("Process [", stdout);
            fflush(stdout);
            myItoa(childPID, codeArray);
            fputs(codeArray, stdout);
            fflush(stdout);
            fputs("] terminated by signal number: ", stdout);
            fflush(stdout);
            myItoa(sigCode, codeArray);
            fputs(codeArray, stdout);
            fflush(stdout);
        }
        //Get exit status
        else if (WIFEXITED(statusCode))
        {
            exitCode = WEXITSTATUS(statusCode);
            //Print message with pid and exit number
            fputs("Child Process with PID [", stdout);
            fflush(stdout);
            myItoa(childPID, codeArray);
            fputs(codeArray, stdout);
            fflush(stdout);
            fputs("] exited with exit code: ", stdout);
            fflush(stdout);
            myItoa(exitCode, codeArray);
            fputs(codeArray, stdout);
            fflush(stdout);
        }

        fputs("\n", stdout);
        fflush(stdout);
        childPID = waitpid(-1, &statusCode, WNOHANG);
    }
}