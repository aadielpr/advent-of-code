#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX_SIZE 20000

int main() {
  int visited_house_count = 1;
  struct House {
    int x;
    int y;
  };

  struct House p = {.x = 0, .y = 0};
  struct House visited[MAX_SIZE] = {p};
  char move;

  while (scanf(" %c", &move) == 1) {
    switch (move) {
      case '^': p.y++; break;
      case '>': p.x++; break;
      case 'v': p.y--; break;
      case '<': p.x--; break;
    }

    bool visit = false;
    for (int j = 0; j < visited_house_count; j++) {
      if (visited[j].x == p.x && visited[j].y == p.y) {
        visit = true;
      }
    }

    if (!visit) {
      visited[visited_house_count] = p;
      visited_house_count++;
    }
  }

  printf("visited house: %d\n", visited_house_count);
}
