#include "Parser.h"
#include <stdio.h>
#include "Node.h"

static Node* parse_command(Scanner *scanner);
static Node* parse_pipe(Scanner *scanner, Node *left);
static Node* parse_end();

Node* parse(Scanner *scanner)
{
    Token next = Scanner_peek(scanner);
    switch(next.type){
        case WORD_TOKEN:  
            return parse_command(scanner);
        case PIPE_TOKEN:
            return parse_command(scanner);
        case END_TOKEN:
            return parse_end();
    }
}

static Node* parse_end() {
     Node *returnerNode= ErrorNode_new("");
     return returnerNode;
 }

static Node* parse_pipe(Scanner *scanner, Node *left){
    Node *right = parse_command(scanner);
    Node *pipeNode = PipeNode_new(left, right);
    pipeNode->type = PIPE_NODE;
    return pipeNode;
}

static Node* parse_command(Scanner *scanner) {
    StrVec strvec = StrVec_value(1);
    while (Scanner_has_next(scanner)) {
        Token tkn = Scanner_next(scanner);
        if (tkn.type == WORD_TOKEN){
            StrVec_push(&strvec, tkn.lexeme);
        } else if (tkn.type == PIPE_TOKEN) {
            Node *left = CommandNode_new(strvec);
            return parse_pipe(scanner, left);
        }
    }
    Node *returnerNode= CommandNode_new(strvec);
    return returnerNode;
}


