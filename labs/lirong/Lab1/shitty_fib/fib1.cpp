#include <iostream>
using namespace std;
int main()
{
    int a = 1,
        b = 1,
        n, i;
    cin >> n;
    for (n; n >= 1; n--)
    {
        i = b;
        b = b + a;
        a = i;
    }
    cout << a;
}