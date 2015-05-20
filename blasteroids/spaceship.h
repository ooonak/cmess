typedef struct Spaceship {
  float sx;
  float sy;
  float heading;
  float speed;
  int lives;
  int timer;
  ALLEGRO_COLOR color;
} Spaceship;

typedef enum KEYS { 
  KEY_UP, 
  KEY_DOWN, 
  KEY_LEFT, 
  KEY_RIGHT, 
  KEY_SPACE,
  NONE
} KEYS;

Spaceship* new_ship();
void destroy_ship(Spaceship *s);
void draw_ship(Spaceship *s);
void move_ship(Spaceship *s, KEYS key);
