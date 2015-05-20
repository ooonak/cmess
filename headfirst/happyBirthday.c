/* How do you update a struct?
 * Chapter 5, p. 236.
 */
#include <stdio.h>

typedef struct {
  const char *name;
  const char *species;
  int age;
} turtle;

/* Error prone version. t.age is a local variable, only inside this function.
void happy_birthday(turtle t)
{
  t.age = t.age + 1;
  printf("Happy Brirthday %s! You are now %i years old!\n",
      t.name, t.age);
} */

// Here we goe. (*t).age and t->age is the same thing, the age field in the struct that t points to.
void happy_birthday(turtle *a)
{
  a->age = a->age + 1;
  printf("Happy Brirthday %s! You are now %i years old!\n",
      a->name, a->age);
}

int main()
{
  turtle myrtle = {"Myrtle", "Leatherback sea turtle", 99};
  happy_birthday(&myrtle);
  printf("%s's age is now %i\n", myrtle.name, myrtle.age);
}
