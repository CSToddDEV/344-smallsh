/*
Author: Calvin Todd
Class: CS 344
Assignment: Assignment 3 - smallsh - myItoa.c
*/

//Imports
#include <stdio.h>
#include "smallsh.h"

void myItoa (int pid, char *pPID) {
    //Declare Variables
    int i = 0; //pPid index
    int n = 0; //number to turn in to ascii

    if (pid >= 0)
    {
        do
        {
            //Convert int to ASCII
            n = pid % 10;
            n = n + 48;

            //Add to pPID
            pPID[i] = n;


            //Update pid
            pid = pid / 10;

            i++;
        } while (pid > 0);
    }
    pPID[i] = '\0';
}