/*
* File for our shell to use to handle external commands
* @author: Zachary Semanco
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include "command.h"


void parseAndRun(command_t *cmd_ptr)
{
    char* precmd = strdup("/bin/");

    int len1 = strlen(precmd);
    int len2 = strlen(cmd_ptr->cmd);

    const char* command = strndup(strcat(precmd, cmd_ptr->cmd), len1+len2);

    const char* arguments[20] = { strdup(cmd_ptr->cmd) };

    for(int i = 0; i < cmd_ptr->argc; i++)
    {
        arguments[i+1] = strdup(cmd_ptr->args[i]);
        i++;
    }

    run_command(command, arguments);
}

void run_command(const char* command, const char* arguments[])
{
    
    pid_t pid = fork();

    if(pid == 0)
    {
        execvp(command, arguments);
        perror("ERROR: Could not execute command!\n");
        exit(-1);
    } else
    {
        int status;
        waitpid(pid, &status, 0);
    }
    printf("---done running command---\n");
}