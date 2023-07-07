#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void) {
    int *a;
    int *b;
    int i;
    a = (int *)malloc(sizeof(int) * 5);
    b = (int *)malloc(sizeof(int) * 5);

    for (i = 0; i < 5; i++)
        a[i] = i;
    b = a;
    a[2] = 10;
    for (i = 0; i < 5; i++)
        printf("a:%d\tb:%d\n", a[i], b[i]);

    free(a);
    free(b);

    return 0;
}
