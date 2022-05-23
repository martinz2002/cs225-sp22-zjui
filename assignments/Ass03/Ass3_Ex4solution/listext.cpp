//
//  listext.cpp
//  
//
//  Created by KD on 14.01.21.
//  Modified by KD on 02.03.22.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "listext.h"
#include "time.h"
using std::cout;
using std::cin;
using std::rand;
using std::srand;

template<class T> Listext<T>::Listext(int size)
{
    maxsize = size;
    if (size < 20)
        minsize = size;
    else
        minsize = 20;
    numitems = 0;
    reprarray = new T[maxsize];
}

template<class T> T &Listext<T>::operator[](int index)
{
    return reprarray[index - 1];
}

template<class T> int Listext<T>::getlength(void)
{
    return numitems;
}

template<class T> void Listext<T>::setitem(int index, T value)
{
    if ((index > 0) && (index <= numitems))
    {
        reprarray[index - 1] = value;
        return;
    }
    else
        cout << "Index error: index out or range\n";
}

template<class T> T Listext<T>::getitem(int index)
{
    if ((index > 0) && (index <= numitems))
    {
        return reprarray[index - 1];
    }
    else
    {
        cout << "Index error: index out or range\n";
        exit(EXIT_FAILURE);
    }
}

template<class T> void Listext<T>::append(T value)
{
    if (numitems == maxsize)
        allocate();
    reprarray[numitems] = value;
    ++numitems;
    return;
}

template<class T> void Listext<T>::insert(int index, T value)
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
}

template<class T> void Listext<T>::allocate(void)
{
    int newsize = 2 * maxsize;
    T *newarray = new T[newsize];
    for (int i = 0; i < numitems; ++i)
    {
        newarray[i] = reprarray[i];
    }
    delete[] reprarray;
    reprarray = newarray;
    maxsize = newsize;
    return;
}

template<class T> void Listext<T>::remove(int index)
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
}

template<class T> void Listext<T>::deallocate(void)
{
    int newsize = maxsize / 2;
    T *newarray = new T[newsize];
    for (int i = 0; i < numitems; ++i)
    {
        newarray[i] = reprarray[i];
    }
    delete[] reprarray;
    reprarray = newarray;
    maxsize = newsize;
    return;
}

template<class T> void Listext<T>::concat(Listext<T> &list)
{
    int length = list.getlength();
    for (int i = 1; i <= length; ++i)
    {
        append(list[i]);
    }
    return;
}

template<class T> bool Listext<T>::member(T value)
{
    bool result = false;
    for (int i = 0; i < numitems; ++i)
    {
        if (reprarray[i] == value)
        {
            result = true;
            break;
        }
    }
    return result;
}

template<class T> bool Listext<T>::equal(Listext<T> &list)
{
    bool result = true;
    if (numitems == list.getlength())
    {
        for (int i = 0; i < numitems; ++i)
        {
            if (reprarray[i] == list[i + 1])
                continue;
            else
            {
                result = false;
                break;
            }
        }
    }
    else
        result = false;
    return result;
}

template<class T> bool Listext<T>::sublist(Listext<T> &list)
{
    int length = list.getlength();
    bool result = true;
    for (int i = 1, j = 0; (i <= length) && (j < numitems); ++i, ++j)
    {
        if (list[i] == reprarray[j])
        {
            if ((j == numitems - 1) && (i < length))
            {
                result = false;
                break;
            }
        }
        else
            if (j == numitems - 1)
            {
                result = false;
                break;
            }
            else
                --i;
    }
    return result;
}

template<class T> void Listext<T>::prettyprint(void)
{
    for (int i = 0; i < numitems; i++)
    {
        cout << i+1 << ":  " << reprarray[i];
        if (i != numitems - 1)
            cout << "; ";
        cout << "\n";
    }
}

/* for added member function for rotation and selection need to be implemented */

template<class T> void Listext<T>::rotate(int m)
{
    int k = 1;
    int i = m;
    int j = numitems - m;
    while (i != j)
    {
        if (i > j)
        {
            exchange(k, k+i, j);
            i -= j;
            k += j;
        }
        else
        {
            exchange(k, k+j, i);
            j -= i;
        }
    }
    exchange(k, k+i, i);
    return;
}

template<class T> void Listext<T>::exchange(int i, int j, int m)
{
    T temp;
    for (int k = 0; k < m; k++)
    {
        int i1 = i + k - 1;
        int i2 = j + k - 1;
        temp = reprarray[i1];
        reprarray[i1] = reprarray[i2];
        reprarray[i2] = temp;
    }
    return;
}

template<class T> T Listext<T>::select(int k)
{
    T result;
    srand(time(0));
    int index = rand() % numitems;
    T pivot = reprarray[index];
    Listext<T> U = Listext<T>(2 * maxsize / 3);
    Listext<T> V = Listext<T>(2 * maxsize / 3);
    for (int i = 0; i < numitems; i++)
    {
        if (reprarray[i] < pivot)
            U.append(reprarray[i]);
        else
        {
            if (reprarray[i] > pivot)
                V.append(reprarray[i]);
        }
    }
    int u = U.getlength();
    int v = numitems - V.getlength();
    if (k <= u)
        result = U.select(k);
    else
    {
        if (k > v)
            result = V.select(k - v);
        else
            result = pivot;
    }
    return result;
}
