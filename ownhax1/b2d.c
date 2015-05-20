#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
  int i;

  if (argc > 1) {
    for (i=1; i<argc; i++) {
      long val = strtol(argv[i], 0, 2);
      printf("Decimal: %ld\t Hexadecimal: %#06lx\t Binary: %s\n", val, val, argv[i]);
    }
  }

  return 0;
}
