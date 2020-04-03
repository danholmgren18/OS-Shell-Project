/*
 * Runner Class for the Shell Project 
 * @author: Zachary Semanco, Daniel Holmgren
 */

#include "tokenizer.h"

#define COMMAND_SIZE 60

int main (int argc, char **argv[])
{
  const char *prompt = "Welcome to the Shippensburg University Shell (SUSH)! Please enter a command\n";

  setenv("PS1", prompt, 0);

  printf("%s", getenv("PS1"));


  char command[COMMAND_SIZE];

  fgets(command, COMMAND_SIZE, stdin);
  
  
  printf("\n\n");
  
  Token tokens;

  tokens = tokenize(command); 

  printf("\nIn Main, token.command_name: %s\n", tokens.command_name);
  printf("In Main, token.argument: %s\n", tokens.argument);
  printf("In Main, token.in_quotes: %s\n", tokens.in_quotes);
  printf("In Main, token.file_name: %s\n", tokens.file_name);
  printf("In Main, token.redirect: "); printf(tokens.redirect ? "true\n" : "false\n");
}