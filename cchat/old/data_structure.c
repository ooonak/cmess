#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structure.h"

#define HASH_SIZE 101

/** Element for hash table and linked list */
/*
struct element {
        unsigned long id;
        struct element *table_next;
        struct element *table_prev;
        struct element *list_next;
        struct element *list_prev;
        char *data;
};
*/

/** Entry to hash table */
struct element *hash_table[HASH_SIZE];

/** Doubly linked list of nodes */
struct element *head_of_list;
struct element *tail_of_list;

/** Unique id for every element */
unsigned long id = 0;

/** Hash function: Returns calculated hash value */
unsigned hash(char *s)
{
        unsigned hashval;

        for (hashval = 0; *s != '\0'; s++)
                hashval = *s + 31 * hashval;

        return hashval % HASH_SIZE;
}

/** Add element to doubly linked list */
int add_to_list(struct element *element)
{
        if (head_of_list == NULL) {
                head_of_list = tail_of_list = element;
        } else {
                element->list_prev = tail_of_list;
                tail_of_list->list_next = element;
                tail_of_list = element;
        }

        return 0;
}

/** Remove element from doubly linked list */
void remove_from_list(struct element *element)
{
        if (head_of_list->list_next != NULL) {

                /* If first element */
                if (head_of_list == element) {
                        head_of_list = element->list_next;
                        if (head_of_list->list_prev != NULL)
                                head_of_list->list_prev = NULL;
                }

                /* If last element */
                else if (tail_of_list == element) {
                        tail_of_list = element->list_prev;
                        if (tail_of_list->list_prev != NULL)
                                tail_of_list->list_next = NULL;

                } else {
                        element->list_next->list_prev = element->list_prev;
                        element->list_prev->list_next = element->list_next;
                }

        } else
                head_of_list = tail_of_list = NULL;
}

/** Remove element from hash table */
void remove_from_hash_table(struct element *element)
{
        unsigned hashval = hash(element->data);

        /* If first element */
        if (element->list_prev == NULL) {
                hash_table[hashval] = element->table_next;
        }

        /* If last element */
        else if (element->table_next == NULL) {
                element->list_prev->table_next = NULL;

        } else {
                element->table_next->table_prev = element->list_prev;
                element->table_prev->table_next = element->table_next;
        }
}

/** Lookup node from string */
struct element *elookup(char *s)
{
        struct element *tmp;

        for (tmp = hash_table[hash(s)]; tmp != NULL; tmp = tmp->table_next)
                if (strcmp(s, tmp->data) == 0)
                        return tmp;

        return NULL;
}

/** Insert node into hash table and linked list */
struct element* einsert(char *s)
{
        unsigned hashval;
        struct element *tmp;

        if ((tmp = elookup(s)) == NULL) { /* No entry in table */
                tmp = (struct element*) malloc(sizeof(struct element));
                if (tmp == NULL || (tmp->data = strdup(s)) == NULL)
                        return NULL;

                hashval = hash(s);

                /* Add new element in front of list under hash */
                tmp->table_next = hash_table[hashval];
                if (hash_table[hashval] != NULL)
                        hash_table[hashval]->table_prev = tmp;

                hash_table[hashval] = tmp;
                tmp->id = id++;

        } else { /* Existing entry under that key, add to list */
                free ((void*) tmp->data);
                if ((tmp->data = strdup(s)) == NULL)
                        return NULL;
        }

        /* Insert into linked list */
        add_to_list(tmp);

        return tmp;
}

/* Remove node from hash table and linked list */
int eremove(struct element *tmp)
{
        /* Unlink */
        remove_from_list(tmp);
        remove_from_hash_table(tmp);

        /* Free memory */
        free(tmp->data);
        free(tmp);

        return 0;
}

/** Remove all elements in datastructure */
void eremove_all(void)
{
        struct element *tmp;

        for (tmp = head_of_list; tmp != NULL; tmp = tmp->list_next)
                eremove(tmp);
}

void eprint(struct element *tmp)
{
        printf("Element id: %lu hash key: %d data: %s\n",
                        tmp->id, hash(tmp->data), tmp->data);
}

void eprintall(void)
{
        struct element *tmp;

        for (tmp = head_of_list; tmp != NULL; tmp = tmp->list_next) {
                if (tmp != NULL)
                        eprint(tmp);
        }
}

void eprinttable(void)
{
        unsigned i;

        for (i = 0; i <  HASH_SIZE; i++) {
                if (hash_table[i] != NULL)
                        eprint(hash_table[i]);
        }
}
