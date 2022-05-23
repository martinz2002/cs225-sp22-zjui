//
//  test.cpp
//  
//
//  Created by KD on 04.04.22.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "stacks.cpp"
using std::cout;
using std::cin;

int main()
{
    Stacks<int> mystacks = Stacks<int>(20);
    mystacks.push1(0);
    mystacks.push2(30);
    mystacks.display();
    mystacks.push1(-4);
    mystacks.push1(1);
    mystacks.push1(2);
    mystacks.push2(42);
    mystacks.push2(55);
    mystacks.display();
    mystacks.push1(-8);
    mystacks.push1(3);
    mystacks.push1(4);
    mystacks.push2(79);
    mystacks.push2(-5);
    mystacks.display();
    mystacks.push1(5);
    mystacks.push1(-1);
    mystacks.push1(6);
    mystacks.push1(9);
    mystacks.push2(264);
    mystacks.display();
    mystacks.push1(-7);
    mystacks.push1(-6);
    mystacks.push1(-5);
    mystacks.push2(187);
    mystacks.push2(56);
    mystacks.display();
    mystacks.push1(7);
    mystacks.push1(-3);
    mystacks.push1(8);
    mystacks.push1(-2);
    mystacks.display();
    int num = mystacks.getlength1() + mystacks.getlength2();
    int value;
    for (int i = 0; i < num; i++)
    {
        if (mystacks.isempty1() == false)
        {
            value = mystacks.pop1();
            cout << "Popped from Stack 1: " << value << "\n";
        }
        else
        {
            value = mystacks.pop2();
            cout << "Popped from Stack 2: " << value << "\n";
        }
    }
    return(0);
}
