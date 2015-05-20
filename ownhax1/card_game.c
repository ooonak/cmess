#include <stdio.h>
#include <stdlib.h>

// Arrays of pointers to literal strings.
char *color[] =  {"black", "red"};
char *face[] = {"spade", "club", "heart", "diamond"};
char *value[] = {"Ace", "1", "2", "3",
                  "4", "5", "6", "7", 
                  "8", "9", "10", "Jack", "Queen", "King"};
int score[] = {14, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

// color, face and value is pointers.
typedef struct card {
  const char *color;
  const char *face;
  const char *value;
  int score;
  char* owner;
} card;

// Reserve space on the heap for a type "card".
card* create_card() {
    card *next = malloc(sizeof(card));
    return next;
}

// Make an array, size 52, with "card" structs.
struct card *deck[52];

// Build the deck of cards.
void build_deck()
{
  int i;
  for(i = 0; i < 52; i++) {
    deck[i] = create_card();
    if (i<14) {
      deck[i]->color = color[0];
      deck[i]->face = face[0];
      deck[i]->value = value[i];
      deck[i]->score = score[i];
      deck[i]->owner = "";
    } else if(i<27) {
      deck[i]->color = color[0];
      deck[i]->face = face[1];
      deck[i]->value = value[i-14];
      deck[i]->score = score[i-14];
      deck[i]->owner = "";
    } else if(i<40) {
      deck[i]->color = color[1];
      deck[i]->face = face[2];
      deck[i]->value = value[i-27];
      deck[i]->score = score[i-27];
      deck[i]->owner = "";
    } else { 
      deck[i]->color = color[1];
      deck[i]->face = face[3];
      deck[i]->value = value[i-40];
      deck[i]->score = score[i-40];
      deck[i]->owner = "";
    }
  }
}

// Show a card.
void show_card(int i) {
   printf("%s of %s (%s) is on %s hand.\n", deck[i]->value, deck[i]->face, 
       deck[i]->color, deck[i]->owner);  
}

// Free memory on the heap.
void clean_deck() {
  int i;
  for(i = 0; i<52; i++) {
    //printf("%p\n", &deck[i]);
    free(deck[i]);
  }
}

// Find a random card.
int draw(char* player) {
  int r = rand() % 52;
  if(deck[r]->owner = "") {
    deck[r]->owner = player;
    return r;
  } else {
    draw(player);
  }
}

int main()
{
  char* player = "Casper";
  int score;

  build_deck();

  int input = 0;
  while(input != 9) {
    printf("Hi %s, you got %i points.", player, score);
    puts("\nEnter your choice:\n1 to draw card from deck,\n2 to show your hand,\n9 to quit\n");
    scanf("%hi", &input);

    switch(input) {
      case 1:
        puts("You draw a card!\n");
        int card = draw(player);
        score = score + deck[card]->score;
        show_card(card);
        break;

      case 2:
        puts("Your hand is as follows:\n");
        int i;
        for(i = 0; i < 52; i++) {
          if(deck[i]->owner == player) {
            show_card(i);
          }
        }
        break;
      }
    }

  clean_deck();

  return 0;
}
