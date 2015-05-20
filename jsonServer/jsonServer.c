/*
 *  2015-02-06 Casper, v. 0.01
 *  Given a sweep struct, return data about mine coordinates in
 *  JsonRPC 2.0 netstring encoding.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LENGTH 480

/* A mine is defined by it's coordinates */
typedef struct mine {
  double x;
  double y;
} mine_t;

/* Sweep holds every mine found, as a mine_t pointer the total no of mines */
typedef struct sweep {
  int no;
  mine_t *mine_p;
} sweep_t;

/* Return digits in int */
int dl(int in)
{
  int i=0;
  while(in > 0) {
    in = in/10;
    i++;
  }
  return i;
}

/* Encode as netstring */
char* toNetString(char* jsonString)
{
  /* Find length of jsonString */
  int i = 0;
  while( *(jsonString+i) != '\0') {
    i++;
  };
  /* Calculate length of entire string: no:json */
  i = i + 2 + dl(i);
  char* tmpString = malloc(sizeof(char)*i);
  /* Concatenate netstring and return */
  sprintf(tmpString, "%d", i);
  strcat(tmpString, ":\0");
  strcat(tmpString, jsonString);

  return tmpString;
}

/* Make JsonRPC 2.0 encoded string out of struct */
char* toJson(sweep_t *sweep)
{
  int i, no=sweep->no, size = LENGTH;
  char *jsonString = malloc(sizeof(char[size]));
  char start[] = "{\"jsonrpc\": \"2.0\", ";
  char end[] = "}";
  char temp[8];

  strcpy(jsonString, start);
  strcat(jsonString, "\"no\": \0");

  sprintf(temp, "%2d", no);
  strcat(jsonString, temp);
  strcat(jsonString, ": \0");

  for (i=0; i<no; i++) {
    strcat(jsonString, "{");
    strcat(jsonString, "\"x\": ");
    sprintf(temp, "%3.2f", sweep->mine_p[i].x);
    strcat(jsonString, temp);
    strcat(jsonString, ", \"y\": ");
    sprintf(temp, "%3.2f", sweep->mine_p[i].y);
    strcat(jsonString, temp);
    strcat(jsonString, "}\0");

    if (i < no-1)
      strcat(jsonString, ", ");

    /* Check length of string, realloc twice the size if space is used */
    if (strlen(jsonString) > size*0.90) {
      size = 2*size;
      printf("realloc() size is now: %d\n", size);
      if (!(jsonString = realloc(jsonString, sizeof(char[size]))))
        break;
    }
  }

  strcat(jsonString, end);

  return jsonString;
}

int main()
{
  /* Found three mines in sweep 1 */
  int i, no = 10;
  mine_t c = { -412.55, -929.15 };

  mine_t *tmpMines = malloc(sizeof(mine_t)*no);

  for (i=0; i<no; i++)
    tmpMines[i] = c;

  sweep_t *sweep1 = malloc(sizeof(sweep_t));
  sweep1->no = no;
  sweep1->mine_p = tmpMines;

  /* Convert to Json */
  char *jsonString = toJson(sweep1);

  /* Convert to netstring */
  char *netString = toNetString(jsonString);

  /* Print */
  printf("jsonNetString: \"%s\"", netString);

  free(sweep1);
  free(tmpMines);
  free(jsonString);
  free(netString);

  return 0;
}
