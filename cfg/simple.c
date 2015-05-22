#include <stdio.h>

int
main()
{
  int i=0;

  while (i<6) {
    if (i%2 == 0)
      puts("Even number");
    else
      puts("Uneven number");

    i++;
  }

  return 0;
}
