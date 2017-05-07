<<<<<<< HEAD
#include "tokens.h"
#include <stddef.h>
#include <stdlib.h>

// Increasing this trades off space for time
#define RESIZE_FACTOR 2

struct t_tree;
struct t_list;

// A t_tree is an intermediary in parsing a Scheme command.
// Scheme commands take the form (parent children[1] children[2] ... ).
struct t_tree {
    struct atom *parent;
    struct t_list *children;
};

// A dynamic list of t_trees, used to store children.
struct t_list {
    struct t_tree *tree;
    size_t ptr;
    size_t cap;
};
=======
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
>>>>>>> stacks etc
