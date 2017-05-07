<<<<<<< HEAD
# define ATOM_LENGTH 16
# define NULL_ATOM "oudhn9s8afhwq34"

// An atom is the building block of a Scheme token.
// Atoms are any token without () in it.
struct atom {
    char *a;
};
=======
#ifndef TOKENS_H_INCLUDED
#define TOKENS_H_INCLUDED

#include <stddef.h>
#include <stdlib.h>
#include "util.h"

typedef struct t_tree t_tree;

// An n-ary tree for holding tokens, based on a linked list
struct t_tree {
	char *atom; // This node
	t_tree *child; // Child node
	t_tree *next; // Sibling node
};

void wipe(t_tree *t);
t_tree *tokenize(char *scheme);

#endif // TOKENS_H_INCLUDED
>>>>>>> stacks etc
