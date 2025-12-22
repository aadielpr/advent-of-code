#include <stdbool.h>
#include <stdio.h>
#include <string.h>

enum Vowel { A = 'a', I = 'i', U = 'u', E = 'e', O = 'o' };

int main() {
    char str[17];
    int nice_string = 0;

    while (scanf("%16s", str) == 1) {
        int vowel_count = 0;
        bool twin_letter = false;
        bool illegal = false;
        printf("%s\n", str);

        int len = strlen(str);
        for (int i = 0; i < len; i++) {
            char c = str[i];
            char next_c = i == len - 1 ? '0' : str[i + 1];

            // concat the string
            char pair_str[3];
            snprintf(pair_str, sizeof(pair_str), "%c%c", c, next_c);

            // check vowel
            if (c == A || c == I || c == U || c == E || c == O) {
                vowel_count++;
            }

            // check is this twin
            if (c == next_c) {
                twin_letter = true;
            }

            // check illegal string
            if (strcmp(pair_str, "ab") == 0 || strcmp(pair_str, "cd") == 0 ||
                strcmp(pair_str, "pq") == 0 || strcmp(pair_str, "xy") == 0) {
                illegal = true;
            }
        }

        if (vowel_count >= 3 && twin_letter && !illegal) {
            nice_string++;
        }
    }

    printf("total: %d\n", nice_string);
}
