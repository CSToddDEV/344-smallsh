/*
Author: Calvin Todd
Class: CS 344
Assignment: Assignment 3 - smallsh -exitShell.c
*/
#define _POSIX_C_SOURCE 200809L

//Imports
#include "smallsh.h"



bool exitShell () {
    //Declare variables

    //Kill all open children
    kill(0, 10);

    //Return flase for loop run variable so main() exits normally
    return false;
}