/*
 * 21-05-2015
 * Playing with callback functions by function pointers
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* (*callback_fn)(char* a, char* b);

char*
a_first(char* a ,char* b)
{
  char* result = malloc(strlen(a)+strlen(b)+1);

  strcpy(result, a);
  strcat(result, b);

  return result;
}

char*
b_first(char* a ,char* b)
{
  char* result = malloc(strlen(a)+strlen(b)+1);

  strcpy(result, b);
  strcat(result, a);

  return result;
}

void
repeat(int no, char* a, char* b, callback_fn fn)
{
  int i;

  for (i=0; i<no; i++) {
    printf("%s", fn(a, b));
  }
  printf("\n");

}

int main()
{
  int no = 3;
  char* a = "ja ";
  char* b = "NEJ ";

  printf("Print a first:\n");

  /* Print a first, using function pointer */
  repeat(no, a, b, a_first);

  printf("Print b first:\n");

  /* Print b first, using function pointer */
  repeat(no, a, b, b_first);

  return 0;
}
