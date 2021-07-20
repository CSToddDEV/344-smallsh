#! /bin/bash

#Author: Calvin Todd
#Class: CS 344
#Assignment: Assignemnt 3 Compile Script
#Description: This script compiles my promgrams in to an executable.

clear

echo "Compiling has begun..."
echo

echo "Compiling smallsh.c ----> smallsh"
gcc smallsh.c smallshLoop.c getInput.c executeArgs.c exitShell.c printEnv.c cdShell.c variableExpansion.c myItoa.c status.c -std=c11 -Wall -Werror -g3 -o smallsh -lm
echo

echo "Compiling Complete!"