/*
 * Runner Class for the Shell Project 
 * @author: Zachary Semanco, Daniel Holmgren
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "tokenizer.h"      //Header file allowing us to use the tokenizer file and functions
#include "command.h"        //Header file for the command struct

// The max amount of characters to be read
#define COMMAND_SIZE 60

// The list of internal commands and its size
int command_list_size = 6;
char *command_list[] = {"cd", "setenv", "unsetenv", "pwd", "exit", "accnt"};

// Funciton definitions for functions later in the file
int checkInternalCommand(command_t *cmd);
void execInternal(int command_num, command_t *cmd);


int main (int argc, char **argv[])
{
    while(1){
        // User prompt when starting the shell, stored in PS1
        const char *prompt = "> Welcome to the Shippensburg University Shell (SUSH)! Please enter a command\n";
        printf(">");
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

        // instance of command_t struct
        command_t cmd;
        memset(&cmd, 0, sizeof(cmd));
        
        // The 'command' portion of the entered string is assumed to be the first part the user enters
        cmd.cmd = strdup(tkn.tokens[0]);
        
        // Defines the number of arguments for our command
        cmd.argc = tkn.num_tokens - 1;
        
        // Place the arguments into their array
        int i = 1;
        while(tkn.tokens[i] != NULL)
        {
            cmd.args[i-1] = strdup(tkn.tokens[i]);
            i++;
        }

        // Checks to see if the command the user entered is an internal command
        command_t *cmd_ptr = &cmd;
        if(checkInternalCommand(cmd_ptr)){
            //should run the code from the if()
        }
        else {
            parseAndRun(cmd.cmd, cmd.args, cmd.argc);
        }
    }    
}

// Checks to see if the command is internal
// If so, execute it
int checkInternalCommand(command_t *cmd)
{
    for(int i = 0; i < command_list_size; i++)
    {
        if (strcmp(command_list[i], cmd->cmd) == 0)
        {
            execInternal(i, cmd);
            return 1;
        }
    }
    return 0;
}

// Finds the proper internal command to execute
void execInternal(int command_num, command_t *cmd)
{ 
    switch(command_num) 
    {
        case 0:
            //cd
            printf("User entered %s\n", command_list[command_num]);
            if(chdir(cmd->args[0]) == 0){
                printf("Changed directory to: %s\n", getenv("PWD"));
            }else printf("Error: Failed to change directory\n");
            break;
        case 1:
            //setenv
            if((setenv(cmd->args[0], cmd->args[1], 1)) == 0){
                printf("Set env var %s to %s\n", cmd->args[0], cmd->args[1]);
            } else printf("Error: Failed to change env var\n");
            break;
        case 2:
            //unsetenv
            if((unsetenv(cmd->args[0])) == 0){
                printf("Unset env var %s\n", cmd->args[0]);
            } else printf("Failed to unset env var\n");
            break;
        case 3:
            //pwd
            printf("Current working directory: %s\n", getenv("PWD"));
            break;
        case 4:
            //exit
            printf("Thanks for using the SUSH, goodbye\n");
            exit(0);
            break;
        case 5:
            //accnt
            printf("User entered %s\n", command_list[command_num]);
            break;
        default: 
            printf("Not an internal command\n");
    }
}