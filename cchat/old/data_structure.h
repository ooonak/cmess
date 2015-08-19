/** Element for hash table and linked list */
struct element {
        unsigned long id;
        struct element *table_next;
        struct element *table_prev;
        struct element *list_next;
        struct element *list_prev;
        char *data;
};

/** Lookup node from string */
struct element *elookup(char *s);

/** Insert node into hash table and linked list */
struct element* einsert(char *s);

/* Remove node from hash table and linked list */
int eremove(struct element *tmp);

/** Remove all elements in datastructure */
void eremove_all(void);

void eprint(struct element *tmp);

void eprintall(void);

void eprinttable(void);
