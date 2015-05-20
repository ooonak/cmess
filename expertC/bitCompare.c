#include <stdio.h>
#include <stdlib.h>

int binCompare(int *a, int *b)
{
  if (!(*a ^ *b))
    return 1;
  else
    return 0;
}

int main(int argc, char *argv[])
{
  int a, b;

  if (argc == 3) {
    a = atoi(argv[1]);
    b = atoi(argv[2]);

    if (binCompare(&a, &b))
      puts("Values equals, bitwise compared.");
    else
      puts("Values are not equal, bitwise compared.");

  } else {
    puts("You have to enter two arguments, the two number you wish to compare");

  }
  return 0;
}
