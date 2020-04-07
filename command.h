/*
*
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

#endif