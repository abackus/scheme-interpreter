#ifndef TOKENS_INTERNAL_H_INCLUDED
#define TOKENS_INTERNAL_H_INCLUDED
#include "tokens.h"

#define ATOM_SIZE 16

// Methods for t_trees
t_tree *newatom(char *scheme);
void newsibling(t_tree *t, t_tree *sibling);
void newchild(t_tree *t, t_tree *child);
void insertatom(t_tree *t, s_queue *queue);

// Methods for tokenization
t_tree *tokenize_r(s_queue *queue);

// Methods for debugging
void toscheme_r(t_tree *tokens, s_queue *queue);
char *toscheme(t_tree *tokens);
int main();

#endif // TOKENS_INTERNAL_H_INCLUDED