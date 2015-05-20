#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  unsigned int a=atoi(argv[1]), b=atoi(argv[2]);

  printf("& %d\n", a & b);
  printf("| %d\n", a | b);
  printf("<< %d\n", a << 1);
  printf(">> %d\n", a >> 1);
  printf("^ %d\n", a ^ b);

}
