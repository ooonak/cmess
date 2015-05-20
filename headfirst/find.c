#include <stdio.h>
#include <string.h>

int NUM_ADS = 7;
char *ADS[] = {
  "William: SBM GSOH likes sports, TV, dining",
  "Matt: SWM NS likes art, movies, theater",
  "Luis: SLM ND likes books, theater, art",
  "Mike: DWM DS likes trucks, sports and bieber",
  "Peter: SAM likes chess, working out and art",
  "Josh: SJM likes sports, movies and theater",
  "Jed: DBM likes theater, books and dining"
  };

int sports_no_bieber(char *s)
{
  return strstr(s, "sports") && !strstr(s, "bieber");
}

int sports_or_workout(char *s)
{
  return strstr(s, "sports") || strstr(s, "working out");
}

int ns_theater(char *s)
{
  return strstr(s, "NS") && strstr(s, "theater");
}

int arts_theater_or_dining(char *s)
{
  return strstr(s, "arts") || strstr(s, "theater") || strstr(s, "dining");
}

/* 
 *  Variadic functions:
 *  We pass a pointer to a function as parameter to find.
 *  The syntax: (*match)(char*)
 *  *match is a pointer to a function
 *  char* is the parameter for the function
 */
void find(int(*match)(char*))
{
  int i;
  puts("Search results:");
  puts("---------------");
  for (i = 0; i < NUM_ADS; i++) {
    // Here does "find" call the function that that match points to with argument ADS[i] (char*)
    if (match(ADS[i])) {
      printf("%s\n", ADS[i]);
    }
  }
  puts("---------------");
}

int main()
{
  // Call function "find" with function "sports_no_bieber" as parameter.
  find(sports_no_bieber);
  find(sports_or_workout);
  find(ns_theater);
  find(arts_theater_or_dining);
  return 0;
}
