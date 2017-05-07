
    // *scheme will be of the form ((a b) (c d e) (f g) h)

	struct t_tree tree = {
		.parent = &NULL_ATOM,
	};
    struct t_list ch;
    newtreelist(&ch);

    int i = 0;
    int j = 0;
    char curr_atom[ATOM_LENGTH];
	strcpy(curr_atom, ""); // clear mem

    while (i < strlen(scheme)) {
        char c = scheme[i];
        if (c == '(') {
            char *curr_branch = closeparens(scheme, i);
            i += strlen(curr_branch);
            struct t_tree ch_branch = tokenize(curr_branch);
            addtreelist(&ch, &ch_branch);
        } else if (c == ' ') {
            if (strlen(curr_atom) == 0) {
                continue;
            }
            struct atom *atm = newatom(curr_atom, j);
            if (tree.parent == &NULL_ATOM) {
                tree.parent = atm;
            } else {
                struct t_tree t;
                t.parent = &atm;
				addtreelist(&ch, &t);
            }
            i++;
			j = 0;
        } else {
            curr_atom[j] = c;
            i++;
            j++;
        }
    }

	if (strlen(curr_atom) > 0) {
		struct atom atm = *newatom(curr_atom, j);
		if (tree.parent == &NULL_ATOM) {
			tree.parent = &atm;
		}
		else {
			struct t_tree t;
			t.parent = &atm;
			addtreelist(&ch, &t);
		}
	}

    assignch(&tree, &ch);

    return tree;
}