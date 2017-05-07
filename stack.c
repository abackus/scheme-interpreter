#include "stack_internal.h"

// Push a new frame onto the call stack
stackf *stackf_push(stackf *curr_thread, size_t vars) {
	size_t size = vars * sizeof(mbucket);
	mbucket *b = malloc(size);
	stackf *frame = malloc(sizeof(stackf));
	if (b == NULL || frame == NULL) {
		err("Failed to write to call stack!", "");
	}
	frame->under = curr_thread;
	frame->buckets = b;
	frame->size = size;
	return frame;
}

// Pop a frame off the call stack
stackf *stackf_pop(stackf *curr_thread) {
	stackf *target = curr_thread->under;
	mbucket *b = curr_thread->buckets;
	for (size_t i = 0; i < curr_thread->size; i += sizeof(mbucket)) {
		free((b + i)->key);
		free((b + i)->value);
	}
	free(b); // Make sure this works as intended!
	free(curr_thread);
	return target;
}

// Returns the hash code for v
unsigned hash(s_queue *k) {
	// Make sure this isn't destructive
	sq_node *k_copy = k->first;
	unsigned hash = 0;
	while (k_copy != NULL) {
		hash += (int)k_copy->c;
		hash *= 131;
		k_copy = k_copy->next;
	}
	return hash;
}

// Add a new variable
mbucket *addvar(stackf *curr_thread, s_queue *k, var *v, scmtype type) {
	unsigned h = hash(k) % curr_thread->size;

	// TODO: this
}