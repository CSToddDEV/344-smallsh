/*
Author: Calvin Todd
Class: CS 344
Assignment: Assignment 3 - smallsh
*/
#define _POSIX_C_SOURCE 200809L

//Imports
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "smallsh.h"

int main (int argc, char *argv[], char * envp[]) {
    //Declare Variables
    char welcome[] = "Welcome to smallsh by Calvin Todd!\n";
    char exit[] = "\nThank you for using smallsh by Calvin Todd!  May the force be with you.";
    char *pWelcome;
    char *pExit;
    struct sigaction SIGINTHandler = {0};

    //Build sig handler structures
    SIGINTHandler.sa_handler = SIG_IGN;
    sigfillset(&SIGINTHandler.sa_mask);
    SIGINTHandler.sa_flags = 0;
    sigaction(SIGINT, &SIGINTHandler, NULL); 

    //Welcome
    pWelcome = welcome;
    puts(pWelcome);
    fflush(stdout);

    //printEnv for debug
    // printEnv(envp);

    //Call smallsh loop
    smallshLoop();

    //Exit
    pExit = exit;
    puts(pExit);
    fflush(stdout);

    return 0;
}