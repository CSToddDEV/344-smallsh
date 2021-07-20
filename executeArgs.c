/*
Author: Calvin Todd
Class: CS 344
Assignment: Assignment 3 - executeArgs
*/

//Imports
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

//Constants
#define BUFFLEN 2049
#define DELIM " "

//Function Declarations
bool exitShell ();
void cdShell ();
void status (int * statusCode);

bool executeArgs (char *input, int* pStatusCode) {
    //Declare Variables
    char *program;
    char* arg;
    char* file;
    char* devNull = "/dev/null";
    char *args[512];
    char ampString[] = "&";
    int fdInput;
    int fdOutput;
    int childStatus;
    int i = 0;
    pid_t spawnPID;
    bool runShell = true;
    bool background = false;
    bool inputSet = false;
    bool outputSet = false;

    //Split input stringin to args
    args[i] = strtok(input, " ");

    while (args[i])
    {
        i++;
        arg = strtok(NULL, " ");

        //Break loop if Null
        if (!arg)
        {
            break;
        }

        //Check for redirection/background operators
        //Handle Input
        if (strcmp(arg, "<") == 0)
        {
            //Open file to read read for input
            file = strtok(NULL, " ");
            fdInput = open(file, O_RDONLY);
            
            //Check fd to make sure file was opened
            if (fdInput < 0)
            {
                fputs("ERROR: ", stderr);
                fputs(file, stderr);
                fputs(" was not a readable file.\n", stderr);
                *pStatusCode = 1;
                return runShell;
            }
            
            //Redirect stdin and check if succesful
            if (dup2(fdInput, stdin) < 0)
            {
                fputs("ERROR: Unable to duplicate file descriptor in dup2()\n", stderr);
                *pStatusCode = 1;
                return runShell;
            }
            inputSet = true;
            
        }

        //Handle Output
        else if (strcmp(arg, ">") == 0)
        {
            //Open file to read read for input
            file = strtok(NULL, " ");
            fdOutput = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0755);
            
            //Check fd to make sure file was opened
            if (fdOutput < 0)
            {
                fputs("ERROR: ", stderr);
                fputs(file, stderr);
                fputs(" was not a valid output file.\n", stderr);
                *pStatusCode = 1;
                return runShell;
            }
            
            //Redirect stdin and check if succesful
            if (dup2(fdOutput, stdout) < 0)
            {
                fputs("ERROR: Unable to duplicate file descriptor in dup2()\n", stderr);
                *pStatusCode = 1;
                return runShell;
            }
            outputSet = true;
        }

        //Handle Background
        else if (strcmp(arg, "&") == 0)
        {
            //Ensure & was the last arg
            arg = strtok(NULL, " ");
            if (!arg)
            {
                background = true;
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

                //If inputs are not set, set them to /dev/null
                if (background)
                {
                    //If input was not set in args
                    if (!setInput)
                    {
                        //Open /dev/null to read read for input
                        fdInput = open(devNull, O_RDONLY);
                        
                        //Check fd to make sure file was opened
                        if (fdInput < 0)
                        {
                            fputs("ERROR: ", stderr);
                            fputs(file, stderr);
                            fputs(" was not a readable file.\n", stderr);
                            *pStatusCode = 1;
                            return runShell;
                        }
            
                        //Redirect stdin and check if succesful
                        if (dup2(fdInput, stdin) < 0)
                        {
                            fputs("ERROR: Unable to duplicate file descriptor in dup2()\n", stderr);
                            *pStatusCode = 1;
                            return runShell;
                        }
                        inputSet = true;
                    }

                    //If output was not set in args
                    if (!setOutput)
                    {
                        //Open /dev/null to read read for input
                        fdOutput = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0755);
                        
                        //Check fd to make sure file was opened
                        if (fdOutput < 0)
                        {
                            fputs("ERROR: ", stderr);
                            fputs(file, stderr);
                            fputs(" was not a valid output file.\n", stderr);
                            *pStatusCode = 1;
                            return runShell;
                        }
            
                        //Redirect stdin and check if succesful
                        if (dup2(fdOutput, stdout) < 0)
                        {
                            fputs("ERROR: Unable to duplicate file descriptor in dup2()\n", stderr);
                            *pStatusCode = 1;
                            return runShell;
                        }
                        inputSet = true;
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
                    continue;
                }

                //Else Run the Porgram in the foreground
                else
                {
                    //Wait for child proccess to finish, update status code
                    waitpid(spawnPID, &childStatus, 0);
                
                    //Set exit process
                    if (WIFEXITED(childStatus))
                    {
                        *pStatusCode = WEXITSTATUS(childStatus);
                    }
                }
                
        }
    }

    //Close input file if open
    if (fdInput)
    {
        close(fdInput);
    }

    //Close output file if open
    if (fdOutput)
    {
        close(fdOutput);
    }


    free(input);

    return runShell;
}