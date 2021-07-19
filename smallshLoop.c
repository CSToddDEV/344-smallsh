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
char ** processInput (char *input);
bool executeArgs (char **args, int *pStatusCode);
char* variableExpansion (char *input);

void smallshLoop (void) {
    //Declare Variables
    bool runLoop = true;
    char *input;
    char **args;
    char prompt = ':';
    int statusCode = 0;
    int *pStatusCode = &statusCode;
    int i;

    while (runLoop)
    {
        //Display Cursor set i
        putchar(prompt);
        fflush(stdout);
        i = 0;

        //Get Input
        input = getInput();

        //Variable Expansion
        input = variableExpansion(input);

        //Process Inputs
        args = processInput(input);

        //Process arguments
        runLoop = executeArgs(args, pStatusCode);
        
        //Free array of array pointers
        while (args[i])
        {
            printf("HERE ");
            puts(args[i]);
            // free(args[i]);
            i++;
        }

        //Free pointer to array of pointers
        // free(args);
    }
}