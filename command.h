/*
* Header File for the Command File
* @author: Zachary Seamnco
*/

#ifndef _COMMAND_H
#define _COMMAND_H

enum redirect_type {
    OUT,
    IN,
    APPEND,
    PIPE
};

typedef struct _Command
{
    char *cmd;
    char *in_name;
    char *out_name;
    int argc;
    int contains_redirect;
    int redirect_pos;
    int redirect_type;
    char *args[];
} command_t;

void parseAndRun(command_t *cmd_ptr);
void run_command(const char* cmd, const char* args[], command_t *cmd_ptr);
#endif