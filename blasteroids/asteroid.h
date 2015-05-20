typedef struct Asteroid {
  float sx;
  float sy;
  float heading;
  float twist;
  float speed;
  float rot_velocity;
  float scale;
  int gone;
  struct Asteroid *next;
  struct Asteroid *prior;
  ALLEGRO_COLOR color;
} Asteroid;

Asteroid* make_roids(int many);
void draw_roids(Asteroid *last);
void destroy_roids(Asteroid *last);
void move_roids(Asteroid *last);
Asteroid* split_roid(Asteroid *roid);
