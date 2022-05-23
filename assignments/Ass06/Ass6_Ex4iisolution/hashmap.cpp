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
using std::cout;
using std::cin;
using std::hash;

/* This defines a constructor */
template<class K, class T> hashmap<K,T>::hashmap(int size)
{
    maxsize = size;
    if (size < 20)
        maxsize = 20; // default size is 20; no smaller hashmaps are considered
    numitems = 0; // initially, the hashmap is empty
    keyarray = new K*[maxsize];  // allocate space for the array of pointers
    reprarray = new T[maxsize];  // allocate space for the array of pointers
    // the for loop initialises all table entries to be undefined
    for (int i = 0; i < maxsize; i++)
    {
        keyarray[i] = 0;
    }
    K *pt0 = new K;  // This defines the fixed placeholder pointer
    *pt0 = 0;
    pt_nil = pt0;
}

template<class K, class T> T & hashmap<K,T>::operator[](int index)
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

template<class K, class T> void hashmap<K,T>::add(K key, T item)
{
    hash<K> hashfunction; // use the predefined hashfunction to get "key" values
    int index;
    index = hashfunction(key) % maxsize; // First determine the position index in the hash table, where the new value is stored, if free.
    int location = -1;  // used to distinguish between undefined entries (null pointer) and placeholders
    while (keyarray[index] != 0) // We first check, if the item is already in the hashtable
    {
        if (keyarray[index] != pt_nil && *keyarray[index] == key)  // key found; no insertion
        {
            if (reprarray[index] == item) // The value associated with the key is already the item to be inserted
            {
                cout << "The hashtable already contains an entry with key " << key << " and value " << item << ".\n";
            }
            else // The value associated with the key differs from the item to be inserted
            {
                cout << "The hashtable already contains an entry with key " << key << " and different value " << reprarray[index] << ".\n";
            }
            return;
        }
        if (location < 0 && keyarray[index] == pt_nil) // a placeholder object is found; i.e. if the item is not in the hashtable, this will be the place for the insertion
            location = index;
        index = (index + 1) % maxsize;
    }
    // after leaving the while loop we either have location < 1, i.e. we store the (key,item) pair at the last examined index (which contains a null pointer),
    // otherwise, if location >= 0 holds, we found a placeholder, so the (key,item) pair will be stored at the location of this placeholder
    if (location < 0)
        location = index;
    K *pt = new K;
    *pt = key;
    keyarray[location] = pt;   // store key in the hashtable
    reprarray[location] = item;   // store associated item in the hashtable
    ++ numitems;
    int load = 100 * numitems / maxsize;
    if (load >= 75)             // max load factor is exceeded; double the size
    {
        int newsize = 2 * numitems;
        rehash(newsize);
    }
    return;
}

template<class K, class T> void hashmap<K,T>::remove(K key)
{
    hash<K> hashfunction;  // use again the predefined hashfunction
    int index;
    index = hashfunction(key) % maxsize;
    while (keyarray[index] != 0)  // same as for add we search for key in the hashtable; the search starts at the designated hash value, and stops when we find a null pointer
    {
        if (keyarray[index] != pt_nil && *keyarray[index] == key)
                    // key found
        {
            int nextindex = (index + 1) % maxsize;
            /* check the next entry, if it is a null pointer; if yes, we can overwrite key by a null pointer; otherwise we use a placeholder, i.e. the pointer pt_nil */
            if (keyarray[nextindex] == 0)
                keyarray[index] = 0;
            else
                keyarray[index] = pt_nil;
            --numitems;
            /* Note that we do not update the assciated value, which is irrelevant for placeholders or null pointers. */
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
    cout << "The key " << key << " is not in the hashtable.\n";
    return;
}

template<class K, class T> T *hashmap<K,T>::retrieve(K key)
{
    hash<K> hashfunction;  // use the "key" function for the type K (if defined)
    int index;
    index = hashfunction(key) % maxsize;
    while (keyarray[index] != 0) // again we search for key starting from the index position until we find a null pointer
    {
        if (keyarray[index] != pt_nil && *keyarray[index] == key)
        {
            T res = reprarray[index];
            T *pt;
            pt = &res;
            return pt; // The key was found, so a pointer to the associated item will be returned
        }
        index = (index + 1) % maxsize;
    }
    cout << "The key " << key << " does not appear in the hashtable.\n";
    return 0;  // a null pointer was found, so the key is not in the hashtable
}

template<class K, class T> bool hashmap<K,T>::member(K key, T item)
{
    hash<K> hashfunction;  // use the "key" function for the type K (if defined)
    int index;
    index = hashfunction(key) % maxsize;
    while (keyarray[index] != 0) // again we search for key starting from the index position until we find a null pointer
    {
        if (keyarray[index] != pt_nil && *keyarray[index] == key)
        {
            if (reprarray[index] == item)
                return true;  // The (key,item) pair was found
            else
            {
                cout << "The key " << key << " is in the hashtable, but the associated value is " << reprarray[item] << ", which differs from " << item << ".\n";
                return false;
            }
        }
        index = (index + 1) % maxsize;
    }
    return false;  // a null pointer was found, so the (key,item) pair is not in the hashtable
}

template<class K, class T> void hashmap<K,T>::rehash(int newsize)
{
    if (newsize < 20)
        newsize = 20;
    int newnum = 0;
    K **newkeyarray = new K*[newsize];
    T *newarray = new T[newsize];
    // allocate space for a new hashmap of the given new size
    for (int i = 0; i < newsize; i++)
    {
        newkeyarray[i] = 0;   // initialise the new hashtable with only null pointers
    }
    for (int i = 0; i < maxsize; i++)  // we need to copy all existing entries to the new hash table
    {
        if (keyarray[i] != 0 && keyarray[i] != pt_nil)
        {
            K item = *keyarray[i];
            T value = reprarray[i];
            hash<K> hashfunction;
            int index = hashfunction(item) % newsize;
                // recompute the new hash value
            while (newkeyarray[index] != 0)  // find the first free place, where the entry can be stored in the new hashtable
            {
                index = (index + 1) % newsize;
            }
            newkeyarray[index] = keyarray[i];  // do the actual copying
            newarray[index] = reprarray[i];  // do the actual copying
            ++ newnum;
        }
    }
    numitems = newnum;   // change the number of stored elements
    keyarray = newkeyarray;   // make the new hashmap
    reprarray = newarray;
    maxsize = newsize;   // update the size
}

template<class K, class T> void hashmap<K,T>::display(void) // only for test purposes
{
    cout << "The size of the hashtable is: " << maxsize << "\n";
    cout << "The number of elements in the hashtable is: " << numitems << "\n";
    for (int i = 0; i < maxsize; ++i)
    {
        if (keyarray[i] == 0)
            cout << "The entry " << i + 1 << " is undefined.\n";
        else if (keyarray[i] == pt_nil)
            cout << "The entry " << i + 1 << " is free.\n";
        else
            cout << "The entry " << i + 1 << " has the key " << *keyarray[i] << " and the value " << reprarray[i]<< " .\n";
    }
    return;
}
