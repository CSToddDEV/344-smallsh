/*
Author: Calvin Todd
Class: CS 344
Assignment: Assignment 3 - smallsh
*/
#define _POSIX_C_SOURCE 200809L

//Imports
#include "smallsh.h"

//Global Variable Flag
volatile sig_atomic_t fgOnly = 0;

int main (int argc, char *argv[], char * envp[]) {
    //Set pgid to PID in case called by shell.  Make smallsh group leader
    setpgid(0, 0);

    //Declare Variables
    char welcome[] = "Welcome to smallsh by Calvin Todd!\n";
    char exit[] = "\nThank you for using smallsh by Calvin Todd!  May the force be with you.";
    char *pWelcome;
    char *pExit;
    struct sigaction SIGINTHandler = {0};
    struct sigaction SIGSTPHandler = {0};
    struct sigaction SIGUSRHandler = {0};

    //Build sig handler structures
    SIGINTHandler.sa_handler = SIG_IGN;
    sigfillset(&SIGINTHandler.sa_mask);
    SIGINTHandler.sa_flags = 0;
    sigaction(SIGINT, &SIGINTHandler, NULL);

    SIGSTPHandler.sa_handler = handleSIGTSTP;
    sigfillset(&SIGSTPHandler.sa_mask);
    SIGSTPHandler.sa_flags = 0;
    sigaction(SIGTSTP, &SIGSTPHandler, NULL);

    SIGUSRHandler.sa_handler = SIG_IGN;
    sigfillset(&SIGUSRHandler.sa_mask);
    SIGUSRHandler.sa_flags = 0;
    sigaction(SIGUSR1, &SIGUSRHandler, NULL);

    //Welcome
    pWelcome = welcome;
    puts(pWelcome);
    fflush(stdout);

    //Call smallsh loop
    smallshLoop();

    //Exit
    pExit = exit;
    puts(pExit);
    fflush(stdout);

    return 0;
}