//
//  test.cpp
//
//  Created by KD on 18.01.21.
//  Modified on 03.04.22.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "fifo.cpp"
using std::cout;
using std::cin;

int main()
{
    // Test 1
    fifo<int> queue1 = fifo<int>(10);
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
    // Test 2
    fifo<int> queue2 = fifo<int>();
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
    // Test 3
    cout << "Test 3\n";
    queue1.reverse();
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
    return(0);
}
