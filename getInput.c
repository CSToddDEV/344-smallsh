/*
Author: Calvin Todd
Class: CS 344
Assignment: Assignment 3 - getInput
*/

//Imports
#include "smallsh.h"

//Constants
#define BUFFLEN 2049

char* getInput () {
    //Declare Variables
    char *buffer = malloc(BUFFLEN);
    int i = 0;

    //Verify malloc
    if (!buffer)
    {
        puts("ERROR: Error allocationg memory");
        fflush(stdout);
        exit(1);
    }

    //Get Input
    do {
        //Get character from input
        buffer[i] = getchar();
        i++;
    } while ((buffer[i-1] != EOF) && (buffer[i-1] != '\n'));
    
    //Add Null terminator
    buffer[i - 1] = ' ';
    buffer[i] = '\0';

    //return input
    return buffer;
}