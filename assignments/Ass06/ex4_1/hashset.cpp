//
//  hashset.cpp
//
//
//  Created by KD on 6.03.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "hashset.h"
using std::cin;
using std::cout;
using std::hash;

/* This defines a constructor */
template <class T>
hashset<T>::hashset(int size)
{
    maxsize = size;
    if (size < 20)
        maxsize = 20;             // default size is 20; no smaller hashtables are considered
    numitems = 0;                 // initially, the hashtable is empty
    reprarray = new T *[maxsize]; // allocate space for the array of pointers
    // the for loop initialises all table entries to be undefined
    for (int i = 0; i < maxsize; i++)
    {
        reprarray[i] = 0;
    }
    T *pt0 = new T; // This defines the fixed placeholder pointer
    *pt0 = 0;
    pt_nil = pt0;
}

// template<class T> hashset<T>::~hashset(void)
// {
//     delete[] reprarray;
// }

template <class T>
T &hashset<T>::operator[](int index)
{
    if (index <= 0 || index > maxsize)
    {
        cout << "Index error: index out of range\n";
        exit(EXIT_FAILURE);
    }
    if (reprarray[index - 1] != 0 && reprarray[index - 1] != pt_nil)
        return *reprarray[index - 1];
    else
    {
        cout << "Index not used in hashtable";
        return 0;
    }
}

template <class T>
void hashset<T>::add(T item)
{
    if (numitems + 1 > maxsize)
    {
        rehash(maxsize * 2);
    }
    // rehash for larger size
    hash<T> hashfunction;
    T insert_item = item, temp_item;
    int now_index, hash_of_item_in_array, insert_item_hash;
    // now_index: the index we are examinining now; insert_item_hash: the hash value of item to be inserted
    insert_item_hash = hashfunction(item) % maxsize;
    now_index = insert_item_hash;
    while (reprarray[now_index] != 0) // the primal condition of the pointers to hash list are all 0,
    // so we continue examinining when the pointer is not zero (it literally points to certain value)
    {
        hash_of_item_in_array = hashfunction(*reprarray[now_index]) % maxsize;
        if (now_index - hash_of_item_in_array > now_index - insert_item_hash)
        // compare the distance between examinined value and inserted value
        {
            temp_item = insert_item;
            insert_item = *reprarray[now_index];
            *reprarray[now_index] = temp_item;
            // swap inserted item with value in list
            insert_item_hash = hash_of_item_in_array;
        }
        now_index++;
        // turns to next index
        if (now_index % maxsize != now_index)
        {
            rehash(maxsize * 2);
            add(insert_item);
            return;
            // rehash if it reaches the end of reprarray
        }
    }
    reprarray[now_index] = new T;
    *reprarray[now_index] = insert_item;
    numitems++;
    //the occasion if the current position is empty
    /* This function needs to be re-implemented by taking the Robin Hood method into account */
}

template <class T>
void hashset<T>::remove(T item)
{
    hash<T> hashfunction; // use again the predefined hashfunction
    int index;
    index = hashfunction(item) % maxsize;
    while (reprarray[index] != 0) // same as for add we search for item in the hashtable; the search starts at the designated hash value, and stops when we find a null pointer
    {
        if (reprarray[index] != pt_nil && *reprarray[index] == item)
        // item found
        {
            int nextindex = (index + 1) % maxsize;
            /* check the next entry, if it is a null pointer; if yes, we can overwrite item by a null pointer; otherwise we use a placeholder, i.e. the pointer pt_nil */
            if (reprarray[nextindex] == 0)
                reprarray[index] = 0;
            else
                reprarray[index] = pt_nil;
            --numitems;
            int load = 100 * numitems / maxsize;
            if (load <= 25)
            // if the min load factor is undershot, we shrink the hashtable, but the size shall always be >= 20
            {
                int newsize = numitems;
                if (newsize < 20)
                    newsize = 20;
                rehash(newsize);
            }
            return;
        }
        index = (index + 1) % maxsize;
    }
    cout << item << " is not in the hashtable.\n";
    return;
}

template <class T>
bool hashset<T>::member(T item)
{
    hash<T> hashfunction; // use the "key" function for the type T (if defined)
    int index;
    index = hashfunction(item) % maxsize;
    while (reprarray[index] != 0) // again we search for item starting from the index position until we find a null pointer
    {
        if (reprarray[index] != pt_nil && *reprarray[index] == item)
            return true; // item was found
        index = (index + 1) % maxsize;
    }
    return false; // a null pointer was found, so item is not in the hashtable
}

template <class T>
void hashset<T>::rehash(int newsize)
{
    if (newsize < 20)
        newsize = 20;
    int newnum = 0;
    T **newarray = new T *[newsize]; // allocate space for a new hashtable of the given new size
    for (int i = 0; i < newsize; i++)
    {
        newarray[i] = 0; // initialise the new hashtable with only null pointers
    }
    for (int i = 0; i < maxsize; i++) // we need to copy all existing entries to the new hash table
    {
        if (reprarray[i] != 0 && reprarray[i] != pt_nil)
        {
            T item = *reprarray[i];
            hash<T> hashfunction;
            int index = hashfunction(item) % newsize;
            // recompute the new hash value
            while (newarray[index] != 0) // find the first free place, where the entry can be stored in the new hashtable
            {
                index = (index + 1) % newsize;
            }
            newarray[index] = reprarray[i]; // do the actual copying
            ++newnum;
        }
    }
    numitems = newnum;    // change the number of stored elements
    reprarray = newarray; // make the new hashtable the one of the hashset object
    maxsize = newsize;    // update the size
}

template <class T>
void hashset<T>::display(void) // only for test purposes
{
    cout << "The size of the hashtable is: " << maxsize << "\n";
    cout << "The number of elements in the hashtable is: " << numitems << "\n";
    for (int i = 0; i < maxsize; ++i)
    {
        if (reprarray[i] == 0)
            cout << "The entry " << i + 1 << " is undefined.\n";
        else if (reprarray[i] == pt_nil)
            cout << "The entry " << i + 1 << " is free.\n";
        else
            cout << "The entry " << i + 1 << " is " << *reprarray[i] << " .\n";
    }
    return;
}
