#include "tokens_internal.h"
#include "util.h"
#include <string.h>

// Functions for writing to a tree_list.
void newtreelist(struct t_list *tl) {
    tl->tree = malloc(sizeof(struct t_tree)); // Write access violation?
    if (tl->tree == NULL) {
        err("Memory allocation failed while trying to create a tree list");
        return;
    }
    tl->ptr = 0;
    tl->cap = RESIZE_FACTOR;
}

void addtreelist(struct t_list *tl, struct t_tree *t) {
    if (tl->ptr == tl->cap) {
        tl->cap *= RESIZE_FACTOR;
        tl->tree = realloc(tl->tree, tl->cap * sizeof(struct t_tree));
        if (tl->tree == NULL) {
            err("Memory allocation failed while trying to write to a tree list");
            return;
        }
    }
    tl->tree[tl->ptr++] = *t;
}

void wipetreelist(struct t_list *tl) {
    free(tl->tree);
    tl->tree = NULL;
    tl->ptr = tl->cap = 0;
}

void assignch(struct t_tree *t, struct t_list *tl) {
    t->children = tl;
}

// Creates an atom with the string passed to it in the tree
void setatom(char *scheme, int len, struct t_tree *t) {
	t->parent = malloc(sizeof(struct atom));
	if (t->parent == NULL) {
		err("Memory allocation failed while writing to atom");
		return;
	}
	t->parent->a = malloc(len + 1);
	if (t->parent->a == NULL) {
		err("Memory allocation failed while writing to atom string");
		return;
	}
	strcpy(t->parent->a, scheme);
	t->parent->a[len] = '\0';
}

// Destroys everything in a t_tree
void wipetree(struct t_tree *tree) {
	wipetreelist(tree->children);
	free(tree->parent);
	free(tree->parent->a);
}

// Creates a t_tree from a string of Scheme syntax.
// Returns the index of the final char, for recursive purposes.
unsigned tokenize_int(char *scheme, struct t_tree *tree, unsigned l_end, unsigned r_end) {
	char *atom[ATOM_LENGTH];
	unsigned atm_ptr = 0;
	while (l_end < r_end) {
		switch (scheme[l_end]) {
		case '(': {
			struct t_tree *child = malloc(sizeof(struct t_tree));
			if (child == NULL) {
				err("Failed to write child tree to memory");
				return;
			}
			l_end = tokenize_int(scheme, child, l_end, r_end);
			addtreelist(&(tree->children), child);
			free(child); // could be buggy
			// can I free this memory since it's malloced in addtreelist()?
			break;
		}
		case ')': {
			return r_end;
		}
		case ' ': {
			if (atm_ptr == 0) {
				break;
			}
			if (tree->parent == NULL) {
				setatom(atom, atm_ptr, tree);
			}
			else { // put the atom as a child
				struct t_tree *child = malloc(sizeof(struct t_tree));
				if (child == NULL) {
					err("Failed to write child tree to memory");
					return;
				}
				setatom(atom, atm_ptr, child);
				addtreelist(&(tree->children), child);
				free(child); // could be buggy
				strcpy(atom, "\0"); // wipe the current atom
				atm_ptr = 0;
			}
			l_end++;
			break;
		}
		default: {
			atom[atm_ptr] = scheme[l_end];
			atm_ptr++;
			l_end++;
			break;
		}
		}
	}

	return r_end;
}

// Wrapper for tokenize_int
struct t_tree *tokenize(char *scheme) {
	struct t_tree *tokens = malloc(sizeof(struct t_tree));
	if (tokens == NULL) {
		err("Failed to write tree to memory");
		return;
	}
	newtreelist(tokens->children);
	tokenize_int(scheme, tokens, 0, strlen(scheme));
	return tokens;
}

// Debugging
void printt_internal(struct t_tree *t, char *indent) {
	printf(indent);
	printf(t->parent->a); // exception?
	strcat(indent, "\t");
	struct t_list *ch = t->children;
	for (int i = 0; i < ch->ptr; i++) {
		if (ch == &NULL_LIST) {
			return;
		}
		struct t_tree tree = ch->tree[i];
		printt_internal(&tree, indent);
	}
}

void printt(struct t_tree *t) {
	char indent[20];
	//indent[0] = '\0';
	printt_internal(t, indent);
}

int main() {
	struct t_tree *t = tokenize("d");
    printt(t);
	wipetree(t);
	getchar();
    return 0;
}
