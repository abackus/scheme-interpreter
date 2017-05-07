#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

typedef struct s_queue s_queue;
typedef struct sq_node sq_node;

// A queue of chars for string parsing purposes
// Implemented using a linked list
struct s_queue {
	sq_node *first;
	sq_node *last;
	int len;
};

// A node in an s_queue
struct sq_node {
	char c;
	sq_node *next;
};

// Methods for s_queues
s_queue *newqueue();
sq_node *newnode(char c);
void sq_push(s_queue *queue, char c);
char sq_pop(s_queue *queue);
char *tostring(s_queue *queue);
s_queue *toqueue(char *string);

// Methods for debugging
void err(char *msg, char *scheme);

#endif // UTIL_H_INCLUDED
