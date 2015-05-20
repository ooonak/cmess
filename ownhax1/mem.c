#include <stdio.h>
#include <stdlib.h>

/* Declare an array of ten pointers to type int.
 * obtain memory on the heap with malloc for everyone
 * and assign a value to each.
 * Don't free them, debug with malloc()
 */

int main()
{
  int i, *no[10];

  for (i=0; i<10; i++) {
    no[i] = malloc(sizeof(int));
    no[i] = &i;
    printf("%d\n", *no[i]);
  }

  return 0;
}
