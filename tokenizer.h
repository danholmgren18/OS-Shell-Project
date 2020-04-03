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

Token tokenize(char *str); //Function holding tokenizing functionality 

