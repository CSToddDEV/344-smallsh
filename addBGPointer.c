/*
Author: Calvin Todd
Class: CS 344
Assignment: Assignment 3 - smallsh - addBGPointer.c
*/

//Imports
#include "smallsh.h"

//Constants


//Function Declarations

void addBGPointer (int bgProcessCount, struct BGProcess **pBGProcessArray, struct BGProcess *pBGProcess) {
//Declare variables
i = 0;

//Check to see if array needs to be realloc
while (pBGProcessArray[i * sizeof(pBGProcess)])
{
    i++;    
}

//Realloc array
if ((i * sizeof(pBGProcess)) >= sizeof(pBGProcessArray))
{
    pBGProcessArray = realloc(pBGProcessArray, ((i + 1) * sizeof(pBGProcess)));
}

//Reset i and find next open pointer spot
while (pBGProcessArray[i * sizeof(pBGProcess)])
{
    i++;    
}

pBGProcessArray[i * sizeof(pBGProcess)] = pBGProcess;

}