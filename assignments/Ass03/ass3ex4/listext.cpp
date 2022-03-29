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
using std::cin;
using std::cout;

template <class T>
Listext<T>::Listext(int size)
{
    maxsize = size;
    if (size < 20)
        minsize = size;
    else
        minsize = 20;
    numitems = 0;
    reprarray = new T[maxsize];
}

template <class T>
T &Listext<T>::operator[](int index)
{
    return reprarray[index - 1];
}

template <class T>
int Listext<T>::getlength(void)
{
    return numitems;
}

template <class T>
void Listext<T>::setitem(int index, T value)
{
    if ((index > 0) && (index <= numitems))
    {
        reprarray[index - 1] = value;
        return;
    }
    else
        cout << "Index error: index out or range\n";
}

template <class T>
T Listext<T>::getitem(int index)
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

template <class T>
void Listext<T>::append(T value)
{
    if (numitems == maxsize)
        allocate();
    reprarray[numitems] = value;
    ++numitems;
    return;
}

template <class T>
void Listext<T>::insert(int index, T value)
{
    if (numitems == maxsize)
        allocate();
    if (index < numitems)
    {
        for (int j = numitems - 1; j >= index; --j)
        {
            reprarray[j + 1] = reprarray[j];
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

template <class T>
void Listext<T>::allocate(void)
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

template <class T>
void Listext<T>::remove(int index)
{
    if ((numitems == maxsize / 4) && (maxsize > minsize))
        deallocate();
    if (index <= numitems)
    {
        for (int j = index; j < numitems; ++j)
        {
            reprarray[j - 1] = reprarray[j];
        }
        --numitems;
        return;
    }
    else
        cout << "Index error: list index out of range\n";
}

template <class T>
void Listext<T>::deallocate(void)
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

template <class T>
void Listext<T>::concat(Listext<T> &list)
{
    int length = list.getlength();
    for (int i = 1; i <= length; ++i)
    {
        append(list[i]);
    }
    return;
}

template <class T>
bool Listext<T>::member(T value)
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

template <class T>
bool Listext<T>::equal(Listext<T> &list)
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

template <class T>
bool Listext<T>::sublist(Listext<T> &list)
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
        else if (j == numitems - 1)
        {
            result = false;
            break;
        }
        else
            --i;
    }
    return result;
}

template <class T>
void Listext<T>::prettyprint(void)
{
    for (int i = 0; i < numitems; i++)
    {
        cout << i + 1 << ":  " << reprarray[i];
        if (i != numitems - 1)
            cout << "; ";
        cout << "\n";
    }
}

/* for added member function for rotation and selection need to be implemented */

template <class T>
void Listext<T>::exchange(int i, int j, int m) // Exchage the sublists of [i..i+m-1] and [j..j+m-1]
{
    for (int a = 0; a < m; a++)
    {
        T temp = this->getitem(i + a);
        this->setitem(i + a, this->getitem(j + a));
        this->setitem(j + a, temp);
    }
    return;
}

template <class T>
void Listext<T>::rotate(int m)
{
    // this member function needs to be implemented
    int k = 1, i = m, j = this->getlength() - m;
    bool halt = false;
    while (!halt)
    {
        if (i > j)
        {
            this->exchange(k, k + i, j);
            i -= j;
            k += j;
        }
        else if (i < j)
        {
            this->exchange(k, k + j, i);
            j -= i;
        }
        else if (i == j)
        {
            exchange(k, k + i, i);
            halt = true;
        }
    }
}

template <class T>
T Listext<T>::select(int k)
{
    // cout << "     "
    //      << "select k = " << k << std::endl;
    T pivot = this->getitem((numitems + 1) / 2);
    int U_array_counter = 0;
    int V_array_counter = 0;
    Listext<T> *U_array = new Listext<T>(); // numbers smaller than pivot
    Listext<T> *V_array = new Listext<T>(); // numbers larger than pivot
    for (int i = 1; i <= this->getlength(); i++)
    {
        if (this->getitem(i) < pivot) // add any number smaller than
        {
            U_array_counter++;
            U_array->append(this->getitem(i));
        }
        else if (this->getitem(i) > pivot)
        {
            V_array->append(this->getitem(i));
            V_array_counter++;
        }
    }
    if (k > U_array_counter && k <= this->getlength() - V_array_counter)
    {
        return pivot;
    }
    else if (k <= U_array_counter)
    {
        return U_array->select(k);
    }
    else
    {
        return V_array->select(k - (this->getlength() - V_array_counter));
    }
    return -11451;
}
