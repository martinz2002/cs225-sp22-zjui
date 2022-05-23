//
//  stacks.cpp
//  
//
//  Created by KD on 14.01.21.
//  Modified by KD on 04.04.22.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "stacks.h"
using std::cout;
using std::cin;

template<class T> T &Stacks<T>::operator[](int index)
{
    return reprarray[index - 1];
}

template<class T> int Stacks<T>::getlength1(void)
{
    return numitems1;
}

template<class T> int Stacks<T>::getlength2(void)
{
    return numitems2;
}

template<class T> void Stacks<T>::allocate(void)
{
    // This function needs to be modified
    int newsize = 2 * maxsize;
    T *newarray = new T[newsize];
    for (int i = 0; i < numitems1; ++i)
    {
        newarray[i] = reprarray[i];
    }
    for (int i = 1; i <= numitems2; ++i)
    {
        newarray[newsize - i] = reprarray[maxsize - i];
    }
    delete[] reprarray;
    reprarray = newarray;
    maxsize = newsize;
    return;
}

template<class T> void Stacks<T>::deallocate(void)
{
    // This function needs to be modified
    int newsize = maxsize / 2;
    T *newarray = new T[newsize];
    for (int i = 0; i < numitems1; ++i)
    {
        newarray[i] = reprarray[i];
    }
    for (int i = 1; i <= numitems2; ++i)
    {
        newarray[newsize - i] = reprarray[maxsize - i];
    }
    delete[] reprarray;
    reprarray = newarray;
    maxsize = newsize;
    return;
}

template<class T> T Stacks<T>::top1(void)
{
    return reprarray[numitems1 - 1];
}

template<class T> T Stacks<T>::top2(void)
{
    return reprarray[maxsize - numitems2];
}

template<class T> T Stacks<T>::pop1(void)
{
    T result = reprarray[numitems1 - 1];
    numitems1--;
    if ((numitems1 + numitems2 == maxsize / 4) && (maxsize > minsize))
        deallocate();
    return result;
}

template<class T> T Stacks<T>::pop2(void)
{
    T result = reprarray[maxsize - numitems2];
    numitems2--;
    if ((numitems1 + numitems2 == maxsize / 4) && (maxsize > minsize))
        deallocate();
    return result;
}

template<class T> void Stacks<T>::push1(T item)
{
    if (numitems1 + numitems2 == maxsize)
        allocate();
    reprarray[numitems1] = item;
    ++numitems1;
    return;
}

template<class T> void Stacks<T>::push2(T item)
{
    if (numitems1 + numitems2 == maxsize)
        allocate();
    reprarray[maxsize - numitems2 - 1] = item;
    ++numitems2;
    return;
}

template<class T> bool Stacks<T>::isempty1(void)
{
    return (numitems1 == 0);
}

template<class T> bool Stacks<T>::isempty2(void)
{
    return (numitems2 == 0);
}

template<class T> void Stacks<T>::display(void)
{
    cout << "The elements in stack 1 from bottom to top are:\n";
    for (int i = 0; i < numitems1; i++)
    {
        cout << i << ": " << reprarray[i] << "\n";
    }
    cout << "The elements in stack 2 from bottom to top are:\n";
    for (int i = 0; i < numitems2; i++)
    {
        cout << i << ": " << reprarray[maxsize - i - 1] << "\n";
    }
    cout << "\n";
    return;
}
