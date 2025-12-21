#include <stdio.h>
#include <string.h>

int main() {
    char bracket;
    int floor = 0;
    int hit_basement = 0;
    int turn = 0;

    while (scanf(" %c", &bracket) == 1) {
        floor += bracket == '(' ? 1 : -1;

        if (!hit_basement)
            turn++;

        if (floor == -1)
            hit_basement = 1;
    }

    printf("floor: %d\n", floor);
    printf("turn: %d\n", turn);
    return 0;
}
