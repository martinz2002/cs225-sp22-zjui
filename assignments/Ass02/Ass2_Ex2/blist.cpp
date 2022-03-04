//
//  blist.cpp
//
//
//  Created by KD on 14.01.21.
//  Modified by KD on 09.05.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "blist.h"
using std::cin;
using std::cout;

/* the class template AList does not require any major change.
 However, we only allow list elements in a range between min and max */

template <class T>
AList<T>::AList(int size)
{
    maxsize = size;
    if (size < 20)
        minsize = size;
    else
        minsize = 20;
    numitems = 0;
    min = 0;
    max = 0;
    reprarray = new T[maxsize];
}

template <class T>
T &AList<T>::operator[](int index)
{
    return reprarray[index - 1];
}

template <class T>
void AList<T>::setmin(T minimum)
{
    if (minimum <= max)
        min = minimum;
    return;
}

template <class T>
void AList<T>::setmax(T maximum)
{
    if (maximum >= min)
        max = maximum;
    return;
}

template <class T>
T AList<T>::getmin(void)
{
    return min;
}

template <class T>
T AList<T>::getmax(void)
{
    return max;
}

template <class T>
int AList<T>::getlength(void)
{
    return numitems;
}

template <class T>
void AList<T>::setitem(int index, T value)
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
T AList<T>::getitem(int index)
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
void AList<T>::append(T value)
{
    if (value < min || value >= max)
    {
        cout << "Value " << value << " is out of range.\n";
        return;
    }
    if (numitems == maxsize)
        allocate();
    reprarray[numitems] = value;
    ++numitems;
    return;
}

template <class T>
void AList<T>::insert(int index, T value)
{
    if (value < min || value >= max)
    {
        cout << "Value " << value << " is out of range.\n";
        return;
    }
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
void AList<T>::allocate(void)
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
void AList<T>::remove(int index)
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
void AList<T>::deallocate(void)
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
void AList<T>::concat(AList<T> &list)
{
    if (list.getmax() > max)
        max = list.getmax();
    if (list.getmin() < min)
        min = list.getmin();
    int length = list.getlength();
    for (int i = 1; i <= length; ++i)
    {
        append(list[i]);
    }
    return;
}

template <class T>
bool AList<T>::member(T value)
{
    if (value < min || value >= max)
    {
        cout << "Value " << value << " is out of range.\n";
        return false;
    }
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
bool AList<T>::equal(AList<T> &list)
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
bool AList<T>::sublist(AList<T> &list)
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
void AList<T>::prettyprint(void)
{
    for (int i = 0; i < numitems; i++)
    {
        cout << i + 1 << ":  " << reprarray[i];
        if (i != numitems - 1)
            cout << "; ";
        cout << "\n";
    }
}

/* for the derived class template only bucket sort needs to be implemented */

template <class T>
AList<T> *BList<T>::bucketsort(void) // increasing order
{
    // NOTE: 默认派生为私有派生；任何派生形式都不能访问 base class 的 private member
    // numitem = getlength();
    if (this->getlength() <= 1)
    {
        exit(EXIT_FAILURE);
    }
    // Fetch some useful data
    const int my_max = this->getmax();
    const int my_min = this->getmin();
    const int numitem = this->getlength();
    double each_bucket = (my_max - my_min) / numitem;   // Get the range of each bucket
    AList<T> *bucket = new AList<T>[numitem];
    // Set the max and min value of each bucket, indicating the range of each
    for (int each_item = numitem - 1; each_item >= 0; each_item--)
    {
        bucket[each_item].setmax(my_min + each_bucket * (each_item + 1));
        bucket[each_item].setmin(my_min + each_bucket * each_item);
    }
    for (int each_item = numitem - 1; each_item >= 0; each_item--)
    {
        int temp = (this->getitem(each_item + 1) - my_min) / each_bucket;
        // binary search to find where to insert
        // increasing order
        int left = 0, right = bucket[temp].getlength() - 1;
        while (left <= right && right >= 0 && left <= bucket[temp].getlength() - 1)
        {
            int m = (left + right) / 2;
            if (bucket[temp].getitem(m + 1) == this->getitem(each_item + 1))
            {
                left = m;
                right = m;
                break;
            }
            else if (bucket[temp].getitem(m + 1) > this->getitem(each_item + 1))
            {
                right = m - 1;
            }
            else // if (bucket[temp].getitem(m) < this->getitem(each_item))
            {
                left = m + 1;
            }
        }

        bucket[temp].insert(left, this->getitem(each_item + 1));
    }
    // concat all the buckets
    for (int each_item = 1; each_item < numitem; each_item++)
    {
        if (bucket[each_item].getlength() != 0)
        {
            bucket[0].concat(bucket[each_item]);
        }
    }
    return bucket;
}
