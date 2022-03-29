//
//  hashmap.cpp
//
//
//  Created by KD on 6.03.21.
//  Modified on 22.03.22.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "hashmap.h"
using std::cin;
using std::cout;
using std::hash;

/* This defines a constructor */
template <class K, class T>
hashmap<K, T>::hashmap(int size)
{
    maxsize = size;
    if (size < 20)
        maxsize = 20;            // default size is 20; no smaller hashmaps are considered
    numitems = 0;                // initially, the hashmap is empty
    keyarray = new K *[maxsize]; // allocate space for the array of pointers
    reprarray = new T[maxsize];  // allocate space for the array of pointers
    // the for loop initialises all table entries to be undefined
    for (int i = 0; i < maxsize; i++)
    {
        keyarray[i] = 0;
    }
    K *pt0 = new K; // This defines the fixed placeholder pointer
    *pt0 = 0;
    pt_nil = pt0;
}

template <class K, class T>
T &hashmap<K, T>::operator[](int index)
{
    if (index <= 0 || index > maxsize)
    {
        cout << "Index error: index out of range\n";
        exit(EXIT_FAILURE);
    }
    if (keyarray[index - 1] != 0 && keyarray[index - 1] != pt_nil)
        return reprarray[index - 1];
    else
    {
        cout << "Index not used in hashtable";
        return 0;
    }
}

template <class K, class T>
void hashmap<K, T>::add(K key, T item)
{
    if (numitems + 1 >= maxsize)
    {
        rehash(maxsize * 2);
    }
    hash<K> hashfunction;
    int index1;
    index1 = hashfunction(key) % maxsize;
    while (keyarray[index1] != 0)
    {
        rehash(maxsize * 2);
        index1 = hashfunction(key) % maxsize;
    }
    keyarray[index1] = new T;
    reprarray[index1] = item;
    *keyarray[index1] = key;
    numitems++;
    /* This member function needs to be implemented. Adapt the corresponding function on hashsets. */
}

template <class K, class T>
void hashmap<K, T>::remove(K key)
{
    if (numitems + 1 >= maxsize)
    {
        rehash(maxsize * 2);
    }
    hash<K> hashfunction;
    int index1;
    index1 = hashfunction(key) % maxsize;
    while (keyarray[index1] != 0 && *keyarray[index1] != key)
    {
        index1++;
        index1 %= maxsize;
    }
    if (keyarray[index1])
    {
        keyarray[index1] = 0;
        rehash(maxsize);
    } /* This member function needs to be implemented. Adapt the corresponding function on hashsets. */
    numitems--;
}

template <class K, class T>
T hashmap<K, T>::retrieve(K key)
{
    if (numitems + 1 >= maxsize)
    {
        rehash(maxsize * 2);
    }
    hash<K> hashfunction;
    int index1;
    index1 = hashfunction(key) % maxsize;
    while (keyarray[index1] != 0 && *keyarray[index1] != key)
    {
        index1++;
        index1 %= maxsize;
    }
    if (keyarray[index1])
        return reprarray[index1];
    else
        return -1;
    /* This member function needs to be implemented. Adapt the corresponding function on hashsets. */
}

template <class K, class T>
bool hashmap<K, T>::member(K key, T item)
{
    if (retrieve(key) == item)
        return true;
    else
        return false;
    /* This member function needs to be implemented. Adapt the corresponding function on hashsets. */
}

template <class K, class T>
void hashmap<K, T>::rehash(int newsize)
{
    if (newsize < 20)
        newsize = 20;
    int newnum = 0;
    K **newkeyarray = new K *[newsize];
    T *newarray = new T[newsize];
    // allocate space for a new hashmap of the given new size
    for (int i = 0; i < newsize; i++)
    {
        newkeyarray[i] = 0; // initialise the new hashtable with only null pointers
    }
    for (int i = 0; i < maxsize; i++) // we need to copy all existing entries to the new hash table
    {
        if (keyarray[i] != 0 && keyarray[i] != pt_nil)
        {
            K item = *keyarray[i];
            T value = reprarray[i];
            hash<T> hashfunction;
            int index = hashfunction(item) % newsize;
            // recompute the new hash value
            while (newkeyarray[index] != 0) // find the first free place, where the entry can be stored in the new hashtable
            {
                index = (index + 1) % newsize;
            }
            newkeyarray[index] = keyarray[i]; // do the actual copying
            newarray[index] = reprarray[i];   // do the actual copying
            ++newnum;
        }
    }
    numitems = newnum;      // change the number of stored elements
    keyarray = newkeyarray; // make the new hashmap
    reprarray = newarray;
    maxsize = newsize; // update the size
}

template <class K, class T>
void hashmap<K, T>::display(void) // only for test purposes
{
    cout << "The size of the hashtable is: " << maxsize << "\n";
    cout << "The number of elements in the hashtable is: " << numitems << "\n";
    for (int i = 0; i < maxsize; ++i)
    {
        if (reprarray[i] == 0)
            cout << "The entry " << i + 1 << " is undefined.\n";
        else if (reprarray[i] == pt_nil[i])
            cout << "The entry " << i + 1 << " is free.\n";
        else
            cout << "The entry " << i + 1 << " has the key " << *keyarray[i] << " and the value " << reprarray[i] << " .\n";
    }
    return;
}
