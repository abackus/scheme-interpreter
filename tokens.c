#include "tokens_internal.h"

// Creates a t_tree with a single atom and no children
// Precondition: the scheme contains no spaces or parentheses
static t_tree *newatom(char *scheme) {
	t_tree *atom = malloc(sizeof(t_tree));
	if (atom == NULL) {
		err("Couldn't create new atom", scheme);
	}
	atom->atom = scheme;
	atom->child = NULL;
	atom->next = NULL;
	return atom;
}

// Adds a sibling to the t_tree t
static void newsibling(t_tree *t, t_tree *sibling) {
	if (t == NULL) {
		err("Can't write a sibling to a null tree", sibling->atom);
	}

	while (t->next != NULL) {
		t = t->next;
	}

	t->next = sibling;
}

// Adds a child to the t_tree t
static void newchild(t_tree *t, t_tree *child) {
	if (t == NULL) {
		err("Can't write a child to a null tree", child->atom);
	}

	if (t->child) {
		newsibling(t->child, child);
	}
	else {
		t->child = child;
	}
}

// Insert atom into a t_tree
static void insertatom(t_tree *t, s_queue *queue) {
	if (strlen(t->atom)) {
		newchild(t, newatom(tostring(queue)));
	}
	else {
		t->atom = tostring(queue);
	}
}

// Removes a t_tree t and all its children and siblings.
void wipe(t_tree *t) {
	if (t->next) {
		wipe(t->next);
	}
	if (t->child) {
		wipe(t->child);
	}
	free(t);
}

// Helper function for tokenize
static t_tree *tokenize_r(s_queue *queue) {
	// Add support for quote
	unsigned whitespace = 0;
	s_queue *atom = newqueue();
	t_tree *tokens = newatom("");

	char c = sq_pop(queue);
	while (c != '\0') {
		// Safety checks here

		// Check for spaces
		if (isspace(c)) {
			if (whitespace == 0 && atom->first) { // Delimits an atom
				insertatom(tokens, atom);
				atom = newqueue();
			}
			whitespace++;
			goto next;
		}
		else {
			whitespace = 0;
		}

		// Check for parens
		if (c == '(') {
			newchild(tokens, tokenize_r(queue));
			goto next;
		}
		if (c == ')') {
			if (atom->first) {
				insertatom(tokens, atom);
			}
			return tokens;
		}

		// Append to atom
		sq_push(atom, c);

		next:
			// Get next char from queue
			c = sq_pop(queue);
	}

	if (atom->first) {
		insertatom(tokens, atom);
	}

	return tokens;
}

// Creates a t_tree of the Scheme
t_tree *tokenize(char *scheme) {
	return tokenize_r(toqueue(scheme), 0);
}

// Helper method for toscheme
static void toscheme_r(t_tree *tokens, s_queue *queue) {
	if (tokens == NULL) {
		return;
	}
	if (tokens->atom[0] == '\0') {
		if (tokens->child) {
			toscheme_r(tokens->child, queue);
		}
		return;
	}
	if (tokens->child) {
		sq_push(queue, '(');
	}
	int i = 0;
	while (tokens->atom[i] != '\0') {
		sq_push(queue, tokens->atom[i]);
		i++;
	}
	if (tokens->next) {
		sq_push(queue, ' ');
		toscheme_r(tokens->next, queue);
	}
	if (tokens->child) {
		sq_push(queue, ' ');
		toscheme_r(tokens->child, queue);
		sq_push(queue, ')');
	}
}

// For debugging: takes in a t_tree and turns it back into Scheme
static char *toscheme(t_tree *tokens) {
	s_queue *queue = newqueue();
	toscheme_r(tokens, queue);
	return tostring(queue);
}

// For debugging
int main(void) {
	// Attempts to construct a tree for "(a (b c) d)"
	t_tree *t = tokenize("(eval (define tau 6.28))");
	printf(toscheme(t));
	wipe(t);

	/* s_queue *queue = toqueue("abc");
	char *c = tostring(queue);
	puts(c);
	char c[] = " ";
	while (c[0] != '\0') {
		c[0] = sq_pop(queue);
		c[1] = '\0';
		puts(c);
	}
	free(queue); */
	getchar(); 
}