//
//  test.cpp
//
//  Created by KD on 18.01.21.
//  Modified on 04.04.22.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "dfifo.cpp"
using std::cout;
using std::cin;

int main()
{
    // Test 1
    Dfifo<int> queue1 = Dfifo<int>();
    queue1.pushback(0);
    queue1.pushback(-4);
    queue1.pushback(1);
    queue1.pushback(2);
    queue1.pushback(-8);
    queue1.pushback(3);
    queue1.pushback(4);
    queue1.pushback(5);
    queue1.pushback(-1);
    queue1.pushback(6);
    queue1.pushback(9);
    queue1.pushback(-7);
    queue1.pushback(-6);
    queue1.pushback(-5);
    queue1.pushback(7);
    queue1.pushback(-3);
    queue1.pushback(8);
    queue1.pushback(-2);
    cout << "Test 1\n";
    queue1.display();
    queue1.reverse();
    queue1.display();
    cout << "\n";
    // Test 2
    Dfifo<int> queue2 = Dfifo<int>();
    queue2.pushback(30);
    queue2.pushback(42);
    queue2.pushback(55);
    queue2.pushback(79);
    queue2.pushback(-5);
    queue2.pushback(264);
    queue2.pushback(187);
    queue2.pushback(56);
    cout << "Test 2\n";
    queue2.display();
    queue2.reverse();
    queue2.display();
    cout << "\n";
    // Test 3
    int mem = 0;
    int num = queue1.getlength();
    for (int i = 0; i < num; i++)
    {
        mem = queue1.popfront();
        queue2.pushback(mem);
        mem = queue2.popfront();
        queue2.pushback(mem);
    }
    queue2.display();
    queue2.reverse();
    queue2.display();
    cout << "\n";
    return(0);
}
