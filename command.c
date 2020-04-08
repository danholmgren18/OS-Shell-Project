/*
* File for our shell to use to handle external commands
* @author: Zachary Semanco
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
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
        if(!strcmp(cmd_ptr->args[i], ">") || !strcmp(cmd_ptr->args[i], "<") || !strcmp(cmd_ptr->args[i], "|"))
        {
            i++; //skip the redirect symbol. 
        }
        arguments[i+1] = strdup(cmd_ptr->args[i]);
        printf("----- %s\n",arguments[i+1]);
    }

    run_command(command, arguments, cmd_ptr->redirect_pos);
}

void run_command(const char* command, const char* arguments[], int redirect)
{
    int fd;
    if(redirect != 0) {
        fd = open(arguments[redirect], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    }

    pid_t pid = fork();

    if(pid == 0)
    {
        if (redirect != 0) {
            dup2(fd, 1); // make stdout go to file

            close(fd);

            execvp(command, arguments);
            perror("~ ERROR: Could not execute command with redirect!");

        } else 
        {
            execvp(command, arguments);
            perror("~ ERROR: Could not execute command!");
            exit(-1);
        }
    } else
    {
        int status;
        waitpid(pid, &status, 0);
    }
    printf("~ ---done running command---\n");
}