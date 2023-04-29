#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sum(int a, int b) { return a + b; }

int sub(int a, int b) { return a - b; }

int mul(int a, int b) { return a * b; }

int divi(int a, int b) { return a / b; }

int main(void) {
    int a = 0;
    int b = 0;
    char op[2];
    printf("Welcome to the Calculator App\n");
    do {
        scanf("Input value of a: %d\nInput value of b: %d\n", a, b);


    } while (strcmp(op, "+") == 0 || strcmp(op, "-") == 0 ||
            strcmp(op, "*") == 0 || strcmp(op, "/") == 0);
    return 0;
}
