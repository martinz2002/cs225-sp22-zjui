#include <stdio.h>


int main()
{
    int n, i, k, temp, j = 1;
    scanf("%d", &n);
    for (temp = n; temp != 0; temp--)
    {
        j *= 2;
    }
    temp = j;
    n = 1;
    while (temp != 0)
    {
        j = temp;
        for (k = 0; k != n; k++)
        {
            {
                for (i = j; i != 0; i--)
                {
                    printf("R");
                }
                k++;
                if (k == n)
                {
                    break;
                }
                for (i = j; i != 0; i--)
                {
                    printf("W");
                }
            }
        }
        printf("\n");
        n *= 2;
        temp /= 2;
    }
    return 0;
}

