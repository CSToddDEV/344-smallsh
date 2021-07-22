/*
Author: Calvin Todd
Class: CS 344
Assignment: Assignment 3 - smallsh - myItoa.c
*/

//Imports
#include "smallsh.h"

void myItoa (int pid, char *pPID) {
    //Declare Variables
    int i = 0; //Reversed Num index
    int n = 0; //number to turn in to ascii
    int j = 0; //pPid index
    int len = 0; //length of string
    char reversedNum[25];

    if (pid >= 0)
    {
        do
        {
            //Convert int to ASCII
            n = pid % 10;
            n = n + 48;

            //Add to pPID
            reversedNum[i] = n;


            //Update pid
            pid = pid / 10;

            i++;
            len++;
        } while (pid > 0);
    }
    reversedNum[i] = '\0';

    //Add reversed string to pPid
    for (i = (len - 1); j < len; j++)
    {
        pPID[j] = reversedNum[i];
        i--;
    }
    pPID[j] = '\0';
}