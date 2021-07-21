/*
Author: Calvin Todd
Class: CS 344
Assignment: Assignment 3 - executeArgs
*/
#define _POSIX_C_SOURCE 200809L

//Imports
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include "smallsh.h"

//Constants
#define BUFFLEN 2049
#define DELIM " "

bool executeArgs (char *input, int *pStatusCode) {
    //Declare Variables
    char* program;
    char* arg;
    char* fileInput;
    char* fileOutput;
    char* devNull = "/dev/null";
    char cPID[25];
    char* args[512];
    char ampString[] = "&";
    int fdInput = -1;
    int fdOutput = -1;
    int childStatus;
    int i = 0;
    int statusID;
    pid_t spawnPID;
    bool runShell = true;
    bool background = false;
    bool inputSet = false;
    bool outputSet = false;
    struct sigaction SIGINTHandlerOG;

    //Build sig handler structures
    SIGINTHandlerOG.sa_handler = SIG_DFL;
    sigfillset(&SIGINTHandlerOG.sa_mask);
    SIGINTHandlerOG.sa_flags = 0;

    //Split input stringin to args
    args[i] = strtok(input, " ");

    while (args[i])
    {
        i++;
        arg = strtok(NULL, " ");

        //Break loop if Null
        if (!arg)
        {
            args[i] = arg;
            break;
        }

        //Check for redirection/background operators
        //Handle Input
        if (strcmp(arg, "<") == 0)
        {
            //Get file to read read for input
            fileInput = strtok(NULL, " ");
            inputSet = true;
            i--;
            
        }

        //Handle Output
        else if (strcmp(arg, ">") == 0)
        {
            //Get file to write for output
            fileOutput = strtok(NULL, " ");
            outputSet = true;
            i--;
        }

        //Handle Background
        else if (strcmp(arg, "&") == 0)
        {
            //Ensure & was the last arg
            arg = strtok(NULL, " ");
            if (!arg)
            {
                background = true;
                i--;
            }
            else
            {
                //If not last char, update arg array
                args[i] = ampString;
                i++;
                args[i] = arg;
            }
            
        }

        //Else is arg, handle normal
        else
        {
            args[i] = arg;
        }
    }

    program = args[0];

    if (!program)
    {
        //If blank line return
        free(input);
        return runShell;
    }

    //Based on the first arg passed choose program to run  
    if (strcmp(program, "exit") == 0)
    {
        runShell = exitShell();
    }

    else if (strcmp(program, "cd") == 0)
    {
        cdShell(args);
    }

    else if (strcmp(program, "status") == 0)
    {
        status(pStatusCode);
    }

    else if (program[0] == '#')
    {
        //Pass since a comment
        ;
    }

    else
    {
        //Fork and run execvp
        spawnPID = fork();

        //Switch statement to handle fork
        switch(spawnPID) {
            case -1:
                perror("Error in fork(): ");
                free(input);
                exit(1);
                break;

            case 0:
                //Child Proccess
                //Change sigaction
                if (!background)
                {
                    sigaction(SIGINT, &SIGINTHandlerOG, NULL);
                }
                
                //If input was not set in args
                if (!inputSet && background)
                {
                    //Open /dev/null to read read for input
                    fdInput = open(devNull, O_RDONLY);
                        
                    //Check fd to make sure file was opened
                    if (fdInput < 0)
                    {
                        fputs("ERROR: ", stderr);
                        fputs(fileInput, stderr);
                        fputs(" was not a readable file.\n", stderr);
                        *pStatusCode = 1;
                        return runShell;
                    }
            
                    //Redirect stdin and check if succesful
                    if (dup2(fdInput, 0) < 0)
                    {
                        fputs("ERROR: Unable to duplicate file descriptor in dup2()\n", stderr);
                        *pStatusCode = 1;
                        return runShell;
                    }
                }
                //Set input
                else if (inputSet)
                {
                    fdInput = open(fileInput, O_RDONLY);
            
                    //Check fd to make sure file was opened
                    if (fdInput < 0)
                    {
                        fputs("ERROR: ", stderr);
                        fputs(fileInput, stderr);
                        fputs(" was not a readable file.\n", stderr);
                        *pStatusCode = 1;
                        return runShell;
                    }
                        
                    //Redirect stdin and check if succesful
                    if (dup2(fdInput, 0) < 0)
                    {
                        fputs("ERROR: Unable to duplicate file descriptor in dup2()\n", stderr);
                        *pStatusCode = 1;
                        return runShell;
                    }
                }

                //If output was not set in args
                if (!outputSet && background)
                {
                    //Open /dev/null to read read for input
                    fdOutput = open(devNull, O_CREAT | O_WRONLY | O_TRUNC, 0755);
                        
                    //Check fd to make sure file was opened
                    if (fdOutput < 0)
                    {
                        fputs("ERROR: ", stderr);
                        fputs(fileOutput, stderr);
                        fputs(" was not a valid output file.\n", stderr);
                        *pStatusCode = 1;
                        return runShell;
                    }
            
                    //Redirect stdin and check if succesful
                    if (dup2(fdOutput, 1) < 0)
                    {
                        fputs("ERROR: Unable to duplicate file descriptor in dup2()\n", stderr);
                        *pStatusCode = 1;
                        return runShell;
                    }
                }
                //Set output
                else if (outputSet)
                {
                    fdOutput = open(fileOutput, O_CREAT | O_WRONLY | O_TRUNC, 0755);
            
                    //Check fd to make sure file was opened
                    if (fdOutput < 0)
                    {
                        fputs("ERROR: ", stderr);
                        fputs(fileOutput, stderr);
                        fputs(" was not a valid output file.\n", stderr);
                        *pStatusCode = 1;
                        return runShell;
                    }
                        
                    //Redirect stdin and check if succesful
                    if (dup2(fdOutput, 1) < 0)
                    {
                        fputs("ERROR: Unable to duplicate file descriptor in dup2()\n", stderr);
                        *pStatusCode = 1;
                        return runShell;
                    }
                }
                
                //Child Proccess Run Command from path
                execvp(program, args);

                //Error catching if execvp doesn't find command
                puts("ERROR: Command not found");
                free(input);
                exit(1);
                break;

            default:
                //Parent Proccess

                //Run the program in the background if the background flag is set
                if (background)
                {
                    //Get PID and print to error output (since stdout might be different)
                    waitpid(spawnPID, &childStatus, WNOHANG);
                    fputs("Child process ", stderr);
                    fflush(stdout);
                    fputs(program, stderr);
                    fflush(stdout);
                    fputs(" began in the background with PID: ", stderr);
                    fflush(stdout);
                    myItoa(spawnPID, cPID);
                    fputs(cPID, stderr);
                    fflush(stdout);
                    fputs("\n", stderr);
                    fflush(stdout);

                }

                //Else Run the Porgram in the foreground
                else
                {
                    //Wait for child proccess to finish, update status code
                    waitpid(spawnPID, &childStatus, 0);
                
                    //Set exit process
                    if (WIFEXITED(childStatus))
                    {
                        statusID = WEXITSTATUS(childStatus);
                        pStatusCode = &statusID;
                    }

                    //Handle Signal exits
                    if (WIFSIGNALED(childStatus))
                    {
                        statusID = WTERMSIG(childStatus);
                        fputs("\nterminated by signal number: ", stdout);
                        fflush(stdout);
                        myItoa(statusID, cPID);
                        fputs(cPID, stdout);
                        fflush(stdout);
                        fputs("\n", stdout);
                        fflush(stdout);
                    }
                }
                
        }
    }

    //Close input file if open
    if (fdInput > 0)
    {
        close(fdInput);
    }

    //Close output file if open
    if (fdOutput > 0)
    {
        close(fdOutput);
    }


    free(input);

    return runShell;
}