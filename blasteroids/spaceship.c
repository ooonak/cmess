#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "spaceship.h"
#include "game.h"

static const double ROTATION_SIZE = 10;
static const double SPEED_SIZE = 0.8;

/* Build new ship */
Spaceship* new_ship()
{
  Spaceship *s = malloc(sizeof(Spaceship));
  s->sx = SCREEN_W/2;
  s->sy = SCREEN_H/2;
  s->heading = 0.0;
  s->speed = 0.0;
  s->lives = 3;
  s->timer = 5 * FPS; /* The first 5 seconds of a new life, you can't die. */
  s->color = al_map_rgb(0, 255, 0);
  return s;
}

/* Free memory */
void destroy_ship(Spaceship *s)
{
  free(s);
} 

/* Draw ship */
void draw_ship(Spaceship *s)
{
  ALLEGRO_TRANSFORM transform;
  al_identity_transform(&transform);
  al_rotate_transform(&transform, 0);
  al_rotate_transform(&transform, (s->heading * (M_PI/180)));
  al_translate_transform(&transform, s->sx, s->sy);
  al_use_transform(&transform);
  al_draw_line(-8, 9, 0, -11, s->color, 3.0f);
  al_draw_line(0, -11, 8, 9, s->color, 3.0f);
  al_draw_line(-6, 4, -1, 4, s->color, 3.0f);
  al_draw_line(6, 4, 1, 4, s->color, 3.0f);
}

/* Move ship */
void move_ship(Spaceship *s, KEYS key)
{
  switch(key) {
    case KEY_RIGHT:
      s->heading += ROTATION_SIZE;
        if(s->heading > 360)
          s->heading -= 360; 
      break;  
    case KEY_LEFT:
      s->heading -= ROTATION_SIZE;
        if(s->heading <= 0)
          s->heading += 360;
      break;  
    case KEY_DOWN:
      s->speed -= SPEED_SIZE;
      break;  
    case KEY_UP:
      s->speed += SPEED_SIZE;
    }

    /* Can't move backwards */
    if (s->speed > 0 && s->speed <= 20) {
      /* Movement calculated from heading and speed */
      s->sx += s->speed * sin((M_PI/180) * s->heading);
      s->sy -= s->speed * cos((M_PI/180) * s->heading);

      /* See if spaceship moves beyond screen */
      if (s->sx > SCREEN_W)
        s->sx -= SCREEN_W;
      if (s->sx < 0)
        s->sx += SCREEN_W;
      if (s->sy > SCREEN_H)
        s->sy -= SCREEN_H;
      if (s->sy < 0)
        s->sy += SCREEN_H;
    }
}
