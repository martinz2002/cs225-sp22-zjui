#include <iostream>
using namespace std;
int fibb(int a, int b, int n)
{
    switch (n)
    {
    case 1:
        return 1;
    case 2 /* constant-expression */:
        return b; /* code */
    default:
        return fibb(b, a + b, n - 1);
    }
}

int main()
{
    int n;
    cin >> n;
    cout << fibb(1, 1, n);
    return 0;
}