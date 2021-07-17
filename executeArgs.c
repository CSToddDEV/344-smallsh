/*
Author: Calvin Todd
Class: CS 344
Assignment: Assignment 3 - executeArgs
*/

//Imports
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Constants
#define BUFFLEN 2049
#define DELIM " "

//Function Declarations

bool executeArgs (char **args) {
    //Declare Variables
    bool runShell = true;
    char *program = args[0];
    char returnMessage[50];
    int i = 0;

    //Based on the first arg passed choose program to run  
    fflush(stdout);

    if (strcmp(program, "exit") == 0)
    {
        strcpy(returnMessage, "You hit exit");
        runShell = false;
    }

    else if (strcmp(program, "cd") == 0)
    {
        strcpy(returnMessage, "You hit cd");
    }

    else if (strcmp(program, "status") == 0)
    {
        strcpy(returnMessage, "You hit status");
    }

    else
    {
        strcpy(returnMessage, "You hit other!");
    }

    puts(returnMessage);
    fflush(stdout);
    return runShell;
}