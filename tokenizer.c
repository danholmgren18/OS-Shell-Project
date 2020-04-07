/*
* Class to play around with the Finite State Machine Functionality
* @author: Zachary Semanco 
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct _Token2 
{
    int num_tokens;
    char *tokens[20];
} tokenizer_t;

tokenizer_t tokenize(char *input_str)
{
    tokenizer_t tknzr;
    int count = 0;

    char* tok = strtok(input_str, " ");    
   
    while(tok != NULL)
    {        
        tknzr.tokens[count] = strdup(tok);
        count++;
        tok = strtok(NULL, " ");
    }

    tknzr.num_tokens = count;

    return tknzr;
}