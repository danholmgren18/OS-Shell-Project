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

    printf("Your command: %s", command);

 }