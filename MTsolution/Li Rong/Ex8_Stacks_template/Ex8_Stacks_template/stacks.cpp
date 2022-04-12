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
using std::cin;
using std::cout;

template <class T>
T &Stacks<T>::operator[](int index)
{
    return reprarray[index - 1];
}

template <class T>
int Stacks<T>::getlength1(void)
{
    return numitems1;
}

template <class T>
int Stacks<T>::getlength2(void)
{
    return numitems2;
}

/*
template<class T> void AList<T>::append(T value)
{
    if (numitems == maxsize)
        allocate();
    reprarray[numitems] = value;
    ++numitems;
    return;
}

template<class T> void AList<T>::insert(int index, T value)
{
    if (numitems == maxsize)
        allocate();
    if (index < numitems)
    {
        for (int j = numitems - 1; j >= index; --j)
        {
            reprarray[j+1] = reprarray[j];
        }
        reprarray[index] = value;
        ++numitems;
        return;
    }
    else
    {
        append(value);
        return;
    }
} */

template <class T>
void Stacks<T>::allocate(void)
{
    // This function needs to be modified
    int newsize = 2 * maxsize;
    T *newarray = new T[newsize];
    for (int i = 0; i < numitems1; ++i)
    {
        newarray[i] = reprarray[i];
    }
    for (int i = newsize - numitems2; i < newsize; ++i)
    {
        newarray[i] = reprarray[i - newsize + maxsize];
    }
    delete[] reprarray;
    reprarray = newarray;
    maxsize = newsize;
    return;
}

/*
template<class T> void AList<T>::remove(int index)
{
    if ((numitems == maxsize / 4) && (maxsize > minsize))
        deallocate();
    if (index <= numitems)
    {
        for (int j = index; j < numitems; ++j)
        {
            reprarray[j-1] = reprarray[j];
        }
        --numitems;
        return;
    }
    else
        cout << "Index error: list index out of range\n";
} */

template <class T>
void Stacks<T>::deallocate(void)
{
    // This function needs to be modified
    int newsize = maxsize / 2;
    T *newarray = new T[newsize];
    for (int i = 0; i < numitems1; ++i)
    {
        newarray[i] = reprarray[i];
    }
    for (int i = newsize - numitems2; i < newsize; ++i)
    {
        newarray[i] = reprarray[i - newsize + maxsize];
    }
    delete[] reprarray;
    reprarray = newarray;
    maxsize = newsize;
    return;
}

template <class T>
T Stacks<T>::top1(void)
{
    if (numitems1 == 0)
    {
        cout << "Stack 1 is empty\n";
        return 0;
    }
    else
        return reprarray[numitems1 - 1];

    // This function needs to be implemented
}

template <class T>
T Stacks<T>::top2(void)
{
    if (numitems2 == 0)
    {
        cout << "Stack 2 is empty\n";
        return 0;
    }
    else
        return reprarray[maxsize - numitems2];
    // This function needs to be implemented
}

template <class T>
T Stacks<T>::pop1(void)
{
    if (isempty1())
    {
        cout << "Stack 1 is empty\n";
        return 0;
    }
    T item = reprarray[numitems1 - 1];
    --numitems1;
    if ((numitems1 + numitems2 <= maxsize / 2) && (maxsize / 2 > minsize))
        deallocate();
    return item;
    // This function needs to be implemented
}

template <class T>
T Stacks<T>::pop2(void)
{
    if (isempty2())
    {
        cout << "Stack 2 is empty\n";
        return 0;
    }
    T item = reprarray[maxsize - numitems2];
    --numitems2;
    if ((numitems1 + numitems2 <= maxsize / 2) && (maxsize / 2 > minsize))
        deallocate();
    return item;
    // This function needs to be implemented
}

template <class T>
void Stacks<T>::push1(T item)
{
    if (numitems1 + numitems2 + 1 >= maxsize)
    {
        allocate();
    }
    reprarray[numitems1] = item;
    ++numitems1;
    // This function needs to be implemented
}

template <class T>
void Stacks<T>::push2(T item)
{
    if (numitems1 + numitems2 + 1 >= maxsize)
    {
        allocate();
    }
    reprarray[maxsize - numitems2 - 1] = item;
    ++numitems2;
    // This function needs to be implemented
}

template <class T>
bool Stacks<T>::isempty1(void)
{
    return (numitems1 == 0);
    // This function needs to be implemented
}

template <class T>
bool Stacks<T>::isempty2(void)
{
    return (numitems2 == 0);
    // This function needs to be implemented
}

template <class T>
void Stacks<T>::display(void)
{
    cout << "Stack 1: \n";
    for (int i = 0; i < numitems1; ++i)
    {
        cout << reprarray[i] << " ";
    }
    cout << "\n";
    cout << "Stack 2: \n";
    for (int i = maxsize - 1; i >= maxsize - numitems2; --i)
    {
        cout << reprarray[i] << " ";
    }
    cout << "\n";
    // This function needs to be implemented
}
