#include "tokens_internal.h"
#include "util.h"
#include <string.h>

// Functions for writing to a tree_list.
void newtreelist(struct t_list *tl) {
    tl->tree = malloc(sizeof(struct t_tree));
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
    tl->tree[tl->ptr++] = *t; // is this buggy?
}

void wipetreelist(struct t_list *tl) {
    free(tl->tree);
    tl->tree = NULL;
    tl->ptr = tl->cap = 0;
}

void assign(struct t_tree *t, struct t_list *tl) {
    t->children = tl;
}

// Finds the appropriate closing parens.
char *closing_parens(char *scheme, int start) {
    int end = start;
    int stack = 0;
    while (end < strlen(scheme)) {
        char c = scheme[end];
        if (c == '(') {
            stack++;
        } else if (c == ')') {
            if (stack == 0) {
                char *scpy;
                strncpy(scpy, scheme + start, end);
                return scpy;
            } else {
                stack--;
            }
        }
        end++;
    }
    char *msg;
    sprintf(msg, "Couldn't find closing parens in malformed token %s", scheme);
    err(msg);
}

// Creates an atom with the string passed to it
struct atom newatom(char *scheme) {
    struct atom atm;
    atm.a = scheme;
    return atm;
}

// Creates a token_tree from a string of Scheme syntax.
struct t_tree tokenize(char *scheme) {
    // *scheme will be of the form ((a b) (c d e) (f g) h)
    
    struct t_tree tree;
    struct t_list ch;
    newtreelist(&ch);

    int i = 0;
    int j = 0;
    char curr_atom[ATOM_LENGTH];
    while (i < strlen(scheme)) {
        char c = scheme[i];
        if (c == '(') {
            char *curr_branch = closing_parens(scheme, i);
            i += strlen(curr_branch);
            struct t_tree ch_branch = tokenize(curr_branch);
            addtreelist(&ch, &ch_branch);
        } else if (c == ' ') {
            if (strlen(curr_atom) == 0) {
                continue;
            }
            // use the current atom
            struct atom atm = newatom(curr_atom);
            if (tree.parent == NULL) {
                tree.parent = &atm;
            } else {
                struct t_tree t;
                t.parent = &atm;
            }
            strcpy(curr_atom, ""); // wipe the current atom
            i++;
        } else {
            curr_atom[j] = c;
            i++;
            j++;
        }
    }
    assign(&tree, &ch);

    return tree;
}

int main() {
    printf("Going to tokenize");
    tokenize("(define f 10)");
    return 0;
}
