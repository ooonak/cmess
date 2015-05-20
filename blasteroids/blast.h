typedef struct Blast {
  float sx;
  float sy;
  float heading;
  int alive;
} Blast;

Blast** new_blasts();
void destroy_blasts(Blast** blasts);
void shoot_blast(Blast *blast, Spaceship *s);
void move_blasts(Blast** blasts);
void draw_blasts(Blast** blasts);
