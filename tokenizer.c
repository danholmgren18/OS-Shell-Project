/*
* Class to play around with the Finite State Machine Functionality
* @author: Zachary Semanco, DDaniel Holmgren
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tokenizer.h"


enum state {
    INITIAL,
    TOKEN,
    QUOTE,
    AFTER_QUOTE,
    REDIRECT_FOUND,
    AFTER_REDIRECT,
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

int isredirect(char ch) {
    if ((ch == '>') || (ch == '<') || (ch == '|')) return 1;
    else return 0;
}

tokenizer_t tokenize(char *input_str)
{
    tokenizer_t tknzr;
    
    memset(&tknzr, 0, sizeof(tknzr));
    tknzr.redirect_found = 0;
    int curr = 0;
    enum state state = INITIAL;  
    enum state next_state = INITIAL;
    int token_start = 0;

    while (state != DONE) {

        char ch = input_str[curr];

        switch(state) {
            case INITIAL:
                if (iswhitespace(ch)) next_state = INITIAL;
                
                else if (ch == ' ') {
                    tknzr.tokens[tknzr.num_tokens] = "";
                    tknzr.num_tokens++;
                    next_state = INITIAL;
                }
                else if (isredirect(ch)){
                    token_start = curr;
                    next_state = REDIRECT_FOUND;
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
                } else if (isredirect(ch)) {
                    next_state = REDIRECT_FOUND;
                    tknzr.tokens[tknzr.num_tokens] = strndup(input_str+token_start, (curr-token_start));
                    tknzr.num_tokens++;
                    token_start = curr;
                }
                else {
                    next_state = TOKEN;
                }
                break;
            case QUOTE:
                
                if (ch == '"') {
                    tknzr.tokens[tknzr.num_tokens] = strndup(input_str+token_start+1, (curr-token_start-1));
                    tknzr.num_tokens++;
                    next_state = AFTER_QUOTE;
                } else if (isnewline(ch)) next_state = ERROR;
                else {
                    next_state = QUOTE;
                }
                break;

            case AFTER_QUOTE:
                if (iswhitespace(ch)) next_state = INITIAL;
                else if (isnewline(ch)) next_state = DONE;
                else next_state = ERROR;
                break;

            case REDIRECT_FOUND:
                tknzr.redirect_found = 1;
                if (iswhitespace(ch)) {
                    tknzr.tokens[tknzr.num_tokens] = strndup(input_str+token_start, (curr-token_start));
                    tknzr.num_tokens++;
                    next_state = INITIAL;
                    token_start = curr;
                } else if (ch == '>') {
                    next_state = REDIRECT_FOUND;
                    tknzr.append;
                }
                else if (isnewline(ch)) next_state = ERROR;
                else {
                    token_start = curr;
                    next_state = TOKEN;
                }
                break;
            
            case AFTER_REDIRECT:
                if (iswhitespace(ch)) next_state = AFTER_REDIRECT;
                else if (isnewline(ch)) next_state = ERROR;
                else {
                    next_state = TOKEN;
                    token_start = curr;
                }

            case END_TOKEN:
                tknzr.tokens[tknzr.num_tokens] = strndup(input_str+token_start, (curr-token_start));
                tknzr.num_tokens++;
                next_state = DONE;
                break;
 
            case ERROR:
                next_state = DONE;
                printf("~ Error in Tokenizer\n");
                break;
        } // end switch

        curr++;
        state = next_state;

    } // end of while

    return tknzr;
}