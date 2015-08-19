#include <stdio.h>
#include <string.h>
#include "data_structure.h"

int main()
{
        int i, j=3;

        for (i=1; i<=j; i++) {
                printf("===== RUNNING TEST %d of %d =====\n", i, j);

                printf("Insert 4 elements\n");

                insert_element("Casper", "192.168.0.1");
                insert_element("Maria", "192.168.0.1");
                insert_element("Bertram", "192.168.0.1");
                insert_element("Harald", "192.168.0.1");

                printf("Print list\n");
                eprintall();

                printf("Clean up\n");
                clean_up();

                printf("Print list (should now be empty)\n");
                eprintall();

                printf("\nInsert 2 elements\n");

                insert_element("Bertram", "192.168.0.1");
                insert_element("Harald", "192.168.0.1");

                printf("Print list\n");
                eprintall();

                printf("Clean up\n");
                clean_up();

                printf("Print list (should now be empty)\n");
                eprintall();
        }

        return 0;
}
