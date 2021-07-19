/*
Author: Calvin Todd
Class: CS 344
Assignment: Assignment 3 - smallsh -  cdShell.c
*/

//Imports
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

//Constants
#define MAXPATH 1024

//Function Declarations

void cdShell (char **args) {
    //Declare variables
    char *dir = args[1];
    char err[] = "smallsh: cd: ";
    char err2[] = ": No such file or directory";
    char err3[MAXPATH];

    if (!dir)
    {
        //If no second argument, change to home
        chdir(getenv("HOME"));
    }
    else if (chdir(dir) == 0)
    {

    }
    else
    {
        //Print error
        strncat(err3, err, sizeof(err3));
        strncat(err3, dir, sizeof(err3));
        strncat(err3, err2, sizeof(err3));
        puts(err3);
        fflush(stdout);
    }
}