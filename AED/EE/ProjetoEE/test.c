#include <stdio.h>
#include <stdlib.h>

int main (void)
{
    int *count;
    count = (int *)calloc(1, sizeof(int) * 10);
    printf("%d\n", count[2]);
    free(count);
    return 0;
}
