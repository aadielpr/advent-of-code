#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum Operation {
    AND,
    OR,
    RSHIFT,
    LSHIFT,
    NOT,
    SIGN,
};

struct Wire {
    char lhs[8], rhs[8], out[8];
    bool isCalc;
    uint16_t v;
    enum Operation op;
};

bool is_number(const char *s) { return isdigit(s[0]); }

uint16_t to_uint16(const char *s) { return (uint16_t)atoi(s); }

struct Wire *get_wire(const char *wire, struct Wire wires[], int wire_size) {
    for (int i = 0; i < wire_size; i++) {
        if (strcmp(wires[i].out, wire) == 0) {
            return &wires[i];
        }
    }

    return NULL;
}

uint16_t calculate(const char *wire, struct Wire *wires, int size) {
    struct Wire *w = get_wire(wire, wires, size);

    if (w == NULL) {
        printf("wire not found %s\n", wire);
        exit(1);
    }

    if (w->isCalc) {
        return w->v;
    }

    uint16_t l;
    uint16_t r;
    uint16_t res;

    switch (w->op) {
    case AND:
        l = is_number(w->lhs) ? to_uint16(w->lhs) : calculate(w->lhs, wires, size);
        r = is_number(w->rhs) ? to_uint16(w->rhs) : calculate(w->rhs, wires, size);
        w->v = l & r;
        break;
    case OR:
        l = is_number(w->lhs) ? to_uint16(w->lhs) : calculate(w->lhs, wires, size);
        r = is_number(w->rhs) ? to_uint16(w->rhs) : calculate(w->rhs, wires, size);
        w->v = l | r;
        break;
    case LSHIFT:
        l = is_number(w->lhs) ? to_uint16(w->lhs) : calculate(w->lhs, wires, size);
        w->v = l << atoi(w->rhs);
        break;
    case RSHIFT:
        l = is_number(w->lhs) ? to_uint16(w->lhs) : calculate(w->lhs, wires, size);
        w->v = l >> atoi(w->rhs);
        break;
    case NOT:
        l = calculate(w->lhs, wires, size);
        w->v = ~l & 0xFFFF;
        break;
    case SIGN:
        w->v = calculate(w->lhs, wires, size);
        break;
    }

    w->isCalc = true;
    return w->v;
}

int main() {
    char line[64];
    int size = 0;
    struct Wire wires[512];

    while (fgets(line, sizeof line, stdin) != NULL) {
        struct Wire wire = {.isCalc = false};
        if (sscanf(line, "%s AND %s -> %s", wire.lhs, wire.rhs, wire.out) == 3) {
            wire.op = AND;
        } else if (sscanf(line, "%s OR %s -> %s", wire.lhs, wire.rhs, wire.out) == 3) {
            wire.op = OR;
        } else if (sscanf(line, "%s LSHIFT %s -> %s", wire.lhs, wire.rhs, wire.out) == 3) {
            wire.op = LSHIFT;
            if (is_number(wire.lhs)) {
                wire.v = to_uint16(wire.lhs) << atoi(wire.rhs);
                wire.isCalc = true;
            }
        } else if (sscanf(line, "%s RSHIFT %s -> %s", wire.lhs, wire.rhs, wire.out) == 3) {
            wire.op = RSHIFT;
            if (is_number(wire.lhs)) {
                wire.v = to_uint16(wire.lhs) >> atoi(wire.rhs);
                wire.isCalc = true;
            }
        } else if (sscanf(line, "NOT %s -> %s", wire.lhs, wire.out) == 2) {
            wire.op = NOT;
            if (is_number(wire.lhs)) {
                wire.v = (~to_uint16(wire.lhs)) & 0xFFFF;
                wire.isCalc = true;
            }
        } else if (sscanf(line, "%s -> %s", wire.lhs, wire.out) == 2) {
            wire.op = SIGN;
            if (is_number(wire.lhs)) {
                wire.v = to_uint16(wire.lhs);
                wire.isCalc = true;
            }
        }

        wires[size] = wire;
        size++;
    }

    uint16_t res = calculate("a", wires, size);
    printf("%s: %d\n", "a", res);

    return 0;
}
