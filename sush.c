/*
 * Runner Class for the Shell Project 
 * @author: Zachary Semanco, Daniel Holmgren
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"      //Header file allowing us to use the tokenizer file and functions
#include "command.h"

// The max amount of characters to be read
#define COMMAND_SIZE 60

// The list of internal commands and its size
int command_list_size = 7;
char *command_list[] = {"cd", "setenv", "unsetenv", "pwd", "exit", "accnt", "\0"};

// Funciton definitions for functions later in the file
void checkInternalCommand(char *cmd);
void execInternal(int command_num);


int main (int argc, char **argv[])
{
    // User prompt when starting the shell, stored in PS1
    const char *prompt = "Welcome to the Shippensburg University Shell (SUSH)! Please enter a command\n";
    setenv("PS1", prompt, 0);
    printf("%s", getenv("PS1"));


    char command[COMMAND_SIZE];

    // gets the command that the user enters
    fgets(command, COMMAND_SIZE, stdin);
    
    // instance of tokenizer_t struct
    tokenizer_t tkn;
    memset(&tkn, 0, sizeof(tkn));

    // tokenize the string
    tkn = tokenize(command); 
    

    for(int i = 0; i < tkn.num_tokens; i++)
    {
        printf("tkn.tokens[%d] = %s\n", i, tkn.tokens[i]);
    }

    // instance of command_t struct
    command_t cmd;
    memset(&cmd, 0, sizeof(cmd));
    
    // The 'command' portion of the entered string is assumed to be the first part the user enters
    cmd.cmd = strdup(tkn.tokens[0]);

    // Checks to see if the command the user entered is an internal command
    checkInternalCommand(cmd.cmd);

    // Defines the number of arguments for our command
    cmd.argc = tkn.num_tokens-1;
    
    // Place the arguments into their array
    for(int i = 0; i < tkn.num_tokens; i++)
    {
        printf("tkn.tokens[%d] = %s\n", i, tkn.tokens[i]);
        cmd.args[i-1] = strdup(tkn.tokens[i]);
        printf("cmd.args[%d] = %s\n", i, cmd.args[i]);
    }
}

// Checks to see if the command is internal
// If so, execute it
void checkInternalCommand(char *cmd)
{
    // printf("cmd = %s\n", cmd);

    for(int i = 0; i < command_list_size - 1; i++)
    {
        // printf("Trying to compare %s and %s\n", command_list[i], cmd);
        if (strcmp(command_list[i], cmd) == 0)
        {
            execInternal(i);
        }
    }
}

// Finds the proper internal command to execute
void execInternal(int command_num)
{  
    printf("command_num = %d\n", command_num);
    switch(command_num) 
    {
        case 0:
            printf("User entered %s\n", command_list[command_num]);
            break;
        case 1:
            printf("User entered %s\n", command_list[command_num]);
            break;
        case 2:
            printf("User entered %s\n", command_list[command_num]);
            break;
        case 3:
            printf("User entered %s\n", command_list[command_num]);
            break;
        case 4:
            printf("User entered %s\n", command_list[command_num]);
            break;
        case 5:
            printf("User entered %s\n", command_list[command_num]);
            break;
        default: 
            printf("Not an internal command\n");
    }
}