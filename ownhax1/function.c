#include <stdio.h>

/*
 *
 */

void outer(char *msg)
//void outer(char msg[])
{
  printf("%s\n", msg);
}

void outer2(int* input)
{
  printf("
int main()
{
  char msg[] = "Hello World!";
  outer(msg);
  outer("Casper");

  return 0;
}
