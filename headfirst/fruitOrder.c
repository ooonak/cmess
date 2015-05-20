/*
 * Chapter 5, p. 256.
 */

#include <stdio.h>

typedef enum {
  COUNT, POUNDS, PINTS
} unit_of_measure;

typedef union {
  short count;
  float weight;
  float volume;
} quantity;

typedef struct {
  const char *name;
  const char *country;
  // Below a union. Store different datatypes in the same union, lets us reuse memory space.
  quantity amount;
  // We use an enum to remember which datatype we fetch from the "union" memory space.
  unit_of_measure units;
} fruit_order;

void display(fruit_order order)
{
  printf("This order contains ");
  if (order.units == PINTS)
    printf("%2.2f pints of %s\n", order.amount.volume, order.name);
  else if (order.units == POUNDS)
    printf("%2.2f lbs of %s\n", order.amount.weight, order.name);
  else
    printf("%i %s\n", order.amount.count, order.name);
}

int main()
{
  fruit_order apples = {"Apples", "England", .amount.count=144, COUNT};
  fruit_order strawberries = {"Strawberries", "Spain", .amount.weight=17.6, POUNDS};
  fruit_order oj = {"Orange juice", "U.S.A.", .amount.volume=10.5, PINTS};

  display(apples);
  display(strawberries);
  display(oj);

  return 0;
}
