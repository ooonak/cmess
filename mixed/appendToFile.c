/*
 * Write last 20 lines of file to std out and append second argument to it
 */

#include <stdio.h>

FILE *file;

void showFile()
{

}

void appendFile()
{

}

int main(int argc, char** argv)
{
  if (argc > 1) {

    /* Open file */
    if ((file = fopen(argv[1], "a+"))) {
      showFile();
      appendFile();
    } else {
      puts("Error, could not access file.\n");
    }

  fclose(file);

  } else
    puts("Usage: appendToFile <filename> <string to append>\n");

  return 0;
}
