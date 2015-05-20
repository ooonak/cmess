#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "spaceship.h"
#include "blast.h"
#include "game.h"

const int NO_BLAST = 100;
const float BLAST_SPEED = 7.5;

/* Make array of pointers to blast structs. */
Blast** new_blasts()
{
  /* Dynamically allocated array of pointers to blast structs, NO_BLAST big */
  Blast **blasts = malloc(NO_BLAST * sizeof(Blast*));
  int i;
  for (; i<NO_BLAST; i++) {
    blasts[i] = malloc(sizeof(Blast));
    blasts[i]->sx = -1.0;
    blasts[i]->sy = 0.0;
    blasts[i]->heading = 0.0;
    blasts[i]->alive = 0;
  }
  return blasts;
}

/* Heap cleaning. */
void destroy_blasts(Blast** blasts)
{
  int i;
  for (; i<NO_BLAST; i++) {
    free(blasts[i]);
  }
}

/* Set heading and position to the same as Spaceship and set 'alive' 1 */
void shoot_blast(Blast *blast, Spaceship *s)
{
  blast->sx = s->sx;
  blast->sy = s->sy;
  blast->heading = s->heading - 90;
  blast->alive = 1;
}

/* Calculate new coordinates. */
void move_blasts(Blast** blasts)
{
  int i=0;
  for (; i<NO_BLAST; i++) {
    // sx is -1 from start, no need to draw an inactive blast.
    if (blasts[i]->sx > 0 && blasts[i]->alive) {
      double move_x = BLAST_SPEED * cos((M_PI/180) * blasts[i]->heading);
      double move_y = BLAST_SPEED * sin((M_PI/180) * blasts[i]->heading);
      blasts[i]->sx += move_x;
      blasts[i]->sy += move_y;
    if (blasts[i]->sx < 0 || blasts[i]->sx > SCREEN_W)
      blasts[i]->alive = 0;
    if (blasts[i]->sy < 0 || blasts[i]->sy > SCREEN_H)
      blasts[i]->alive = 0;
    }
  }
}

/* Draw blast if 'alive' is 1. */
void draw_blasts(Blast** blasts)
{
  ALLEGRO_COLOR BLAST_COLOR = al_map_rgb(0, 255, 255);

  int i=0;
  for (; i<NO_BLAST; i++) {
    if (blasts[i]->alive) {
      ALLEGRO_TRANSFORM transform;
      al_identity_transform(&transform);
      al_rotate_transform(&transform, ((M_PI/180) * (blasts[i]->heading - 90)));
      al_translate_transform(&transform, blasts[i]->sx, blasts[i]->sy);
      al_use_transform(&transform);
      al_draw_line(0, 0, 0, 5, BLAST_COLOR, 3.0f);
    }
  }
}

