#include <stdio.h>
#include "ex1.h"

void printred(int a, int i, int b)
{
    if (a > i)
    {
        printline(i, b / 2);
        return;
    }
    for (int k = 0; k < b; k++)
    {
        printf("R");
    }
    printwhite(a + b, i, b);
}

void printwhite(int a, int i, int b)
{
    if (a > i)
    {
        printline(i, b / 2);
        return;
    }
    for (int k = 0; k < b; k++)
    {
        printf("W");
    }
    printred(a + b, i, b);
}

void printline(int i, int b)
{
    if (b == 0)
    {
        printf("\n");
        return;
    }
    printf("\n");
    printred(1, i, b);
}

int main()
{
    int n;
    scanf("%d",&n);
    int i=1<<n;
    // printf("%d",i);
    printline(i, i);
    return 0;
}