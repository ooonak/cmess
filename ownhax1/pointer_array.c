#include <stdio.h>
#include <stdlib.h>

const int NO = 5;

int main()
{
  /* Array of pointers */
  int *int_array_ptr = malloc(NO * sizeof(int));

  int i;

  for (; i<NO; i++) {
    int_array_ptr[i] = malloc(sizeof(int));
    int_array_ptr[i] = i;
    printf("%d, ", int_array_ptr[i]);
  }
  puts("\n");


  /* Array of ints */
  int int_array[10];
  int i;

  for (; i<10; i++) {
    int_array[i] = i;
    printf("%d, ", int_array[i]);
  }
  puts("\n");


  return 0;
}
