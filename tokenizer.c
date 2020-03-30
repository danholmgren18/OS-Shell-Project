/*
* Tokenizer and Parsing class for shell project
* @author: Zachary Semanco, Daniel Holmgren
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* comms[10];
char* token;
char* errors = "<>|";

int tokenize(char *str){
    char *commands[15];
    int place = 0;
    token = strtok(str, " ");
    if(strchr(errors, *token)){
        printf("Found the error\n");
        return 0;
    }
    //commands[place] = token;
    printf("stored the token\n");
    while(token != NULL){
        printf("Entered the while loop\n");
        commands[place] = token;
        place++;
        printf("%s", token);
        token = strtok(NULL, " ");
    }
    
    return 1;
}

int main(void){
    char line[1024];
    printf("Enter a command: ");
    fgets(line, sizeof line, stdin);
    line[strcspn(line, "\n")] = 0;

    int worked = tokenize(line);
    printf("%d\n", worked);
}


