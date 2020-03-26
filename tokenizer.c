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
    int i = 0;
    token = strtok(str, " ");
    comms[i] = token;

    while(token != NULL){
        token = strtok(NULL, " ");
    }
}

