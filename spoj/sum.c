/* 
 *  * My first c program.
 *   */

#import <stdio.h>
#import <stdlib.h>
int main() 
{
  int a;
  int b;

  puts("Enter a: ");
  scanf("%i", &a);
  puts("Enter b: ");
  scanf("%i", &b);

  printf("The sum, a+b: %i\n", a+b);

  return 0;
}
