/*
 * Write last 20 lines of file to std out and append second argument to it
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 100

FILE *file;
char *buffer;

void showFile()
{
  while (1) {
    if (fgets(buffer, sizeof(buffer), file) == NULL) break;
      printf("%s", buffer);
  }
}

void appendFile(char *string)
{
  printf("%s", string);
  if (!(fprintf(file, "%s\n", string)))
     puts("Error, writing to file.");
}

int main(int argc, char** argv)
{
  if (argc > 1) {

    /* Open file */
    if ((file = fopen(argv[1], "a+"))) {

      buffer = malloc(sizeof(char[BUF_SIZE]));

      showFile();

      if (argc > 2) {
        int i;
        for (i=2; i<argc; i++) {
          appendFile(argv[i]);
        }
      }

    } else {
      puts("Error, could not access file.\n");
    }

  free(buffer);
  fclose(file);

  } else
    puts("Usage: appendToFile <filename> <string to append>\n");

  return 0;
}
