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
    int contains_redirect;
    int redirect_pos;
    char *args[];
} command_t;

void parseAndRun(command_t *cmd_ptr);
void run_command(const char* cmd, const char* args[], int redirect);
#endif