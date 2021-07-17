/*
Author: Calvin Todd
Class: CS 344
Assignment: Assignment 3 - processInput
*/

//Imports
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Constants
#define BUFFLEN 2049
#define DELIM " "

//Function Declarations

char** processInput (char *input) {
    //Declare Variables
    char **argArray = malloc(sizeof(char*) * BUFFLEN);
    char *arg;
    int i = 0;

    //Verify malloc
    if (!argArray)
    {
        puts("ERROR: Error allocationg memory");
        fflush(stdout);
        exit(1);
    }

    //Split up the input in to a workable array
    arg = strtok(input, DELIM);
    argArray[i] = arg;
    i++;

    while ( arg )
    {
        arg = strtok(NULL, DELIM);
        //If next character is null, break loop
        if ( arg == NULL ) 
        {
            break;
        }
        //Add input pointer to pointer array
        argArray[i] = arg;
        i++;
    }

    //Return array of pointers to arguments
    return argArray;
}