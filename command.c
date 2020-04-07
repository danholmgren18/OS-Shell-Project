/*
* File for our shell to use to handle external commands
* @author: Zachary Semanco
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "command.h"


void parseAndRun(char* cmd, char *args[], int argc)
{
    char* precmd = strdup("/bin/");

    int len1 = strlen(precmd);
    int len2 = strlen(cmd);

    const char* command = strndup(strcat(precmd, cmd), len1+len2);

    const char* arguments[20] = { strdup(cmd) };

    for(int i = 0; i < argc; i++)
    {
        arguments[i+1] = strdup(args[i]);
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