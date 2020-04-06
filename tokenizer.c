/*
* Class to play around with the Finite State Machine Functionality
* @author: Zachary Semanco 
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INPUT_SIZE 256

typedef struct _Token 
{
    char command_name[64];
    char argument[64];
    char in_quotes[64];
    char file_name[64];
    int redirect; 
} Token;

// a b c d e > output
// a b < input e f g
// tokens: { a  b, c, d e, >, output}

typedef struct _Token2 
{
    int num_tokens;
    char *tokens[20];
} tokenizer_t;

// cmd = { .cmd = "a", .ag s= "b", "c", "d", "e", .append = 0, output = "output"
//  }// struct to "parse" command line
// typedef struct 
// {
//     char *cmd;
//     char *in_name;
//     char *out_name;
//     int append;
//     char *args[];
// } command_t;

Token tokenize(char *input_str)
{
    printf("In the tokenize command\n");
    
    tokenizer_t t_token;
    t_token.num_tokens = 0;

    char* temp = strtok(input_str, " ");
    
    t_token.tokens[t_token.num_tokens] = strdup(temp);
    t_token.num_tokens++;
    
    
    while (temp != NULL)
    {
        printf("here\n");
        
        temp = strtok(NULL, " ");
        
        t_token.tokens[t_token.num_tokens] = strdup(temp);
        
        t_token.num_tokens++;
    }

    printf("Num Tokens = %d\n", t_token.num_tokens);
    for(int i = 0; i < t_token.num_tokens; i++)
    {
        printf("Token %d = %s\n", i, t_token.tokens[i]);
    }


    char str[INPUT_SIZE];
    strcpy(str, input_str);
    
    char command_name[64] = {0};
    char argument[64] = {0};
    char in_quotes[64] = {0};
    char file_name[64] = {0};
    int redirect = 0;

    int state = 0;

    for(int i = 0; i < strlen(str); i++)
    {
        switch(state)
        {
            /* Starting State */
            case 0:
                printf("State 0\n");
                printf("%c - ", str[i]);
               
                if (str[i] == '|' || str[i] == '<' || str[i] == '>') 
                {
                     printf("ERROR: Invalid Command Entered\n");
                     exit(-1); 
                } else if (str[i] == ' ') 
                { 
                    state = 0;
                    printf("to State 0\n");

                } else if(str[i] == '\0' || str[i] == '\n')
                {
                    printf("\n\tEND OF PARSING\n");
                    break;
                } else 
                { 
                    state = 1; 
                    strncat(command_name, &str[i], 1);
                    printf("to State 1\n");
                }
                
                break;

            /* Read First Command State */
            case 1:
                printf("State 1\n");
                printf("%c - ", str[i]);

                if (str[i] == ' ') 
                {
                    state = 2; 
                    printf("to State 2\n");
                } else if(str[i] == '\0' || str[i] == '\n')
                {
                    printf("\n\tEND OF PARSING\n");
                    break;
                } else
                {
                    state = 1;
                    strncat(command_name, &str[i], 1);
                    printf("to State 1\n");
                }
                
                break;

            /* Check State: Quotations(goto 3), Space(goto 2), Redirect(goto 4)  */
            case 2: 
                printf("State 2\n");
                printf("%c - ", str[i]);
                
                if (str[i] == '\'' || str[i] == '\"') //starting quote
                { 
                    state = 3; 
                    printf("to State 3\n");
                } else if (str[i] == ' ') 
                { 
                    state = 2;
                    printf("to State 2\n");
                } else if (str[i] == '<' || str[i] == '>' || str[i] == '|')
                {
                    state = 4;
                    printf("to State 4\n");
                    redirect = 1;
                } else if(str[i] == '\0' || str[i] == '\n')
                {
                    printf("\n\tEND OF PARSING\n");
                    break;
                } else 
                {
                    state = 2;
                    strncat(argument, &str[i], 1);
                    printf("to State 2\n");
                }
                
                break;

            /* In Quotes State */
            case 3:
                printf("State 3\n");
                printf("%c - ", str[i]);

                if (str[i] == '\'' || str[i] == '\"') //ending quote
                { 
                    state = 2;
                    printf("to State 2\n");
                } else if(str[i] == '\0' || str[i] == '\n')
                {
                    printf("\n\tEND OF PARSING\n");
                    break;
                } else 
                { 
                    state = 3;
                    strncat(in_quotes, &str[i], 1);
                    printf("to State 3\n");
                }

                break;
                
            /* Redirect State */
            case 4:
                printf("State 4\n");
                printf("%c - ", str[i]);
                
                if (str[i] == ' ') //leading space
                { 
                    state = 4;
                    printf("to State 4\n"); 
                } else if(str[i] == '\0' || str[i] == '\n')
                {
                    printf("\n\tEND OF PARSING\n");
                    break;
                } else 
                {
                    state = 4;
                    strncat(file_name, &str[i], 1);
                    printf("to State 4\n");
                    
                    if(str[i+1] == ' ')
                    {
                        state = 2;
                        printf("space after text, assume end of text, redirect state 2\n");
                    }
                }
                
                break;

            
            default:
                printf("Invalid State in Tokenizer\n");
                exit(-2);
        }
    }

    printf("Command Name: %.*s\n", (int)sizeof(command_name), command_name);
    printf("Argument:     %.*s\n", (int)sizeof(argument), argument);
    printf("In Quotes:    %.*s\n", (int)sizeof(in_quotes), in_quotes);
    printf("Redirect:     "); printf(redirect ? "true\n" : "false\n"); 
    printf("File Name:    %.*s\n", (int)sizeof(file_name), file_name);

    Token tokens;
    strcpy(tokens.command_name, command_name);
    strcpy(tokens.argument, argument);
    strcpy(tokens.in_quotes, in_quotes);
    tokens.redirect = redirect;
    strcpy(tokens.file_name, file_name);

    return tokens;
}