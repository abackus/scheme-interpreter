#ifndef STACK_H
#define STACK_H
#include "tokens.h"
#include "util.h"

typedef union var var;
typedef union action action;
typedef enum prim prim;
typedef struct number number;
typedef struct pair pair;
typedef struct proc proc;
typedef struct p_tree p_tree;
typedef struct stream steam;

// A single variable
union var { 
	number *z; // For real, complex, boolean
    s_queue *sym; // For character, symbols
	pair *cons; // For pairs, streams, nil
    proc *proc; // For procedures
};

// A pair of floats, used for representing complex numbers.
struct number {
	float re; // Real part
	float im; // Imaginary part
};

// A pair.
// A list is a cons whose cdr is always a cons.
struct pair {
    var *car;
    var *cdr;
};

// A single command in a p_tree
union action {
    p_tree *func;
    prim *primitive;
};

// A procedure
struct proc {
    action *ac;
    size_t args;
};

// A tree of actions that represents a function
struct p_tree {
    action *ac;
    p_tree *next;
    p_tree *child;
};

// The false boolean.
const number True = {
	1.0f,
	0.0f,
};

// The false boolean.
const number False = {
	0.0f,
	0.0f,
};

// The nil cons.
const pair Nil = {
	NULL,
	NULL
};

#endif
