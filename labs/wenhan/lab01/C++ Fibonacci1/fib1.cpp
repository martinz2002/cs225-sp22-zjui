#include <stdio.h>
int fib1(int n)
{
    if (n == 1)
        return 1;
    if (n == 2)
        return 2;
    return fib1(n - 1) + fib1(n - 2);
}

int main()
{
    int i;
    scanf("%d", &i);
    printf("%d", fib1(i));
    return 0;
}