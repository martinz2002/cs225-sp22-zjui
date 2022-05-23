//
//  test.cpp
//
//  Created by KD on 08.01.21.
//  Modified on 02.04.22.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "hashmap.cpp"
using std::cout;
using std::cin;

hashmap<int,int> fibtable = hashmap<int,int>(15);

long fib4(int m);

long fib4(int m)
{
    int n = m;
    int *result = fibtable.retrieve(n);
    if (result != 0)
        return *(fibtable.retrieve(n));
    long i = 1, j = 0, h = 1, k = 0;
    long temp;
    while (n > 0)
    {
        if (n % 2 != 0)
        {
            temp = j * h;
            j = i * h + j * k + temp;
            i = i * k + temp;
        }
        temp = h * h;
        h = 2 * k * h + temp;
        k = k * k + temp;
        n = n / 2;
    }
    fibtable.add(m,j);
    return j;
}

int main()
{
    int n;
    long f;
    bool c = true;
    while (c == true)
    {
        cout << "Enter a non-negative integer.\n";
        cin >> n;
        if (n >=0)
        {
            f = fib4(n);
            cout << "The " << n << "th Fibonacci number is " << f << " .\n";
        }
        else
            cout << "Error: Input " << n << " is negative.\n";
        cout << "Continue? Yes = 1 No = 0\n";
        cin >> c;
    }
    return 0;
}
