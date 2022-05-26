//
//  test.cpp
//
//  Created by KD on 17.05.22.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "deque.cpp"
#include "time.h"
using std::cout;
using std::cin;
using std::rand;
using std::srand;

int main()
{
    Deque<int> *newdeque = new Deque<int>();
    for (int i = 1; i <= 1000; i++)
    {
        (*newdeque).pushback(i);
    }
    (*newdeque).printall();
    for (int j = 0; j < 100; j++)
    {
        if (!(*newdeque).isempty())
        {
            cout << "The front element is " << (*newdeque).popfront() << "\n";
            cout << "After popfront the front element is " << (*newdeque).front() << "\n";
        }
        if (!(*newdeque).isempty())
        {
            cout << "The back element is " << (*newdeque).popback() << "\n";
            cout << "After popback the back element is " << (*newdeque).back() << "\n";
        }
    }
    (*newdeque).printall();
    int item;
    for (int k = 0; k < 35; k++)
    {
        item = rand();
        (*newdeque).pushback(item);
    }
    cout << "\n" << "Empty the deque from front to back:\n";
    int num = (*newdeque).getlength();
    for (int i = 0; i < num; i++)
    {
        cout << (*newdeque).popfront() << " + ";
    }
    cout << "=========\n";
    if ((*newdeque).isempty())
        cout << "The deque is now empty.\n";
    else
        cout << "Somrething is wrong. The deque is not empty.\n";
    return(0);
}
