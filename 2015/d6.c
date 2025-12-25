#include <stdio.h>
#include <string.h>

enum Command { CMD_TOGGLE, CMD_ON, CMD_OFF };

int main() {
    enum Command cmd;

    char line[64];
    char mode[4];

    int x1, x2, y1, y2;
    int grid[1000][1000] = {0};

    int brightness = 0;

    while (fgets(line, sizeof(line), stdin)) {
        if (strncmp(line, "toggle", 6) == 0) {
            sscanf(line, "toggle %d,%d through %d,%d", &x1, &y1, &x2, &y2);
            cmd = CMD_TOGGLE;
        } else {
            sscanf(line, "turn %3s %d,%d through %d,%d", mode, &x1, &y1, &x2,
                   &y2);

            if (strcmp(mode, "on") == 0)
                cmd = CMD_ON;
            else
                cmd = CMD_OFF;
        }

        for (int i = x1; i <= x2; i++) {
            for (int j = y1; j <= y2; j++) {
                if (cmd == CMD_ON)
                    grid[i][j]++;
                else if (cmd == CMD_OFF)
                    grid[i][j] = grid[i][j] > 0 ? grid[i][j] - 1 : 0;
                else if (cmd == CMD_TOGGLE) {
                    grid[i][j] += 2;
                }
            }
        }
    }

    // check light
    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) {
            brightness += grid[i][j];
        }
    }

    printf("total: %d\n", brightness);
}
