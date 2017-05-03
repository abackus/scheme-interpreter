# define ATOM_LENGTH 16
# define NULL_ATOM "oudhn9s8afhwq34"

// An atom is the building block of a Scheme token.
// Atoms are any token without () in it.
struct atom {
    char *a;
};
