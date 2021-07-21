/*
Author: Calvin Todd
Class: CS 344
Assignment: Assignment 3 - smallsh - status.c
*/

//Imports
#include <stdio.h>
#include "smallsh.h"

void status (int * statusCode) {
    //Declare Variables and convert to ASCII
    int code = 48 + *statusCode;
    char *codeString;

    //Display Status and status message
    codeString = (char *) &code;
    fputs( codeString, stdout);
    fputs(": Was the exit code/terminating signal of the most recent foreground process\n", stdout);
    fflush(stdout);

}