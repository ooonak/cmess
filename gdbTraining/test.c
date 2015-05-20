#include <stdlib.h>
#include <stdio.h>

void function2()
{
  char a = 'A';
  char b = 'B';

  int c = (int) a + (int) b;
  printf("c: %d\n", c);
}

void function1(int i, int count)
{
  printf("i: %d, count: %d\n", i, count);

  if (i+count < 10)
    function2();
}

int main()
{
  int i, count = 5;

  for (i=0; i<count; i++) {
    function1(i, count);
  }

  return 0;
}
