#include <stdio.h>

int main() {
  int l, w, h, x, y, z, slack, surface;
  int total_paper = 0;

  while (scanf("%dx%dx%d", &l, &w, &h) == 3) {
    printf("input: l: %d w: %d h: %d\n", l, w, h);

    x = l * w;
    y = w * h;
    z = l * h;
    surface = 2 * x + 2 * y + 2 * z;
    slack = x < y ? x < z ? x : z : y < z ? y : z;
    total_paper += surface + slack;

    printf("(x: %d y: %d z: %d) slack: %d surface: %d\n", x, y, z, slack, surface);
  }

  printf("total paper: %d\n", total_paper);
}
