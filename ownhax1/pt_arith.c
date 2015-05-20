#include <stdio.h>
#include <stdlib.h>

/*
 * Loop thrue an array of pointers to structs with array index
 * and pointer arithmetics
 */

int no = 5;

typedef struct _data { char* value0; int value1; } data_t;

/* Generate array with pointers to ten structs of type _data */
static data_t** initialize()
{
  data_t **data_ptr = malloc(no * sizeof(data_t));
  
  /* Declare ten structs and asign to pointers in array */
  int i;
  for (i=0; i<no; i++) {
    data_ptr[i] = malloc(sizeof(data_t));
    data_ptr[i]->value0 = "value0";
    data_ptr[i]->value1 = i;
  }    

  return data_ptr;
}  

/* Free memory again */
void free_mem(data_t** data)
{
  int i;
  for (i=0; i<no; i++) {
    free(data[i]);
  }
  free(data);
}

/* Print function */
static void print(char* method, char* value0, int value1, data_t* address)
{
  printf("%s: %s, %d, %p\n", method, value0, value1, address);
}

/* Loop thrue array by index */
static void by_index(data_t** data)
{
  printf("%p\n", data);
  int i;
  for (i=0; i<no; i++) {
    print("by_index", data[i]->value0, data[i]->value1, data[i]);
  }  
  printf("\n");
}

/* Loop thrue array by pointer arithmetic */
void by_pt_arith(data_t** data)
{
  data_t* data_ptr;

  /* Remember that data[i] == *(data+i)
   * Because data is a pointer to an array of pointers, we have to
   * dereference it with the *, that gives us the pointer (address)
   * to the first struct
   */ 
  for (data_ptr = *data; data_ptr < (*data+no); data_ptr++) {
    print("by_pt_arith:", data_ptr->value0, data_ptr->value1, data_ptr);
  }
  
  printf("\n");
}

int main()
{
  /* Declaration */
  data_t** data;    

  /* Asignment */
  data = initialize();

  by_index(data);
  by_pt_arith(data);

//  free_mem(data);
}  
