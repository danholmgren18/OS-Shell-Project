/*
 * Runner Class for the Shell Project 
 * @author: Zachary Semanco, Daniel Holmgren
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "tokenizer.h"      //Header file allowing us to use the tokenizer file and functions
#include "command.h"        //Header file for the command struct

// The max amount of characters to be read
#define COMMAND_SIZE 60

// The list of internal commands and its size
int command_list_size = 6;
char *command_list[] = {"cd", "setenv", "unsetenv", "pwd", "exit", "accnt"};
struct rusage usage;
struct rusage cusage;
struct rusage tusage;

// Funciton definitions for functions later in the file
int checkInternalCommand(command_t *cmd);
void execInternal(int command_num, command_t *cmd);
void sigHandler(int signo);
void processAccountSelf();
void currentTotal();
void grandTotal();
void printRUSAGE(struct rusage usage);

void handle_command(const char *line)
{
     if(line == NULL){
            exit(0);
        }

        // instance of tokenizer_t struct
        tokenizer_t tkn;
        memset(&tkn, 0, sizeof(tkn));

        // tokenize the string
        tkn = tokenize(line); 

        // instance of command_t struct
        command_t cmd; 
        memset(&cmd, 0, sizeof(cmd));
        
        // The 'command' portion of the entered string is assumed to be the first part the user enters
        cmd.cmd = strdup(tkn.tokens[0]);
        
        // Defines the number of arguments for our command
        cmd.argc = tkn.num_tokens - 1;

        // Finds the position of the redirect
        if(tkn.redirect_found != 0) 
        {
            int j = 0;
            while(tkn.tokens[j] != NULL)
            {
                //get the position of the redirect
                if(!strcmp(tkn.tokens[j], ">")) {
                    cmd.contains_redirect = 1;
                    cmd.redirect_pos = j + 1; 
                    cmd.out_name = strdup(tkn.tokens[j + 1]);
                    cmd.redirect_type = OUT;
                } else if (!strcmp(tkn.tokens[j], "<")) {
                    cmd.contains_redirect = 1;
                    cmd.redirect_pos = j + 1;
                    cmd.in_name = strdup(tkn.tokens[j + 1]);
                    cmd.redirect_type = IN;
                } else if (!strcmp(tkn.tokens[j], ">>")) {
                    cmd.contains_redirect = 1;
                    cmd.redirect_pos = j + 1;
                    cmd.out_name = strdup(tkn.tokens[j + 1]);
                    cmd.redirect_type = APPEND;
                } else if (!strcmp(tkn.tokens[j], "|")) {
                    cmd.contains_redirect = 1;
                    cmd.redirect_pos = j + 1;
                    cmd.out_name = strdup(tkn.tokens[j + 1]);
                    cmd.redirect_type = PIPE;
                }
                j++;
            }
        }
        
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
            parseAndRun(cmd_ptr);
        }  
}
int main (int argc, char **argv[])
{   
    signal(SIGINT, SIG_IGN);
    signal(SIGUSR1, sigHandler);
    signal(SIGUSR2, sigHandler);


    // FILE fp = *fopen(".sushrc","r");
    // while (fgets(command,1023,fp)) {
    //     handle_command(command);
    // }

    while(1){
        // User prompt when starting the shell, stored in PS1
        const char *prompt = "~ Welcome to the Shippensburg University Shell (SUSH)! Please enter a command\n";

        setenv("PS1", prompt, 0);
        printf("%s", getenv("PS1"));
        printf("~ ");


        char command[COMMAND_SIZE];

        // gets the command that the user enters
        char *line = fgets(command, COMMAND_SIZE, stdin);
        handle_command(command);
       
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
            printf("~ User entered %s\n", command_list[command_num]);
            if(chdir(cmd->args[0]) == 0){
                //changed directory
            }else printf("Error: Failed to change directory\n");
            break;
        case 1:
            //setenv
            if((setenv(cmd->args[0], cmd->args[1], 1)) == 0){
                printf("~ Set env var %s to %s\n", cmd->args[0], cmd->args[1]);
            } else printf("~ Error: Failed to change env var\n");
            break;
        case 2:
            //unsetenv
            if((unsetenv(cmd->args[0])) == 0){
                printf("~ Unset env var %s\n", cmd->args[0]);
            } else printf("~ Failed to unset env var\n");
            break;
        case 3:
            //pwd
            printf("");
            char buffer[FILENAME_MAX];
            printf("~ Current working directory: %s\n", getcwd(buffer, sizeof(buffer)));
            break;
        case 4:
            //exit
            //grandTotal();
            currentTotal();
            printf("Thanks for using the SUSH, goodbye.\n");
            exit(0);
            break;
        case 5:
            //accnt
            //processAccountSelf();
            break;
        default: 
            printf("~ Not an internal command\n");
    }
    processAccountSelf();
}

void printRUSAGE(struct rusage usage)
{
    printf("User CPU time used: %ld.%06ld\n", usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
          printf("System CPU time used: %ld.%06ld\n", usage.ru_stime.tv_sec, usage.ru_stime.tv_usec);
            printf("Max resident set size: %ld\n", usage.ru_maxrss);
            printf("Integral shared memory size: %ld\n", usage.ru_ixrss);
            printf("Integral unshared data size: %ld\n", usage.ru_idrss);
            printf("Integral unshared stack size: %ld\n", usage.ru_isrss);
            printf("Page reclaims: %ld\n", usage.ru_minflt);
            printf("Page faults: %ld\n", usage.ru_majflt);
            printf("Number of swaps: %ld\n", usage.ru_nswap);
            printf("Block input operations: %ld\n", usage.ru_inblock);
            printf("Block output operations: %ld\n", usage.ru_oublock);
            printf("IPC messages sent: %ld\n", usage.ru_msgsnd);
            printf("IPC messages recieved: %ld\n", usage.ru_msgrcv);
            printf("Signals recieved: %ld\n", usage.ru_nsignals);
            printf("Voluntary context switches: %ld\n", usage.ru_nvcsw);
            printf("Involuntary context switches: %ld\n", usage.ru_nivcsw);
}

void processAccountSelf(){
    struct rusage usage;
    
    if(getrusage(RUSAGE_SELF, &usage) == 0){
            printRUSAGE(usage);
    } else printf("An Error Occured\n");
}

void currentTotal(){
    //should display the current total system usage of processes running
}

void grandTotal(){
    //should display totals of system usage from self, children, and threads
}

void sigHandler(int signo){
    if(signo == SIGINT){
        //user pressing ctrl + c
        printf(" ");
    } else if(signo == SIGUSR1){
        //display current processes system resources
        processAccountSelf();
    } else if(signo == SIGUSR2){
        //display the current running total and
        //current process totals
        currentTotal();
    }
}