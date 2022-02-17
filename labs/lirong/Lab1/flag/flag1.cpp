#include <stdio.h>
#include "hahaha.h"
void printred(int a, int b, int n, int row,int each)
{
    if (b <= 0)
    {
        printn(each / 2, n, row - 1);
        return;
    }
    printf("R");
    if (a > 0)
    {
        printred(a-1, b - 1, n, row,each);
    }
    else if (b >= 0)
    {
        printwhite(each-1, b - 1, n, row,each);
    }
}
void printwhite(int a, int b, int n, int row,int each)
{
    if (b <= 0)
    {
        printn(each / 2, n, row - 1);
        return;
    }
    printf("W");
    if (a > 0)
    {
        printwhite(a - 1, b - 1, n, row,each);
    }
    else if (b >= 0)
    {
        printred(each-1, b - 1, n, row,each);
    }
}
void printn(int a, int n, int row)
{
    int temp;
    printf("\n");
    if (row == 0)
    {
        return;
    }
    printred(a-1, n, n, row,a);
}

int main()
{
    int n, temp, c = 1;
    scanf("%d", &n);
    for (temp = n; temp > 0; temp--)
    {
        c *= 2;
    }
    printn(c, c, n+1);
    return 0;
}
