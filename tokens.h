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
