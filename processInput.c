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
#define MAXARGS 513
#define MAXSIZE 2049
#define DELIM " "

//Function Declarations

char ** processInput (char *input) {
    //Declare Variables
    char **argArray = malloc(MAXARGS * sizeof(char *));
    char *arg;
    int i = 0;

    //Check to see if input is a comment
    if (input[0] == '#')
    {
        arg = input;
        argArray[0] = arg;
        return argArray;
    }

    //Split up the input in to a workable array
    arg = (char *) malloc(MAXSIZE);
    
    //Verify malloc
    if (!arg)
    {
        puts("ERROR: Error allocationg memory");
        fflush(stdout);
        exit(1);
    }

    arg = strtok(input, DELIM);
    argArray[i] = arg;
    i++;

    while ( arg )
    {
        arg = (char *) malloc(MAXSIZE);
        //Verify malloc
        if (!arg)
        {
            puts("ERROR: Error allocationg memory");
            fflush(stdout);
            exit(1);
        }

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

    arg = '\0';
    argArray[i] = arg;
    //Return array of pointers to arguments
    return argArray;
}