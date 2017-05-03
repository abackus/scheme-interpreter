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
