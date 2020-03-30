/*
* Class to play around with the Finite State Machine Functionality
* @author: Zachary Semanco 
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INPUT_SIZE 256

int walkThroughInput(char *input_str)
{
    char str[INPUT_SIZE];
    strcpy(str, input_str);
    int input_size = strlen(str);
    char delim[] = " ";

    char *ptr = strtok(str, delim);

    while (ptr != NULL)
    {
        printf("'%s'\n", ptr);
        ptr = strtok(NULL, delim);
    }

    return 0;
}

int main()
{
    printf("\n---Start---\n");
    printf("input the string to be tokeinzed\n");

    char input_str[INPUT_SIZE];

    fgets(input_str, INPUT_SIZE, stdin);


    walkThroughInput(input_str);
}