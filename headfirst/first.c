/* 
 * My first c program.
 */

#import <stdio.h>
#import <stdlib.h>
int main() 
{
  int selector = 1;
  puts("Welcome, hit 0 to quit\n");
  while (selector != 0) {
    puts("Enter your age: ");
    // hi: short int
    scanf("%hi", & selector);
    switch(selector) {
      case 21:
        puts("You may drink");
      case 16:
        puts("You may vote");
        break;
      case 0:
        continue;
      default:
        printf("You entered: %i\n", selector);
    }
  }
  return 0;
}
