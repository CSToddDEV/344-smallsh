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
bool exitShell ();
void cdShell ();
void status (int * statusCode);

bool executeArgs (char **args, int* pStatusCode) {
    //Declare Variables
    bool runShell = true;
    char *program = args[0];
    char returnMessage[50];

    //Based on the first arg passed choose program to run  
    if (strcmp(program, "exit") == 0)
    {
        runShell = exitShell();
    }

    else if (strcmp(program, "cd") == 0)
    {
        cdShell(args);
    }

    else if (strcmp(program, "status") == 0)
    {
        status(pStatusCode);
    }

    else if (program[0] == '#')
    {
        //Pass since a comment
        ;
    }

    else
    {
        strcpy(returnMessage, "You hit other!");
    }

    //Error catching, will Remove (gets rid of second blank line)
    puts(returnMessage);

    fflush(stdout);
    return runShell;
}