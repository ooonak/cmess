#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

/**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:        the pointer to the member.
 * @type:       the type of the container struct this is embedded in.
 * @member:     the name of the member within the struct.
 *
 */
#define container_of(ptr, type, member) ({ \
        const typeof( ((type *)0)->member ) *__mptr = (ptr); \
        (type *)( (char *)__mptr - offsetof(type,member) );})

struct inner {
  int i;
};

struct outer {
  struct inner *case_ptr;
  struct inner case_no_ptr;
};

int main()
{
  /* New inner struct */
  struct inner *case_ptr = (struct inner*) malloc(sizeof(struct inner));

  struct inner case_no_ptr = { 123 };

  /* New outer struct */
  struct outer *out = (struct outer*) malloc(sizeof(struct outer));
  out->case_ptr = case_ptr;
  memcpy(&out->case_no_ptr, &case_no_ptr, sizeof(struct inner));

  /* Print address of outer struct (the one that we wish to find) */
  printf("Address of outer struct: %p\n", out);

  /* Can we given the inner struct, find address of outer struct */
  struct outer *tmp;
  tmp = (struct outer*) container_of(&(out->case_no_ptr), struct outer, case_no_ptr);
  printf("Address of outer struct from 'container_of' 1: %p\n", tmp);

  /* This is not usefull, since we have to know the pointers address,
   * the 'element' is the pointer, not the inner struct
   */
  tmp = container_of(&(out->case_ptr), struct outer, case_ptr);
  printf("Address of outer struct from 'container_of' 2: %p\n", tmp);

  return 0;
}
