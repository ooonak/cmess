#include <stdio.h>
#include <stdlib.h>

typedef struct _sizeStruct {
  int size;
} sizeStruct;

int main()
{
  int NO = 10;
  /* A dynamically allocated array of pointers, malloc will return 
   * a pointer to a block of memory. 
   */
  sizeStruct **array = malloc(NO * sizeof(sizeStruct *));
  int i;
  for (; i<NO; i++) {
    /* create new struct sizeStruct */
    array[i] = malloc(sizeof(sizeStruct));

    /* set up its members */
    array[i]->size = i;
    printf("%d, ", array[i]->size); 
  }
  puts("\n");

  return 0;
}
