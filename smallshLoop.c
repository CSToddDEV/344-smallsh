/*
Author: Calvin Todd
Class: CS 344
Assignment: Assignment 3 - smallsh
*/

//Imports
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//Constants

//Function Declarations
char* getInput ();
bool executeArgs (char *input, int *pStatusCode);
char* variableExpansion (char *input);

void smallshLoop (void) {
    //Declare Variables
    bool runLoop = true;
    char *input;
    char prompt = ':';
    int statusCode = 0;
    int *pStatusCode = &statusCode;

    while (runLoop)
    {
        //Display Cursor set i
        putchar(prompt);
        fflush(stdout);

        //Get Input
        input = getInput();

        //Variable Expansion
        input = variableExpansion(input);

        //Process arguments
        runLoop = executeArgs(input, pStatusCode);
        
    }
}