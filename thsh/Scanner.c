#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "Scanner.h"

Token GetNext(CharItr *self);

bool isSpace(char nextChar);
bool isEnd(char nextChar);
bool isPipe(char nextChar);

Scanner Scanner_value(CharItr char_itr)
{
    Token starterToken = GetNext(&char_itr);

    Token next = {
       starterToken.type,
      starterToken.lexeme
    };


    Scanner itr = {
        char_itr,
        next
    };

    return itr;
}

bool Scanner_has_next(const Scanner *self)
{
    return self->next.type != END_TOKEN;
}

Token Scanner_peek(const Scanner *self)
{
    return self->next;
}

Token Scanner_next(Scanner *self)
{
    Token nextToken = self->next; 
    self->next = GetNext(&self->char_itr);
    return nextToken;
}

CharItr findNextChar;
Token GetNext(CharItr *self){
    if (!CharItr_has_next(self)){
        Token returnToken = {END_TOKEN, Str_from("")};;
        Str_drop(&returnToken.lexeme);
        return returnToken; 
    }

    char nextChar = CharItr_peek(self);

    while (CharItr_has_next(self) && isSpace(nextChar)){
        CharItr_next(self); 
        if (CharItr_has_next(self)) {
            nextChar = CharItr_peek(self);
        }
    }
   
    if (isEnd(nextChar)){
        Token returnToken = {END_TOKEN, Str_from("")};
        return returnToken; 
    }
   
    else if (isPipe(nextChar)){
        Token returnToken = {PIPE_TOKEN, Str_from(&nextChar)};
        CharItr_next(self);
        while (CharItr_has_next(self) && isSpace(nextChar)){
            CharItr_next(self); 
        }
        return returnToken;
    }
   
    else {
        size_t i = 0;
        char charr;
        Str str = Str_value(sizeof(char));

        while (CharItr_has_next(self) && (CharItr_peek(self) != ' ')){
           charr = CharItr_next(self);
           Str_set(&str, i, charr);
           i++;
        } 

        while (CharItr_has_next(self) && (isSpace(CharItr_peek(self)))){
            CharItr_next(self);
        }

        Token returnToken = {WORD_TOKEN, str};
        return returnToken;
    }
}

bool isSpace(char nextChar) {
    if (nextChar == '\t' || nextChar == ' ') {   
        return true;
    }
    return false;
}

bool isEnd(char nextChar) {
    if (nextChar == EOF || nextChar == '\0'){
        return true;
    }
    return false;
}
 bool isPipe(char nextChar) {
     if (nextChar == '|') {
         return true;
     }
     return false;
 }
