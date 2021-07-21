/*
Author: Calvin Todd
Class: CS 344
Assignment: Assignment 3 - processInput
*/

//Imports
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "smallsh.h"

//Constants
#define MAXARGS 513
#define MAXSIZE 2049

//Function Declarations

char ** processInput (char *input) {
    //Declare Variables
    char **argArray = malloc(MAXARGS * (sizeof(char *) + 1));
    char *arg;
    char delim[] = " ";
    int i = 0;

    //Check to see if input is a comment
    if (input[0] == '#')
    {
        arg = input;
        argArray[0] = arg;
        return argArray;
    }

    //Split up the input in to a workable array
    arg = (char *) malloc(MAXSIZE + 1);
    
    //Verify malloc
    if (!arg)
    {
        puts("ERROR: Error allocationg memory");
        fflush(stdout);
        exit(1);
    }

    arg = strtok(input, delim);
    puts(arg);
    argArray[i] = arg;
    puts(argArray[i]);
    i++;

    while ( arg )
    {
        arg = (char *) malloc(MAXSIZE + 1);
        //Verify malloc
        if (!arg)
        {
            puts("ERROR: Error allocationg memory");
            fflush(stdout);
            exit(1);
        }

        arg = strtok(NULL, delim);
        puts("LOOP ARG:");
        if (arg)
        {
            puts(arg);
        }

        //If next character is null, break loop

        if ( !arg ) 
        {
            puts("here!");
            break;
        }

        //Add input pointer to pointer array
        argArray[i] = arg;
        puts("LOOP ARRAY: ");
        puts(argArray[i]);
        i++;
    }

    // arg = '\0';
    argArray[i] = arg;
    //Return array of pointers to arguments

    for (i = 0; i < 3; i++)
    {
        puts("FOR LOOP:");
        printf("%d\n", **argArray);
        puts(*argArray + (i * sizeof(char*)));
    }

    return argArray;
}