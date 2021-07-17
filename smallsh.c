/*
Author: Calvin Todd
Class: CS 344
Assignment: Assignment 3 - smallsh
*/

//Imports
#include <stdio.h>

//Constants


//Function Declarations
void smallshLoop (void);
void printEnv (char * envp[]);

int main (int argc, char *argv[], char * envp[]) {
    //Declare Variables
    char welcome[] = "Welcome to smallsh by Calvin Todd! Please type --help for help!\n";
    char exit[] = "\nThank you for using smallsh by Calvin Todd!  May the force be with you.";
    char *pWelcome;
    char *pExit;

    //Welcome
    pWelcome = welcome;
    puts(pWelcome);
    fflush(stdout);

    printEnv(envp);

    //Call smallsh loop
    smallshLoop();

    //Exit
    pExit = exit;
    puts(pExit);
    fflush(stdout);

    return 0;
}