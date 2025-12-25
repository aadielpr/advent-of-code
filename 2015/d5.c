#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int main() {
    char str[17];
    int nice_string = 0;

    while (scanf("%16s", str) == 1) {
        int len = strlen(str);
        int seen[26][26];
        memset(seen, -1, sizeof(seen));

        bool squeezed = false;
        bool paired = false;

        for (int i = 0; i < len - 1; i++) {
            char c = str[i];
            char n = str[i + 1];
            int x = c - 'a';
            int y = n - 'a';

            if (i + 2 < len && c == str[i + 2]) {
                squeezed = true;
            }

            if (seen[x][y] != -1 && i - seen[x][y] > 1) {
                paired = true;
            }

            if (squeezed && paired) {
                nice_string++;
                break;
            }

            if (seen[x][y] == -1) {
                seen[x][y] = i;
            }
        }
    }

    printf("%d\n", nice_string);
}
