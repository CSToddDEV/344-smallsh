/*
Author: Calvin Todd
Class: CS 344
Assignment: Assignment 3 - smallsh - variableExpansion.c
*/

//Imports
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

//Constants
#define BUFFLEN 2049

//Function Declarations
void myItoa (int pid, char *pPID);

char * variableExpansion (char *input) {
    //Declare Variables
    char *expandedInput = malloc(sizeof(char) * BUFFLEN);
    int i = 0; //Unexpanded string index
    int j = 0; //Expanded string index
    int k = 0; //PID string index
    int pid = getpid();
    char pPID[50];

    myItoa(pid, pPID); //Turn pid in to a character array.

    //If comment return input
    if (input[0] == '#')
    {
        return input;
    }
    else
    {
        while (input[i])
        {
            //Check for expansion variable
            if ((input[i] == '$') && (input[i + 1] == '$'))
            {
                k = 0;
                //Copy PID in to variable
                while (pPID[k])
                {
                    expandedInput[j] = pPID[k];
                    k++;
                    j++;
                }

                i = i + 2;
            }
            else
            {
                //Copy non-variable character
                expandedInput[j] = input[i];
                i++;
                j++;
            }
        }
        expandedInput[j] = '\0';
    
        //Free old input buffer
        free(input);
        return expandedInput;
    }
    
}