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
    token = strtok(str, " ");
    while(token != NULL){
        printf("%s\n", token);
        token = strtok(NULL, " ");
    }
}

int main(void){
    char testing[100];
    strncpy(testing, "This is a test", 100);
    tokenize(testing);
}


