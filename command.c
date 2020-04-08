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
        if(!strcmp(cmd_ptr->args[i], ">") || !strcmp(cmd_ptr->args[i], "<") || !strcmp(cmd_ptr->args[i], "|") || (!strcmp(cmd_ptr->args[i], ">>")))
        {
            i++; //skip the redirect symbol.
        }
        arguments[i+1] = strdup(cmd_ptr->args[i]);
    }

    run_command(command, arguments, cmd_ptr);
}

void run_command(const char* command, const char* arguments[], command_t *cmd_ptr)
{
    int out;
    int in;
    int app;
    // if(cmd_ptr->redirect_type == OUT) {
    //     out = open(cmd_ptr->out_name, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    // } else if (cmd_ptr->redirect_type == IN) {
    //     in = open(cmd_ptr->in_name, O_RDONLY);
    // } else if (cmd_ptr->redirect_type == APPEND) {
    //     app = open(cmd_ptr->out_name, O_RDWR | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
    // }

    pid_t pid = fork();

    if(pid == 0)
    {
        if (cmd_ptr->contains_redirect != 0) 
        {
            if (cmd_ptr->redirect_type == OUT) {
                out = open(cmd_ptr->out_name, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
                
                dup2(out, 1); // make stdout go to file

                close(out);

                execvp(command, arguments);
                perror("~ ERROR: Could not execute command with redirect!");

            } else if (cmd_ptr->redirect_type == IN) {                
                in = open(cmd_ptr->in_name, O_RDONLY);
                
                dup2(in, 0);

                close(in);

                execvp(command, arguments);
                perror("~ ERROR: Could not execute command with redirect!");
            } else if (cmd_ptr->redirect_type == APPEND) {
                app = open(cmd_ptr->out_name, O_RDWR | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
                
                dup2(app, 1);

                close(app);

                execvp(command, arguments);
                perror("~ ERROR: Could not execute command with redirect");
            } else
            {
                execvp(command, arguments);
                perror("~ ERROR: Could not execute command with redirect!");
                exit(-1);
            } 
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