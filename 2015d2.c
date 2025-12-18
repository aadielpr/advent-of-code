#include <stdio.h>

int ribbon(int l, int w, int h) {
  int a = l, b = w, c = h;

  if (b < a) {
    int t = b;
    b = a;
    a = t;
  }

  if (c < b) {
    int t = c;
    c = b;
    b = t;
  }

  if (c < a) {
    int t = c;
    c = a;
    a = t;
  }

  int perimeter = 2 * (a + b);
  int bow = l * w * h;

  return perimeter + bow;
}

int paper(int l, int w, int h) {
  int x, y, z, surface;
  int total_paper = 0;

  x = l * w;
  y = w * h;
  z = l * h;
  surface = 2 * x + 2 * y + 2 * z;

  int slack = x;
  if (y < slack) {
    slack = y;
  }

  if (z < slack) {
    slack = z;
  }

  return surface + slack;
}

int main() {
  int l, w, h;
  int total_paper = 0;
  int total_ribbon = 0;

  while (scanf("%dx%dx%d", &l, &w, &h) == 3) {
    total_paper += paper(l, w, h);
    total_ribbon += ribbon(l, w, h);
  }

  printf("total paper: %d\n", total_paper);
  printf("total ribbon: %d\n", total_ribbon);
}
