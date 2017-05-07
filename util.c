#include <stdio.h>
#include "util.h"

// Prints an error message. To be improved
void err(char *msg, char *scheme) {
	printf(msg);
	printf("\nUser input was: ");
	printf(scheme);
}

// Creates a s_queue with no members
s_queue *newqueue() {
	s_queue *queue = malloc(sizeof(s_queue));
	if (queue == NULL) {
		err("Coudln't make a new s_queue", "");
		return NULL;
	}
	queue->first = NULL;
	queue->last = NULL;
	queue->len = 0;
	return queue;
}

// Creates a sq_node for the character
sq_node *newnode(char c) {
	sq_node *node = malloc(sizeof(sq_node));
	if (node == NULL) {
		err("Couldn't make a queue node", &c);
	}
	node->c = c;
	node->next = NULL;
}

// Push onto the queue
void sq_push(s_queue *queue, char c) {
	sq_node *node = newnode(c);
	if (queue->first == NULL) {
		queue->first = node;
	}
	if (queue->last != NULL) {
		queue->last->next = node;
	}
	queue->last = node;
	queue->len++;
}

// Pop from the queue
char sq_pop(s_queue *queue) {
	if (queue->first == NULL) {
		return '\0';
	}
	char c = queue->first->c;
	sq_node *next = queue->first->next;
	free(queue->first);
	queue->first = next;
	queue->len--;
	return c;
}

// Turn a s_queue* into a char*, destroying the s_queue* in the process
char *tostring(s_queue *queue) {
	char *scheme = malloc(sizeof(char) * (1 + queue->len));
	unsigned i = 0;
	while (queue->first) {
		scheme[i] = sq_pop(queue);
		i++;
	}
	free(queue);
	scheme[i] = '\0';
	return scheme;
}

// Turns a char* into a s_queue*
s_queue *toqueue(char *scheme) {
	s_queue *queue = newqueue();
	int i = 0;
	while (scheme[i] != '\0') {
		sq_push(queue, scheme[i]);
		i++;
	}
	return queue;
}