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
char** processInput (char *input);
bool executeArgs (char **args);

void smallshLoop (void) {
    //Declare Variables
    bool runLoop = true;
    char *input;
    char **args;
    char prompt = ':';
    char newLine = '\n';

    while (runLoop)
    {
        //Display Cursor
        putchar(prompt);
        fflush(stdout);

        //Get Input
        input = getInput();

        //Process Inputs
        args = processInput(input);

        //Process arguments
        runLoop = executeArgs(args);
        
        free(input);
        free(args);
        putchar(newLine);
        fflush(stdout);
    }
}