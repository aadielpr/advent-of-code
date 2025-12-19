#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX_SIZE 20000

struct Coordinate {
  int x;
  int y;
};

void move(struct Coordinate *c, char dir) {
  switch (dir) {
  case '^':
    c->y++;
    break;
  case '>':
    c->x++;
    break;
  case 'v':
    c->y--;
    break;
  case '<':
    c->x--;
    break;
  }
}

bool visited(struct Coordinate houses[], int count, int x, int y) {
  for (int j = 0; j < count; j++) {
    if (houses[j].x == x && houses[j].y == y) {
      return true;
    }
  }
  return false;
}

int main() {
  int count = 1;
  struct Coordinate real_santa = {.x = 0, .y = 0};
  struct Coordinate robo_santa = {.x = 0, .y = 0};
  struct Coordinate houses[MAX_SIZE] = {real_santa};
  char dir;
  bool turn = false;

  while (scanf(" %c", &dir) == 1) {
    struct Coordinate *current_santa = turn ? &real_santa : &robo_santa;
    move(current_santa, dir);

    if (!visited(houses, count, current_santa->x, current_santa->y)) {
      houses[count] = *current_santa;
      count++;
    }

    turn = !turn;
  }

  printf("visited house: %d\n", count);
}
