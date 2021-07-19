/*
Author: Calvin Todd
Class: CS 344
Assignment: Assignment 3 - smallsh - myItoa.c
*/

//Imports
#include <stdio.h>

//Constants


//Function Declarations

void myItoa (int pid, char *pPID) {
    //Declare Variables
    int i = 0; //pPid index
    int n; //number to turn in to ascii

    while (pid > 0)
    {
        //Convert int to ASCII
        n = pid % 10;
        n = n + 48;

        //Add to pPID
        pPID[i] = n;


        //Update pid
        pid = pid / 10;

        i++;
    }
    pPID[i] = '\0';
}