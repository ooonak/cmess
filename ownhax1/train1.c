#include <stdlib.h>
#include <stdio.h>

/* Global variables */
typedef enum { weight, 
               length 
} measure_opt; 

typedef union { int weight; 
                float length; 
} size_opt;

typedef struct fruit { char* name; 
                       size_opt size; 
                       measure_opt measure; 
} fruit_alias;

int main()
{
  /* Assing values to our struct */
  fruit_alias strawberry = { "Jordbaer", .size.weight=10, weight };
  fruit_alias orange = { "Appelsin", .size.length=250.5, length };

  printf("Navn: %s %i\n", strawberry.name, strawberry.size.weight);
  printf("Navn: %s %2.2f\n", orange.name, orange.size.length);

  return 0;
}
