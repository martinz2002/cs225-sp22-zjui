//
//  listkmp.cpp
//
//
//  Created by KD on 14.01.21.
//  Modified by KD on 12.03.22.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "listkmp.h"
using std::cin;
using std::cout;

template <class T>
KMPlist<T>::KMPlist(int size)
{
    maxsize = size;
    if (size < 20)
        minsize = size;
    else
        minsize = 20;
    numitems = 0;
    reprarray = new T[maxsize];
    nextlist = 0;
}

/* Most of the member functions are the same as for AList */

template <class T>
T &KMPlist<T>::operator[](int index)
{
    return reprarray[index - 1];
}

template <class T>
int KMPlist<T>::getlength(void)
{
    return numitems;
}

template <class T>
void KMPlist<T>::setitem(int index, T value)
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
T KMPlist<T>::getitem(int index)
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
void KMPlist<T>::append(T value)
{
    if (numitems == maxsize)
        allocate();
    reprarray[numitems] = value;
    ++numitems;
    return;
}

template <class T>
void KMPlist<T>::insert(int index, T value)
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
void KMPlist<T>::allocate(void)
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
void KMPlist<T>::remove(int index)
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
void KMPlist<T>::deallocate(void)
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
void KMPlist<T>::concat(KMPlist<T> &list)
{
    int length = list.getlength();
    for (int i = 1; i <= length; ++i)
    {
        append(list[i]);
    }
    return;
}

template <class T>
bool KMPlist<T>::member(T value)
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
bool KMPlist<T>::equal(KMPlist<T> &list)
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
bool KMPlist<T>::sublist(KMPlist<T> &list)
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
void KMPlist<T>::prettyprint(void)
{
    for (int i = 0; i < numitems; i++)
    {
        cout << i + 1 << ":  " << reprarray[i];
        if (i != numitems - 1)
            cout << "; ";
        cout << "\n";
    }
}

/* the added member functions create_next and kmp need to be implemented */

template <class T>
void KMPlist<T>::create_next(void)
{
    int lenth_of_list = this->getlength();
    this->nextlist = new int[lenth_of_list];
    this->nextlist[0] = 0;
    int now_next;
    for (int loop_index = 1; loop_index <= lenth_of_list; loop_index++)
    {
        now_next = this->nextlist[loop_index - 1];
        while (this->reprarray[loop_index] != this->reprarray[now_next] && now_next > 0)
        {
            now_next = this->nextlist[now_next - 1];
        }
        this->nextlist[loop_index] = this->reprarray[loop_index] == this->reprarray[now_next] ? now_next + 1 : now_next;
    }
    /* This member function needs to be implemented. It pre-computes the NEXT values used in the KMP algorithm */
}

template <class T>
int KMPlist<T>::kmp(KMPlist<T> *target)
{
    int position_of_list = 1;
    int position_of_target = 1;
    int target_lenth = target->getlength();
    int list_lenth = this->getlength();

    while (position_of_target + list_lenth - 1 <= target_lenth && position_of_list <= list_lenth)
    {
        if (this->getitem(position_of_list) == target->getitem(position_of_list + position_of_target - 1))
        {
            position_of_list++;
        }
        else
        {
            position_of_target += position_of_list;
            position_of_list = this->nextlist[position_of_list - 1] + 1;
            position_of_target -= position_of_list - 1;
        }
    }
    if (position_of_list >= list_lenth)
    {
        return position_of_target;
    }
    else
    {
        return -1;
    }

    /* This member function needs to be implemented. It implements the KMP algorithm with this list as pattern list and an arbitrary target list given as input */
}
