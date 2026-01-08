#include "stdio.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main() {
    char buf[256];
    int code_len = 0;
    int encoded_len = 0;

    while (fgets(buf, sizeof(buf), stdin)) {
        int len = strlen(buf);
        code_len += len - 1;
        encoded_len += 2; // surrounding quotes

        for (int i = 0; i < len - 1; i++) {
            if (buf[i] == '\\' || buf[i] == '\"') {
                encoded_len += 2;
            } else {
                encoded_len += 1;
            }
        }
    }

    printf("code_len: %d\n", code_len);
    printf("encoded_len: %d\n", encoded_len);
    printf("total: %d\n", encoded_len - code_len);
}
