/*
* Header File for the Tokenizer
* @author: Zachary Seamnco
*/
#ifndef _TOKENIZER_H
#define _TOKENIZER_H


typedef struct _Token 
{
    int num_tokens;
    char *tokens[20];
} tokenizer_t;

tokenizer_t tokenize(char *str); //Function holding tokenizing functionality 

#endif