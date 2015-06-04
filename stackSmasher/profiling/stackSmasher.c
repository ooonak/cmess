/*
 * Testing the stack smashing protection in gcc and clang.
 */

#include <stdio.h>
#include <string.h>

#define SIZE 4

void cpyPrint(char *str)
{
  char buf1[SIZE];

  /* Ouch stack corruption caused by buffer overflow */
  strcpy(buf1, str);
  printf("%s\n", buf1);
}

int main()
{
  /* Declare a char array way longer than three */
  char string[] = "The";

  cpyPrint(string);

  //printf("END");

  return 0;
}
