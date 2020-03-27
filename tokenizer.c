/*
* Tokenizer and Parsing class for shell project
* @author: Zachary Semanco, Daniel Holmgren
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* comms[10];
char* token;


void tokenize(char *str){
    char *commands[15];
    int place = 1;
    token = strtok(str, " ");
    commands[0] = token;
    while(token != NULL){
        printf("%s", token);
        token = strtok(NULL, " ");
        commands[place] = token;
        place++;
    }
}

int main(void){
    char line[1024];
    printf("Enter a command: ");
    fgets(line, sizeof line, stdin);
    line[strcspn(line, "\n")] = 0;

    tokenize(line);
}


