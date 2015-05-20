#include <stdio.h>

int array[] = { 1, 2, 4, 5, 7, -76, 0 };

#define TOTAL_ELEMENTS (sizeof(array) / sizeof(array[0]))

int main()
{
  int d = -1, x;

  // Does not evaluate cause TOTAL_ELEMENTS is unsigned, could be fixed by typecast.
  if (d <= TOTAL_ELEMENTS - 2)
    x = array[d+1];
 
  printf("x: %i\n", x);
}
