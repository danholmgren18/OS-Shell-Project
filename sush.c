/*
 * Runner Class for the Shell Project 
 * @author: Zachary Semanco, Daniel Holmgren
 */

#include "tokenizer.h"

#define COMMAND_SIZE 60

int command_list_size = 6;
char *command_list[] = {"cd", "setenv", "unsetenv", "pwd", "exit", "accnt"};


void checkInternalCommand(char *cmd);
void execInternal(int command_num);


int main (int argc, char **argv[])
{
  const char *prompt = "Welcome to the Shippensburg University Shell (SUSH)! Please enter a command\n";

  setenv("PS1", prompt, 0);

  printf("%s", getenv("PS1"));


  char command[COMMAND_SIZE];

  fgets(command, COMMAND_SIZE, stdin);
  
  
  printf("\n\n");
  
  tokenizer_t tkn;

  tkn = tokenize(command); 

  command_t cmd;

  cmd.cmd = tkn.tokens[0];

  checkInternalCommand(cmd.cmd);

  cmd.argc = tkn.num_tokens-1;

  for(int i = 1; i < tkn.num_tokens; i++)
  {
     cmd.args[i-1] = tkn.tokens[i];
  }

  // parseArgs(cmd.arg);

  // printf("\nIn Main, token.command_name: %s\n", tokens.command_name);
  // printf("In Main, token.argument: %s\n", tokens.argument);
  // printf("In Main, token.in_quotes: %s\n", tokens.in_quotes);
  // printf("In Main, token.file_name: %s\n", tokens.file_name);
  // printf("In Main, token.redirect: "); printf(tokens.redirect ? "true\n" : "false\n");
}


void checkInternalCommand(char *cmd)
{
    for(int i = 0; i < command_list_size - 1; i++)
    {
        if(strcmp(command_list[i], cmd) == 0)
        {
           execInternal(i);
        }
    }
}

void execInternal(int command_num)
{
  
    printf("command_num = %d\n", command_num);
    switch(command_num) 
    {
        case 0:
            printf("User entered %s\n", command_list[command_num]);
            break;
        case 1:
            printf("User entered %s\n", command_list[command_num]);
            break;
        case 2:
            printf("User entered %s\n", command_list[command_num]);
            break;
        case 3:
            printf("User entered %s\n", command_list[command_num]);
            break;
        case 4:
            printf("User entered %s\n", command_list[command_num]);
            break;
        case 5:
            printf("User entered %s\n", command_list[command_num]);
            break;
        default: 
            printf("Not an internal command\n");
    }
}

// void parseArgs (int argc, char *args[])
// {
//     int state = 0;

//     for(int i = 0; i < argc; i++)
//     {
//         switch(state)
//         {
//             case 0:

//         }
//     }

// }