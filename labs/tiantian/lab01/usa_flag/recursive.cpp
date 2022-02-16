#include <iostream>
#define RED 1
#define WHITE -1

using namespace std;
int n;
int print_row(int rowNum);
int main()
{
    cin >> n;
    print_row(n);
    return 0;
}

int print_row(int rowNum)
{
    if (rowNum == 0)
        return -1;
    for (int i = 0; i <= n; i++)
    {
        int flipNum = (1 << i) - 1;
        int flag = WHITE; // 1 = red; -1 = white
        while (flipNum >= 0)
        {
            flag = -flag;
            if (flag == RED)
            {
                for (int j = 0; j < (1 << n - i); j++)
                    printf("R");
            }
            else
            {
                for (int j = 0; j < (1 << n - i); j++)
                    printf("W");
            }
            flipNum--;
        }
        printf("\n");
    }
}