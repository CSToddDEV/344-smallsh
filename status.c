/*
Author: Calvin Todd
Class: CS 344
Assignment: Assignment 3 - smallsh - status.c
*/

//Imports
#include <stdio.h>

//Constants


//Function Declarations

void status (int * statusCode) {
    //Declare Variables
    int code = 48 + *statusCode;
    char *codeString;


    codeString = (char *) &code;
    fputs( codeString, stdout);
    fputs(": Was the exit code/terminating signal of the most recent forecground process", stdout);
    fflush(stdout);

}