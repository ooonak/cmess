/**
 * Find subsequence in string in linear time
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
        if (argc != 3) {
                printf("You have to give me two arguments: <cmd> <string> <subsequence>\n");
                return 0;
        }

        char* array;
        char* subsequence;

        array = (char *) malloc(strlen(argv[1])+1);
        subsequence = (char *) malloc(strlen(argv[2])+1);

        strcpy(array, argv[1]);
        strcpy(subsequence, argv[2]);

        unsigned int i, j = 0;

        for (i = 0; i < strlen(array); i++) {
                if (array[i] == subsequence[j])
                        j++;
        }

        if (j == strlen(subsequence))
                printf("Found\n");
        else
                printf("Not found\n");

        return 0;
}
