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
    if (numitems == 0)
        return true;
    else
        return false;
}

template<class T> T fifo<T>::front(void)
{
    if (isempty() == false)
        return reprarray[first];
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
    if (numitems == maxsize)
        allocate();
    last = ++last % maxsize;
    reprarray[last] = value;
    ++numitems;
    return;
}

template<class T> T fifo<T>::popfront(void)
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
    /* This function needs to be implemented. It may be necessary to make changes to other member functions as well. */
}

template<class T> void fifo<T>::display(void)
{
    // This may need to be extended.
    cout << "The queue elements from front to back are:\n";
    int num = getlength();
    int i = first;
    while (i != ((last + 1) % maxsize))
    {
        cout << reprarray[i] << "\n";
        i = ++i % maxsize;
    }
    cout << "\n";
    return;
}
