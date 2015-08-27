#include <stdio.h>
#include <string.h>
#include "data_structure.h"

int main()
{
        char *node = "10.0.0.17 Bertram";

        einsert("10.0.0.13 Casper");
        einsert("10.0.0.13 Casper");
        einsert("10.0.0.13 Casper");
        einsert("10.1.0.13 Casper");
        einsert("192.168.2.13 Maria");
        einsert(node);
        einsert("10.0.0.19 Harald");

        printf("\nPrint list:\n");
        eprintall();

        printf("\nPrint table:\n");
        eprinttable();

        printf("\nPrint lookup:\n");

        struct element *tmp = elookup("10.0.0.17 Bertram");
        if (tmp != NULL)
                eprint(tmp);
        else
                printf("Found nothing\n");

        puts("\n === REMOVE === ");

        eremove_all();

        printf("\nPrint list:\n");
        eprintall();

        printf("\nPrint table:\n");
        eprinttable();

        return 0;
}
