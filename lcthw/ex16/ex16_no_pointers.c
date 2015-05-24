#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person {
    char *name;
    int age;
    int height;
    int weight;
};

struct Person persons[2];

void Person_create(int index, char* name, int age, int height, int weight)
{
    persons[index].name = name;
    persons[index].age = age;
    persons[index].height = height;
    persons[index].weight = weight;
}

void Person_print(struct Person who)
{
    printf("Name: %s\n", who.name);
    printf("\tAge: %d\n", who.age);
    printf("\tHeight: %d\n", who.height);
    printf("\tWeight: %d\n", who.weight);
}

int main(int argc, char *argv[])
{
    // make two people structures
    Person_create(0, "Joe Alex", 32, 64, 140);
    Person_create(1, "Frank Blank", 20, 72, 180);

    // print them out and where they are in memory
    printf("Joe is at memory location %p:\n", &persons[0]);
    Person_print(persons[0]);

    printf("Frank is at memory location %p:\n", &persons[1]);
    Person_print(persons[1]);

    // make everyone age 20 years and print them again
    persons[0].age += 20;
    persons[0].height -= 2;
    persons[0].weight += 40;
    Person_print(persons[0]);

    persons[1].age += 20;
    persons[1].weight += 20;
    Person_print(persons[1]);

    return 0;
}
