/*
Author: Calvin Todd
Class: CS 344
Assignment: Assignment 3 - smallsh -printEnv.c
*/

//Imports
#include <stdio.h>

void printEnv (char * envp[]) {
    //Declare Variables
    int i;

    for (i = 0; envp[i] != NULL; i++)
    {
        printf("\n%s", envp[i]);
    }

}