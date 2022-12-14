//
//  alist.cpp
//  
//
//  Created by KD on 14.01.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "fifo.h"
using std::cout;
using std::cin;

template<class T> fifo<T>::fifo(int size)
{
    maxsize = size;
    if (size < 10)
        minsize = size;
    else
        minsize = 10;
    numitems = 0;
    first = 0;
    last = -1;
    reprarray = new T[maxsize];
    revdir = false;
}

//template<class T> fifo<T>::~fifo()
//{
//    delete[] *reprarray;
//}

template<class T> T &fifo<T>::operator[](int index)
{
    if ((1 <= index) && (index <= numitems))
    {
        int relindex = (index + first -1) % maxsize;
        return reprarray[relindex];
    }
    else
    {
        cout << "Error: index " << index << " out of range.\n";
        exit(EXIT_FAILURE);
    }
}

template<class T> int fifo<T>::getlength(void)
{
    return numitems;
}

template<class T> bool fifo<T>::isempty(void)
{
    return (numitems == 0);
}

template<class T> T fifo<T>::front(void)
{
    if (isempty() == false)
    {
        if (revdir == false)
            return reprarray[first];
        int relindex = (first + numitems - 1) % maxsize;
        return reprarray[relindex];
    }
    else
    {
        cout << "The queue is empty.\n";
        exit(EXIT_FAILURE);
    }
}

template<class T> T fifo<T>::back(void)
{
    if (isempty() == false)
    {
        if (revdir == true)
            return reprarray[first];
        int relindex = (first + numitems - 1) % maxsize;
        return reprarray[relindex];
    }
    else
    {
        cout << "The queue is empty.\n";
        exit(EXIT_FAILURE);
    }
}

template<class T> void fifo<T>::pushback(T value)
{
    if (revdir == true)
        pushf(value);
    else
        pushb(value);
    return;
}

template<class T> void fifo<T>::pushb(T value)
{
    if (numitems == maxsize)
        allocate();
    last = ++last % maxsize;
    reprarray[last] = value;
    ++numitems;
    return;
}

template<class T> void fifo<T>::pushf(T value)
{
    if (numitems == maxsize)
        allocate();
    first = --first % maxsize;
    reprarray[first] = value;
    ++numitems;
    return;
}

template<class T> T fifo<T>::popfront(void)
{
    if (revdir == false)
        return popf();
    return popb();
}

template<class T> T fifo<T>::popf(void)
{
    if ((numitems == maxsize / 4) && (maxsize > minsize))
        deallocate();
    if (isempty() == false)
    {
        T frontelement = reprarray[first];
        first = ++first % maxsize;
        --numitems;
        return frontelement;
    }
    else
    {
        cout << "The queue is empty.\n";
        exit(EXIT_FAILURE);
    }
}

template<class T> T fifo<T>::popb(void)
{
    if ((numitems == maxsize / 4) && (maxsize > minsize))
        deallocate();
    if (isempty() == false)
    {
        int relindex = (first + numitems - 1) % maxsize;
        T frontelement = reprarray[relindex];
        last = --last % maxsize;
        --numitems;
        return frontelement;
    }
    else
    {
        cout << "The queue is empty.\n";
        exit(EXIT_FAILURE);
    }
}

template<class T> void fifo<T>::allocate(void)
{
    int newsize = 2 * maxsize;
    T *newarray = new T[newsize];
    for (int i = 0; i < numitems; ++i)
    {
        int pos = (i + first) % maxsize;
        newarray[i] = reprarray[pos];
    }
    delete[] reprarray;
    reprarray = newarray;
    maxsize = newsize;
    first = 0;
    last = numitems -1;
    return;
}

template<class T> void fifo<T>::deallocate(void)
{
    int newsize = maxsize / 2;
    T *newarray = new T[newsize];
    for (int i = 0; i < numitems; ++i)
    {
        int pos = (i + first) % maxsize;
        newarray[i] = reprarray[pos];
    }
    delete[] reprarray;
    reprarray = newarray;
    maxsize = newsize;
    first = 0;
    last = numitems -1;
    return;
}

template<class T> void fifo<T>::reverse(void)
{
    revdir = (! revdir);
    return;
}

template<class T> void fifo<T>::display(void)
{
    cout << "The queue elements from front to back are:\n";
    int num = getlength();
    if (revdir == false)
    {
        int i = first;
        while (i != ((last + 1) % maxsize))
        {
            cout << reprarray[i] << "\n";
            i = ++i % maxsize;
        }
    }
    else
    {
        int i = last;
        while (i != ((first - 1) % maxsize))
        {
            cout << reprarray[i] << "\n";
            i = --i % maxsize;
        }
    }
    cout << "\n";
    return;
}
