#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 101

/** Chat node */
struct node {
        unsigned long id;
        char ip4[IP_FIELD_SIZE];
        char name[NAME_FIELD_SIZE];
        char time_out;
};

/** Node for hash table */
struct element {
        struct hash_node *table_next;
        struct hash_node *table_prev;
        struct hast_node *list_next;
        struct hast_node *list_prev;
        struct data data;
};

/** Entry to hash table */
struct hash_node *hash_table[HASH_SIZE];

/** Doubly linked list of nodes */
struct node *head_of_list;
struct node *tail_of_list;

unsigned long id = 0;

/**
 * Hash function:
 * Concatenate the last three chars from ip with name and.
 * Returns calculated hash value
 */
unsigned hash(char *ip4, char *name)
{
       char tmp[3 + strlen(name) + 1];
       strncpy(tmp, &ip4[strlen(ip4) - 3], 3);
       strcat(tmp, name);

       unsigned hashval;

       for (hashval = 0; *name != '\0'; name++)
               hashval = *name + 31 * hashval;

       return hashval % HASH_SIZE;
}

/** Insert node into hash table and linked list */
int insert_node(char *ip4, char *name)
{
        /* Obtain write lock */

        /* Insert into hash table */
        unsigned hashval = hash(ip4 , name);
        struct hash_node *tmp_ptr = hash_table[hashval];
        for (; tmp_ptr != NULL; tmp_ptr = tmp_ptr->next);
        tmp_ptr = (struct hash_node*) malloc(sizeof(struct hash_node));

        /* Insert into linked list */
        if (tail_of_list == NULL)
                tail_of_list = head_of_list = &(tmp_ptr->node);
        else {
                tail_of_list->next = &(tmp_ptr->node);
                tmp_ptr->node.prev = tail_of_list;
                tail_of_list = &(tmp_ptr->node);
        }

        tmp_ptr->next = NULL;
        tmp_ptr->node.id = id++;

        strncpy(tmp_ptr->node.ip4, ip4, IP_FIELD_SIZE);
        strncpy(tmp_ptr->node.name, name, NAME_FIELD_SIZE);

        return 0;
}

/* Remove node from hash table and linked list */
int remove_node(char *ip4, char *name)
{

        return 0;
}

/** Lookup node from its ip4 and name */
int lookup_node(char *ip4, char *name)
{

        return 0;
}

/** Lookup node from its id */
int lookup_node_by_id(unsigned long id)
{

        return 0;
}

void print_nodes(void)
{
        struct node *ptr;

        for (ptr = head_of_list; ptr != NULL; ptr = ptr->next) {
                printf("Node id %lu, hashval %d, ip %s, name %s\n",
                                ptr->id, hash(ptr->ip4, ptr->name),
                                ptr->ip4, ptr->name);
        }
}

int main()
{
        insert_node("10.0.0.13", "Casper");
        insert_node("192.168.2.13", "Maria");
        insert_node("10.0.0.17", "Bertram");
        insert_node("10.0.0.19", "Harald");
        insert_node("10.0.0.13", "Casper");

        print_nodes();

        return 0;
}
