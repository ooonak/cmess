/* From chapter 5, p. 234 */
#include <stdio.h>

// typedef gives us alias "equipment" for struct.
typedef struct {
  float tank_capacity;
  int tank_psi;
  // const char * - means pass literal string.
  const char *suit_material;
} equipment;

// Nested structs "equipment kit".
typedef struct scuba {
  const char *name;
  equipment kit;
} diver;

void badge(diver d) 
{
  printf("Name: %s Tank: %2.2f (%i) Suit: %s\n",
      d.name, d.kit.tank_capacity, d.kit.tank_psi, d.kit.suit_material);
}

int main()
{
  diver randy = {"Randy", {5.5, 3500, "Neoprene"}};
  badge(randy);
  return 0;
}
