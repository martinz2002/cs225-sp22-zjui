#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "hashmap.h"
#include "hashmap.cpp"
using std::cin;
using std::cout;
using std::hash;

hashmap<int, int> myhashtable1;

int fibbo(int a)
{
    int value = myhashtable1.retrieve(a);
    if (value != -1)
        return value;
    if (a == 1 || a == 2)
    {
        myhashtable1.add(a, 1);
        return 1;
    }
    value = fibbo(a - 1) + fibbo(a - 2);
    if (!myhashtable1.member(a, value))
        myhashtable1.add(a, value);
    return value;
}

int main()
{
    myhashtable1 = hashmap<int, int>(10);
    int a;
    while (1)
    {
        scanf("%d", &a);
        printf("%d\n", fibbo(a));
    }
}