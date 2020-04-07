/*
* Class to play around with the Finite State Machine Functionality
* @author: Zachary Semanco 
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tokenizer.h"


enum state {
    INITIAL,
    TOKEN,
    QUOTE,
    COMMA_AFTER_QUOTE,
    END_TOKEN,
    ERROR, 
    DONE
};

int iswhitespace(char ch) { 
    if (ch == ' ') return 1;
    if (ch == '\t') return 1;
    return 0;
}

int isnewline(char ch) {
    if (ch == '\n') return 1;
    else return 0;
}

tokenizer_t tokenize(char *input_str)
{
    tokenizer_t tknzr;
    
    memset(&tknzr, 0, sizeof(tknzr));

    int curr = 0;
    enum state state = INITIAL;  
    enum state next_state = INITIAL;
    int token_start = 0;

    while (state != DONE) {

        char ch = input_str[curr];

        // if (ch == '\n') state=END_TOKEN;

        switch(state) {
            case INITIAL:
                if (iswhitespace(ch)) next_state = INITIAL;
                // empty field
                else if (ch == ' ') {
                    tknzr.tokens[tknzr.num_tokens] = "";
                    tknzr.num_tokens++;
                    next_state = INITIAL;
                }
                else if (ch == '"') {
                    token_start = curr;
                    next_state = QUOTE;
                }
                else if (isnewline(ch)) next_state = DONE;
                else {
                    token_start = curr;
                    next_state = TOKEN;
                }
                break;

            case TOKEN:
                if (iswhitespace(ch) || isnewline(ch)) {
                    if(iswhitespace(ch)) { 
                        next_state = INITIAL;
                    } else {
                        next_state = DONE;
                    }
                    tknzr.tokens[tknzr.num_tokens] = strndup(input_str+token_start, (curr-token_start));
                    tknzr.num_tokens++;
                }
                else {
                    next_state = TOKEN;
                }
                break;
            case QUOTE:
                
                if (ch == '"') {
                    tknzr.tokens[tknzr.num_tokens] = strndup(input_str+token_start+1, (curr-token_start-1));
                    tknzr.num_tokens++;
                    next_state = COMMA_AFTER_QUOTE;
                } else if (isnewline(ch)) next_state = ERROR;
                else {
                    next_state = QUOTE;
                }
                break;

            case COMMA_AFTER_QUOTE:
                if (ch == ' ') next_state = INITIAL;
                else if (ch == '\n') next_state = DONE;
                else next_state = ERROR;
                break;
            
            case END_TOKEN:
                tknzr.tokens[tknzr.num_tokens] = strndup(input_str+token_start, (curr-token_start));
                tknzr.num_tokens++;
                next_state = DONE;
                break;
 
            case ERROR:
                next_state = DONE;
                printf("Error in Tokenizer\n");
                break;
        } // end switch


        printf("state %d, %c -> %d\n", state, ch, next_state);
        curr++;
        state = next_state;
        
    } // end of while

    printf("-------------------\n");

    return tknzr;
}