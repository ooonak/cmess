#include <stdio.h>

// Is initialized '0'
int a;

int func()
{
  // Is not initialized
  int b;
  return b;
}
     
int main()
{
  // Is ?
  int c;

  printf("a: %d\n", a);
  printf("b: %d\n", func());
  printf("c: %d\n", c);
}
