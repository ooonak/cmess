#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define STACKSIZE 10

int top=-1;
int stack[STACKSIZE];

#define push(i) stack[++top]=i
#define pop() stack[top--]

char input[80];

void popall()
{
  while(top != -1) {
    printf("[%d] = ", top);
    int tmp = pop();
    printf("%d\n", tmp);
  }
}

char* nextLine()
{
  fgets(input, 79, stdin);
  return input;
}

int main()
{
  char *token;
           
  /* get the first token */
  token = strtok(nextLine(), " ");
              
  /* walk through other tokens */
  while( token != NULL ) {
    push(atoi(token));
    token = strtok(NULL, " ");
  }

  popall();

  return 0;
}
