#ifndef STACK_INTERNAL_H_INCLUDED
#define STACK_INTERNAL_H_INCLUDED

#include "tokens.h"
#include "stack.h"

typedef struct stackf stackf;
typedef struct mbucket mbucket;
typedef enum scmtype scmtype;

// The type of a variable.
enum scmtype {
	real,
	complex,
	boolean,
	character,
	symbol,
	lambda,
	cons,
	stream,
	nil
};

// The stack frame, which is implemented as a stack of hash maps.
// In turn, the hash maps are dynamic arrays.
struct stackf {
	stackf *under;
	mbucket *buckets;
	size_t size;
};

// A link of a bucket in the hash map. Represents a single variable.
struct mbucket {
	s_queue *key;
	var *value;
	scmtype type;
};

stackf *stackf_push(stackf *curr_thread, size_t vars);
stackf *stackf_pop(stackf *curr_thread);

#endif // STACK_INTERNAL_H_INCLUDED