#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NEW(T, N) Object_new(sizeof(T), T##Proto, N)
#define _(N) proto.N

typedef struct {
  char *description;
  int (*init)(void *self);
  void (*descripe)(void *self);
  void (*destroy)(void *self);
} Object;

typedef struct {
  Object proto;
  int length;
  int height;
} Square;

typedef struct {
  Object proto;
  int radius;
} Circle;

/**/
int Object_init(void *self)
{
  return 1;
}

void Object_descripe(void *self)
{
  Object *obj = self;
  printf("%s.\n", obj->description);
}

void Object_destroy(void *self)
{
  Object *obj = self;

  if (obj) {
    if (obj->description)
      free(obj->description);
    free(obj);
  }
}

void *Object_new(size_t size, Object proto, char *description)
{
  if (!proto.init) proto.init = Object_init;
  if (!proto.descripe) proto.descripe = Object_descripe;
  if (!proto.destroy) proto.destroy = Object_destroy;

  Object *el = calloc(1, size);
  *el = proto;

  /* Clang don't like it? */
  el->description = strdup(description);

  if (!el->init(el)) {
    el->destroy(el);
    return NULL;
  } else {
    return el;
  }
}

/* */
int Square_init(void *self)
{
  Square *square = self;
  return 1;
}

Object SquareProto = {
  .init = Square_init
};

int Circle_init(void *self)
{
  Circle *circle = self;
  return 1;
}

Object CircleProto = {
  .init = Circle_init
};


int main()
{
  Square *square = NEW(Square, "square object");
  Circle *circle = NEW(Circle, "circle object");

  square->length = 10;
  square->height = 10;

  circle->radius = 10;

  square->_(descripe)(square);
  circle->_(descripe)(circle);

  return 0;
}

