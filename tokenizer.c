/*
* Tokenizer and Parsing class for shell project
* @author: Zachary Semanco, Daniel Holmgren
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* token;
char* errors = "<>|";

int tokenize(char *str, char *search){
    char *commands[15];
    int place = 0;
    token = strtok(str, search);
    if(strchr(errors, *token)){
        printf("Error: Cannot have special character first.\n");
        return 0;
    }
    while(token != NULL){
        printf("%s\n", token);
        commands[place] = token;
        place++;
        token = strtok(NULL, search);
    }
    
    return 1;
}

int main(void){
    char line[1024];
    printf("Enter a command: ");
    fgets(line, sizeof line, stdin);
    line[strcspn(line, "\n")] = 0;

    int worked = tokenize(line, " ");
    printf("%d\n", worked);
}


