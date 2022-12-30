#include <stdio.h>

int main()
{
    int a;
    int *b;

    a = 42;
    b = &a;
    printf("%d\n",*b);
}