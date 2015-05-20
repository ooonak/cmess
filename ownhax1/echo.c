#include <stdio.h>
#include <string.h>

/*
 * Understand pointers.
 */

//char *string = "Hello World!";
char string[20];

int main()
{
  puts("Write your text, max 19 characters: ");
  scanf("%19[^\n]", string);

  // Print every char in the "string".
  int i;
  for (i = 0; i < 19; i++) {
    printf("| %c ", string[i]);
  }
  printf(" |\n\n");

  // Make a pointer variable that holds the address of the first char in the array.
  char *address = string;
  printf("The first char in the array is stored at: %p\n", address);
  printf("The first char in the array is stored at: %p\n", &string[0]);
  printf("The first char in the array is stored at: %p\n\n", string);

  // Now show what's stored at address + 9.
  printf("The first char in the array is stored at: %p\n", address+8);
  printf("The ninth char in the array is stored at: %p\n", &string[8]);
  printf("The ninth char in the array is stored at: %p\n", string+8);
  printf("Value of address: %c\n\n", *string+8);

  int length = sizeof(string) / sizeof(string[0]);
  printf("Size of the array: %i\n", length);
  printf("Size of the input: %lu\n", strlen(string));


  return 0;
}
