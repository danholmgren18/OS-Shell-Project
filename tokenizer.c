/*
* Class to play around with the Finite State Machine Functionality
* @author: Zachary Semanco 
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INPUT_SIZE 256

int tokenize(char *input_str)
{
    char str[INPUT_SIZE];
    strcpy(str, input_str);

    int state = 0;

    char command_name[64] = {0};
    char argument[64] = {0};
    char file_name[64] = {0};

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
                } else if(str[i] == '\0' || str[i] == '\n')
                {
                    printf("\n\tEND OF PARSING\n");
                    break;
                } else 
                {
                    state = 4;
                    printf("to State 4\n");
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
                    strncat(argument, &str[i], 1);
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

            /* Redirections */
            case 5:
                printf("State 5\n");
                printf("%c - ", str[i]);

                //if ()
                break;

            /* Error State */
            default:
                //printf("ERROR: Command Not Found");
                //exit(-1);
                printf("default\n");
        }
    }

    printf("Command Name: %.*s\n", (int)sizeof(command_name), command_name);
    printf("Argument:     %.*s\n", (int)sizeof(argument), argument);
    printf("File Name:    %.*s\n", (int)sizeof(file_name), file_name);

    return 5;
}