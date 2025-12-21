#include "md5.h"
#include <stdio.h>
#include <string.h>

int main() {
    uint8_t hash[16];
    char str[100];
    char secret_key[9] = "bgvyzdsv";

    int num = 0, run = 1;
    while (run) {
        snprintf(str, sizeof(str), "%s%d", secret_key, num);

        char md5_str[33];
        md5String(str, hash);
        for (int i = 0; i < 16; i++) {
            snprintf(md5_str + i * 2, sizeof(md5_str), "%02x", hash[i]);
        }

        char zeroes[7] = "";
        for (int i = 0; i < 6; i++) {
            // should convert it into a string! damn, c is hard
            char c[2] = {md5_str[i], '\0'};
            strcat(zeroes, c);
        }

        zeroes[6] = '\0';
        // we can't do like zeroes == "00000", need strcmp for this.
        if (strcmp(zeroes, "000000") == 0) {
            break;
        }
        num++;
    }

    printf("%s\n", str);
}
