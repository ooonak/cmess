#include <stdio.h>

enum response_type {DUMP, SECOND_CHANCE, MARRIAGE};
typedef struct {
  char* name;
  enum response_type type;
} response;

void dump(response r)
{
  printf("Dear %s,\n", r.name);
  puts("DUMPED");
}

void second_chance(response r)
{
  printf("Dear %s,\n", r.name);
  puts("SECOND CHANCE");
}

void marriage(response r)
{
  printf("Dear %s,\n", r.name);
  puts("MARRIAGE");
}

// Declare "replies" array that holds our functions.
void (*replies[])(response) = {dump, second_chance, marriage};

int main()
{
  // Declare an array of structs:
  response r[] = {
    {"Mike", DUMP}, {"Luis", SECOND_CHANCE},
    {"Matt", SECOND_CHANCE}, {"William", MARRIAGE}
  };
  int i;
  for (i = 0; i < 4; i++) {
    // Find type "r[i].type" and decide the right function in the array from the value.
    // Then call the function with the type parameter.
    (replies[r[i].type])(r[i]); 
   
/*    
 * Replace the switch statement with at loop that runs true our function array.
 *   switch(r[i].type) {
 *    case DUMP:
 *      dump(r[i]);
 *      break;
 *    case SECOND_CHANCE:
 *      second_chance(r[i]);
 *      break;
 *    default:
 *      marriage(r[i]);
 *  }
*/

  }
  return 0;
}
