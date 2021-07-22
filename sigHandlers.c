/*
Author: Calvin Todd
Class: CS 344
Assignment: Assignment 3 - smallsh - sigHandlers.c
*/

//Imports
#include "smallsh.h"

//Constants

//Function Declarations
void handleSIGTSTP (int sig) {
    if (fgOnly == 0)
    {
        puts("\nEntering Foreground Only Mode (& will be ignored)");
        fgOnly = 1;
    }
    else
    {
        puts("\nExiting Foreground Only Mode (& funcitonality restored)");
        fgOnly = 0;
    }
}