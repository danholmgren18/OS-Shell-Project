/*
* Header File for the Tokenizer
* @author: Zachary Seamnco
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct _Token 
{
    char command_name[64];
    char argument[64];
    char in_quotes[64];
    char file_name[64];
    int redirect; 
} Token;

typedef struct _Token2 
{
    int num_tokens;
    char *tokens[20];
} tokenizer_t;

Token tokenize(char *str); //Function holding tokenizing functionality 

