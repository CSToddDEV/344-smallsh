/*
Author: Calvin Todd
Class: CS 344
Assignment: Assignment 3 - smallsh
*/

//Imports
#include "smallsh.h"

void smallshLoop (void) {
    //Declare Variables
    bool runLoop = true;
    char *input;
    char* exInput;
    char prompt = ':';
    int statusCode = 0;

    while (runLoop)
    {
        //Check pBGProcessArray for recently closed Background Processes, and free pointers
        zombieChildren();

        //Display Cursor set i
        putchar(prompt);
        fflush(stdout);

        //Get Input
        input = getInput();

        //Variable Expansion
        exInput = variableExpansion(input);

        //Process arguments
        runLoop = executeArgs(exInput, &statusCode);

        free(input);
        free(exInput);
    }
}