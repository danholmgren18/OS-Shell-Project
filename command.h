/*
* Header File for the Command File
* @author: Zachary Seamnco
*/

#ifndef _COMMAND_H
#define _COMMAND_H

typedef struct _Command
{
    char *cmd;
    char *in_name;
    char *out_name;
    int append;
    int argc;
    char *args[];
} command_t;

void parseAndRun(char* cmd, char *args[], int argc);
void run_command(const char* cmd, const char* args[]);
#endif