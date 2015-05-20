#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "asteroid.h"
#include "game.h"

/* Create new asteroid */
static Asteroid* new_roid()
{
  Asteroid *a = malloc(sizeof(Asteroid));
  a->sx = random() % SCREEN_W;
  a->sy = random() % SCREEN_H;
  a->heading = ((float)rand()/(float)(RAND_MAX)) * 360;
  a->twist = ((float)rand()/(float)(RAND_MAX)) * 360;
  a->speed = 1.1;
  a->rot_velocity = (((float)rand()/(float)(RAND_MAX)) * 1.8) - 0.9;
  a->scale = 0.9 + (float)rand()/(float)(RAND_MAX) * 0.4;
  a->gone = 0;
  a->next = NULL;
  a->prior = NULL;
  a->color = al_map_rgb( (100 + random() % 155 ), 0, 0);
  ROIDS_ALIVE++;
  return a;
}

/* Make a linked list of many asteroids and return the pointer to the last */
Asteroid* make_roids(int many)
{ 
  Asteroid *j = new_roid();
  Asteroid *last = j;

  int i;
  for (i = 0; i < many; i++, j=j->prior) {
    j->prior = new_roid();
    j->prior->next = j;
  }
  return last;
}

/* Transform asteroid */
static void draw_roid(Asteroid *roid)
{
  ALLEGRO_TRANSFORM transform;
  al_identity_transform(&transform);
  al_rotate_transform(&transform, (roid->twist * (M_PI/180)));
  al_scale_transform(&transform, roid->scale, roid->scale);
  al_translate_transform(&transform, roid->sx, roid->sy);
  al_use_transform(&transform);
  al_draw_line(-22, 20, -18, 4, roid->color, 2.0f);
  al_draw_line(-18, 4, -18, -10, roid->color, 2.0f);
  al_draw_line(-18, -10, -5, -10, roid->color, 2.0f);
  al_draw_line(-5, -10, -10, -22, roid->color, 2.0f);
  al_draw_line(-10, -22, 4, -22, roid->color, 2.0f);
  al_draw_line(4, -22, 20, -10, roid->color, 2.0f);
  al_draw_line(20, -10, 20, -5, roid->color, 2.0f);
  al_draw_line(20, -5, 0, 0, roid->color, 2.0f);
  al_draw_line(0, 0, 20, 10, roid->color, 2.0f);
  al_draw_line(20, 10, 10, 20, roid->color, 2.0f);
  al_draw_line(10, 20, 0, 15, roid->color, 2.0f);
  al_draw_line(0, 15, -22, 20, roid->color, 2.0f);
}

/* Draw every asteroid in the linked list, starting with the last one */
void draw_roids(Asteroid* last)
{ 
  Asteroid* i = last;
  Asteroid* j = NULL;
  for (; i != NULL; i = j ) {
    j = i->prior;
    if (!i->gone) {
      draw_roid(i);
    }
  }
}

/* Free memory */
void destroy_roids(Asteroid *last)
{
  Asteroid* i = last;
  Asteroid* j = NULL;
  for (; i != NULL; i = j ) {
    j = i->prior;
    free(i);
  }
}

/* Change heading, size and color */
static void child_roid(Asteroid *child)
{
  child->heading = random() % 360;
  child->scale = child->scale * 0.5;
  child->speed += 0.5;
  child->color = al_map_rgb( (155 + random() % 100 ), 250, 0);
}

/* Split in two and transform to child asteroid */
Asteroid* split_roid(Asteroid *roid)
{
  Asteroid* child = new_roid();
  child->sx = roid->sx - 20;
  child->sy = roid->sy - 20;
  roid->sx = roid->sx + 20;
  roid->sy = roid->sy + 20;
  child_roid(roid);
  child_roid(child);
  return child;
}

/* Move */
Asteroid* move_roid(Asteroid *roid)
{
  /* Calculate movement */
  double speed = roid->speed;
  double heading = roid->heading;
  double move_x = speed * cos(heading);
  double move_y = speed * sin(heading);
  roid->sx = roid->sx + move_x;
  roid->sy = roid->sy + move_y;

  /* Calculate rotation */
  if (roid->rot_velocity < 0) {
    roid->twist -= roid->rot_velocity;
    if (roid->twist < 0)
      roid->twist -= 360;
    if (roid->twist > 360)
      roid->twist += 360;
  }
  else {
    roid->twist -= roid->rot_velocity;
    if (roid->twist < 0)
      roid->twist += 360;
    if (roid->twist > 360)
      roid->twist -= 360;
  }

  /* See if asteroid moves beyond screen */
  if (move_x > 0 && roid->sx > SCREEN_W)
    roid->sx -= SCREEN_W;
  if (move_x < 0 && roid->sx < 0)
    roid->sx += SCREEN_W;
  if (move_y > 0 && roid->sy > SCREEN_H)
    roid->sy -= SCREEN_H;
  if (move_y < 0 && roid->sy < 0)
    roid->sy += SCREEN_H;

  return roid;
}

/* Move every asteroid in the linked list, starting with the last one */
void move_roids(Asteroid* last)
{ 
  Asteroid* i = last;
  Asteroid* j = NULL;
  for (; i != NULL; i = j ) {
    j = i->prior;
    if (!i->gone) {
      move_roid(i);
    }
  }
}
