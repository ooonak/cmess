#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
  char *a = "Hello";
  char *b = "World";

  char *c = malloc(sizeof(char)*100);

  strcpy(c, a);
  strcat(c, b);

  printf("%s\n", c);

  return 0;
}
