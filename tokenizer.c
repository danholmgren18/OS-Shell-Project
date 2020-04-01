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
    int input_size = strlen(str);
    char delim[] = " ";

    char *ptr = strtok(str, delim);

    int state = 0;

    while (ptr != NULL)
    {
        printf("'%s' \n", ptr);
        ptr = strtok(NULL, delim);
    
        switch(state)
        {
            /* Starting State */
            case 0:
                //if (ptr = error) { default }
                //if (ptr = " ") { state = 0; }
                //if (ptr = valid) { state = 1; }
                break;

            /* Read First Command State */
            case 1:
                //if (ptr = valid) { state = 1; }
                //if (ptr = blank) { state = 2; }
                break;

            /* Junction State */
            case 2: 
                //if (ptr = open_quote) { state = 3; }
                //if (ptr = blank) { state = 2; }
                //if (ptr = valid) { state = 4; }
                break;

            /* Quotations State */
            case 3:
                //if (ptr = close_quote) { state = 2; }
                //if (ptr = valid) { state = 3; }
                break;
                
            /* Command State */
            case 4:
                //if (ptr = valid) { state = 4; }

                break;

            /* Redirections */
            case 5:
                //if ()

            /* Error State */
            default:
                //printf("ERROR: Command Not Found");
                //exit(-1);
        }
    
    
    }

    return 5;
}