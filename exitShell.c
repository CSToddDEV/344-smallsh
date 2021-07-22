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
    struct sigaction SIGTERMHandler = {0};

    //Build sig handler structures - Ignore SIGTERM for parent process so it exits normally
    SIGTERMHandler.sa_handler = SIG_IGN;
    sigfillset(&SIGTERMHandler.sa_mask);
    SIGTERMHandler.sa_flags = 0;
    sigaction(SIGTERM, &SIGTERMHandler, NULL);

    //Kill all open children
    kill(0, 15);

    //Return flase for loop run variable so main() exits normally
    return false;
}